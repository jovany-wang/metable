# Proposal: Metable SQL-like Specification

## Status

Under Discussion

## Author

meijies

## Background

The sql is the most used way to interact with table storage system. Metable needs to support it for user accessing data
by command line tool, web page and client. Furthermore, we will also introduce extra action, `subscribe`.
. `subscribe` keep fetching snapshot data and increment data until unsubscribe it, while `query` action only fetch
snapshot data at the moment.

## SQL

**1) DDL**

```
create database <database_name>;
drop database <database_name>;
show databases;
use <database_name>;

create table <table_name> (
    <column_name> <column_type> <column_option>
    (,<column_name> <column_type> <column_option>)*,
    primary key <column_name> (,<column_name >)*
) <table_option>;
show tables;
drop table <table_name>;

alter table <old_table_name> rename [to] <new_table_name>;
alter table <table_name> add column <column_name> <column_type> <column_option>;
alter table <table_name> drop column <column_name>;
```

**2) DML**

```
insert into <table_name> (<column_name> (, <column_name>)*)
values (<column_value> (, <column_value>)*);

delete from <table_name> where <condition> (and/or <condition>)*;

select (*|<column_name>) (,<column_name>)* from <table_name> where <condition> (and|or <condition>)*;

update <table_name> set <column_name> = <column_value> (,<column_name> = <column_value>)* where <condition> (and|or <condition>)*;

sub (*|<column_name>) (,<column_name>)* from  <table_name> where <condition> (and|or <condition>)*;
```

**supported column option so far:**

+ comment <column_description>
+ not null
+ default <column_value>

**supported table option so far:**

+ comment <table_description>

**supported column type:**

+ bool
+ short
+ int
+ long
+ float
+ double
+ decimal
+ string
+ date
+ datetime

**supported condition**

+ `>`, `<`, `=`, `<=`, `>=`, `!=`
+ `in`
+ `like`, `not like`
+ `between ... and ...`
+ `is null` and `= null`

## Command line tool

The command line tool will let user access data easily at server environment. It supports executing sql statement and
allows user setting environment variables to control how to print data, send data and so on.

**1) Environment variables that need to be supported so far**

| env variable  | description                                                               |
|---------------|---------------------------------------------------------------------------|
| print_format  | the format to print selected data, default is table, also support csv     |

**2) How to set environment variables**
some example here.

```
set print_format=csv;
```
