# Proposal: SQL Support

## Status

Under Discussion

## Background

The sql is the most used way to interact with table store system. Metable need to support it for user accessing data by
command line tool, web page and client. Further more，we will also introduce extra two actions, there are `subscribe`
and `publish`. `subscribe` action use select statement to represent what data do you want and keep fetching snapshot
data and increment data until unsubscribe it, while `query` action only fetch snapshot data at the moment. `publish`
action will keep sending data to server until closing the client.

## SQL

**1) DDL**

```
create database <database_name>;
drop database <database_name>;
create table <table_name> (
    <column_name> <column_type> <column_option>
    (,<column_name> <column_type> <column_option>)*,
    primary key <column_name> (,<column_name >)*
) <table_option>;
drop table <table_name>;
alter table <old_table_name> rename [to] <new_table_name>;
alter table <table_name> add column <column_name> <column_type> <column_option>;
alter table <table_name> drop column <column_name>;
```

**2) DML **

```
insert into <table_name> (<column_name> (, <column_name>)*)
values (<column_value> (, <column_value>)*);

delete from <table_name> where <condition> (and/or <condition>)*

select (*|<column_name>) (, *|<column_name>)* from <table_name> where <condition> (and/or <condition>)*

update <table_name> set <column_name> = <column_value> (,<column_name> = <column_value>)* where <condition> (and/or <condition>)*
```

## command line tool

the command line tool will let user access data easily at server environment. It supports execute sql statement and
allow user to set environment variables to controller how to print data, send data and so on.

**1) Environment variables that need to be supported so far**

| env variable  | description                                                               |
|---------------|---------------------------------------------------------------------------|
| print_format  | the format to print selected data, default is table, also support csv     |
| select_action | the way to fetch selected data, default is query, also support subscribe  |
| insert_action | the way to send data to metable, default is execute, also support publish |

**2) How to set environment variables**
some example here.

```sql
> set print_format=csv;
> set select_action=subscribe;
```

## client library

here provide the basic design for client executing sql statement.

```
client.Sql(<select_sql_statement>).query();
client.Sql(<select_sql_statement>).subscribe(<handle>)
client.Sql(<insert_sql_statement>).execute();
client.Sql(<insert_sql_statement>).publish(<supply>)
```
