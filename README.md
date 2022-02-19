# Metable
A distributed table-like metadata service for managing your large scale cluster with highly performance.  
Note that this project is WIP.

## Features
- Managing your meta data/cluster information with SQL-like language.
- The ability to subscribe the changing operations on a table.
- State-based storage and delta notifications to let you keep a very consistant metadata.
- P2P service registration and discovery to achieve a higher performance.
- Highly performance for adhoc querying the metadata.
- 

## Usage
```sql
# Node1
create table A (
    int id,
    string message
);
```
```sql
# Node2
let func1 = (schemaof(A) record, event) {
    print record, event;
};
sub table A on RECORD_INSERTED, RECORD_DELETED with func1;
```
```sql
# Node3
let func1 = (schemaof(A) record, event) {
    print record, event;
};
sub table A on RECORD_INSERTED, RECORD_DELETED with func1;
```
