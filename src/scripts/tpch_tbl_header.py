#!/usr/bin/python3

"""
    Helper script to prepend the header information to the .tbl files generated by dbgen
"""

tables = {
    "customer": [
        ["c_custkey", "c_name", "c_address", "c_nationkey", "c_phone", "c_acctbal", "c_mktsegment", "c_comment"],
        ["int", "string", "string", "int", "string", "float", "string", "string"]
    ],
    "lineitem": [
        ["l_orderkey", "l_partkey", "l_suppkey", "l_linenumber", "l_quantity", "l_extendedprice", "l_discount", "l_tax",
         "l_returnflag", "l_linestatus", "l_shipdate", "l_commitdate", "l_receiptdate", "l_shipinstruct", "l_shipmode",
         "l_comment"],
        ["int", "int", "int", "int", "float", "float", "float", "float", "string", "string", "string", "string",
         "string", "string", "string", "string"]
    ],
    "nation": [
        ["n_nationkey", "n_name", "n_regionkey", "n_comment"],
        ["int", "string", "int", "string"]
    ],
    "orders": [
        ["o_orderkey", "o_custkey", "o_orderstatus", "o_totalprice", "o_orderdate", "o_orderpriority", "o_clerk",
         "o_shippriority", "o_comment"],
        ["int", "int", "string", "float", "string", "string", "string", "int", "string"]
    ],
    "part": [
        ["p_partkey", "p_name", "p_mfgr", "p_brand", "p_type", "p_size", "p_container", "p_retailsize", "p_comment"],
        ["int", "string", "string", "string", "string", "int", "string", "int", "string"]
    ],
    "partsupp": [
        ["ps_partkey", "ps_suppkey", "ps_availqty", "ps_supplycost", "ps_comment"],
        ["int", "int", "int", "float", "string"]
    ],
    "region": [
        ["r_regionkey", "r_name", "r_comment"],
        ["int", "string", "string"]
    ],
    "supplier": [
        ["s_suppkey", "s_name", "s_address", "s_nationkey", "s_phone", "s_acctbal", "s_comment"],
        ["int", "string", "string", "int", "string", "float", "string"]
    ]}

if __name__ == "__main__":
    for table_name, header in tables.items():
        header_str = "|".join(header[0]) + "\n" + "|".join(header[1]) + "\n"
        file_name = "{}.tbl".format(table_name)

        with open(file_name, "r") as table_file:
            original_tbl_file_content = table_file.read()

        with open(file_name, "w") as table_file:
            table_file.write(header_str + original_tbl_file_content)
