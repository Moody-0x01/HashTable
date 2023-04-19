# Hash Table Rust vs C.

- hash table implementation in Rust vs in C. 

# structures
- I have used a simple struct to encapsulate my key value pairs, Rust was better because it has generics..

- Rust
```Rust

struct Cell<Key, Value> {
    key: Key,
    value: Value,
    taken: bool
}

struct HashTable<Key, Value> { 
    pairs: Vec<Cell<Key, Value>>,
    cap: usize, // Allocated.
    size: usize,
}

```
- C
```C
typedef struct Cell {
	char *key;
	int  value;
	bool taken;
} Cell;

typedef struct HashTable {
	Cell *Cells;
	size_t size;
	size_t cap;
} HashTable;
```

# Funcs
- Hash function.
Rust:
```Rust
impl Hashable for String {
    fn hash(&self) -> usize {
        let mut hash: usize = 5381;
        for c in self.bytes() {
            hash = ((hash << 5).wrapping_add(hash)).wrapping_add(c as usize);
        }

        hash
    }
}
```

C:
```C
size_t hash(char *key) {
	
	size_t hash_ = 5381;
	
	for(;*key != '\0';*key++)
	{
		hash_ = ((hash_ << 5) + hash_) + (size_t) *key;
	}

	return hash_;
}


```


Hash function: [Djb2 Doc](https://theartincode.stanis.me/008-djb2)
