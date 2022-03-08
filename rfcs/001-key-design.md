# Mapping Table Data to KV Storage

## F1

>Each key logically includes the name of the table, the primary key values of the containing row, and the name of the column whose value is stored in the pair.

F1 key design：| {Table name} + {Primary key value} + {Column name} |

For example, we have a table named Example：
```
-----------------------------------------------
first_name* | last_name* | age | phone_number|
-----------------------------------------------
Jhon           Doe         24    123
Jane           Doe         35    456
-----------------------------------------------

This table will be stored as the following shows：
---------------------------------------
key                             value
Example.John.Doe.age            24
Example.Jane.Doe.phone_number   456
```

Optimization will be done in the implementation:
>Although this appears to needlessly repeat all primary key values in the key for each column value, in practice, F1’s physical storage format eliminates this redundancy*.  * Shute, J., et al. F1: A Distributed SQL Database That Scales. VLDB, 6(11), 2013.

Reference：Online, Asynchronous Schema Change in F1

## CockroachDB

Key design： | /{table id}/{primary key valye}/{column id} |

Reference：https://www.cockroachlabs.com/blog/sql-in-cockroachdb-mapping-table-data-to-key-value-storage/


## TiDB

CREATE TABLE t1 {
    id BIGINT PRIMARY KEY,
    age BIGINT,
    name varchar,
    INDEX(age),
}

### Table

Key design: | t + Table ID + Primary Key |

Suppose we have two tuples of values (1, 10, "zhangsan") and (2, 12, "lisi")

This table will be stored as the following shows：
```
t_11_1 -> (10, "zhangsan")
t_11_2 -> (12, "lisi")
```

### Index

Each index has a unique id，and the key is designed as: |  i(literally) + Index ID + index value + Primary Key |

Suppose we have tuples of value (1, 10) and (2, 12)，these indexs in the table will be stored as the following shows:

```
i_13_10_1 -> nil
i_13_12_2 -> nil
```

Firstly, we match the prefix and get the primary key value, then get the data with this value.

Reference：https://pingcap.com/zh/blog/how-tikv-store-get-data
