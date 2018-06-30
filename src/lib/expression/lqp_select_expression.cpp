#include "lqp_select_expression.hpp"

#include <sstream>

#include "boost/functional/hash.hpp"

#include "expression_utils.hpp"
#include "logical_query_plan/abstract_lqp_node.hpp"
#include "logical_query_plan/lqp_utils.hpp"
#include "utils/assert.hpp"


namespace opossum {

LQPSelectExpression::LQPSelectExpression(const std::shared_ptr<AbstractLQPNode>& lqp,
                                         const std::vector<ParameterID>& parameter_ids,
                                         const std::vector<std::shared_ptr<AbstractExpression>>& parameter_expressions):
 AbstractExpression(ExpressionType::Select, parameter_expressions), lqp(lqp), parameter_ids(parameter_ids) {
  Assert(parameter_ids.size() == parameter_expressions.size(), "Need exactly as many ParameterIDs as parameter Expressions");
}

size_t LQPSelectExpression::parameter_count() const {
  return parameter_ids.size();
}

std::shared_ptr<AbstractExpression> LQPSelectExpression::parameter_expression(const size_t parameter_idx) const {
  Assert(parameter_idx < parameter_count(), "Parameter index out of range");
  return arguments[parameter_idx];
}

bool LQPSelectExpression::requires_calculation() const {
  // Select expressions always need to be computed, no matter whether they have arguments or not
  return true;
}

std::shared_ptr<AbstractExpression> LQPSelectExpression::deep_copy() const {
  const auto lqp_copy = lqp->deep_copy();

  return std::make_shared<LQPSelectExpression>(lqp_copy, parameter_ids, expressions_copy(arguments));
}

std::string LQPSelectExpression::as_column_name() const {
  std::stringstream stream;
  stream << "SUBSELECT (LQP, " << lqp.get() << ", Parameters: " << expression_column_names(arguments) << ")";

  return stream.str();
}

DataType LQPSelectExpression::data_type() const {
  Assert(lqp->column_expressions().size() == 1, "Can only determine the DataType of SelectExpressions that return exactly one column");
  return lqp->column_expressions()[0]->data_type();
}

bool LQPSelectExpression::_shallow_equals(const AbstractExpression& expression) const {
  const auto& lqp_select_expression = static_cast<const LQPSelectExpression&>(expression);

  const auto mismatch = lqp_find_subplan_mismatch(lqp, lqp_select_expression.lqp);

  return !mismatch && parameter_ids == lqp_select_expression.parameter_ids;
}

size_t LQPSelectExpression::_on_hash() const {
  return 0;  // TODO(moritz)
}

}  // namespace opossum
