# Simple DB

Simple key-value database. For learning purposes. Based on ideas from the first 4 chapters of the book "Designing Data-Intensive Applications" by Martin Klepmann

## Testing

To build, run:
```
make
```

To run:

```
cd bin
./simpledb
Welcome to simpleDB
> put 1 10
> get 1
10
> get 10
Key not found: 10
> delete 1
Removed key: 1
```


## TODO:

- [ ] create in-memory key-value store using a mem table, integer keys and values
- [ ] flush mem table to disk by writing to an SSTable, keep sequence of SStable files
- [ ] When reading, start from mem-table then try SSTables
- [ ] Merge SSTables into LSM periodically
- [ ] Add a write ahead log for error recovery (write to log before committing to memtable)