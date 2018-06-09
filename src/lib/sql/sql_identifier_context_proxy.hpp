#pragma once

#include <memory>
#include <vector>

#include "expression/parameter_expression.hpp"

namespace opossum {

class AbstractExpression;
struct SQLIdentifier;
class SQLIdentifierContext;

class SQLIdentifierContextProxy final {
 public:
  SQLIdentifierContextProxy(const std::shared_ptr<SQLIdentifierContext>& wrapped_context,
                                     const std::shared_ptr<ParameterID>& parameter_id_counter,
                                     const std::shared_ptr<SQLIdentifierContextProxy>& outer_context_proxy = {});

  std::shared_ptr<AbstractExpression> resolve_identifier_relaxed(const SQLIdentifier& identifier);

  const ExpressionUnorderedMap<ParameterID>& accessed_expressions() const;

 private:
  std::shared_ptr<SQLIdentifierContext> _wrapped_context;
  std::shared_ptr<ParameterID> _parameter_id_counter;
  std::shared_ptr<SQLIdentifierContextProxy> _outer_context_proxy;

  // Previously accessed expressions that were already assigned a ParameterID
  ExpressionUnorderedMap<ParameterID> _accessed_expressions;
};


}  // namespace opossum