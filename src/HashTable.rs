use std::fmt::Display;
pub const CAP: usize = 10;

#[derive(Debug, Clone, Copy)]
struct Cell<Key, Value> {
    key: Key,
    value: Value,
    taken: bool
}

impl<Key: Default + Clone, Value: Default + Clone>Cell<Key, Value> {
    fn new() -> Self {
        Self {
            key: Key::default(),
            value: Value::default(),
            taken: false,
        }
    }
}


#[derive(Debug, Clone)]
struct HashTable<Key, Value> { 
    pairs: Vec<Cell<Key, Value>>,
    cap: usize,
    size: usize,
}

trait Hashable {
    fn hash(&self) -> usize;
}



impl Hashable for String {
    fn hash(&self) -> usize {
        let mut hash: usize = 5381;

        for c in self.bytes() {
            hash = ((hash << 5).wrapping_add(hash)).wrapping_add(c as usize);
        }

        hash
    }
}

impl<Key: Default + Clone + Hashable + Display, Value: Default + Clone + Display> HashTable<Key, Value> {
    fn new() -> Self {
        Self {
            pairs: vec![Cell::new(); CAP],
            cap: CAP,
            size: 0,
        }
    }

    fn keys(&mut self) -> Vec<Key> {
        return self.pairs.iter()
            .filter(|cell| cell.taken)
            .map(|cell| cell.key.clone())
            .collect::<Vec<Key>>();
    }
    
    fn values(&mut self) -> Vec<Value> {
        return self.pairs.iter()
            .filter(|cell| cell.taken)
            .map(|cell| cell.value.clone())
            .collect::<Vec<Value>>();
    }
    
    fn expand(&mut self) -> bool {
        
        if self.size == self.cap {
            let mut new_ = vec![Cell::new(); self.cap + CAP];
            
            for i in 0..self.cap {
                new_[i] = self.pairs[i].clone();
            }

            self.cap = self.cap + CAP;
            return true;
        }
        return false;
    }

    fn get(&mut self, key: &Key) -> Option<&Value> {
        let index = key.hash() % CAP;
        
        if self.pairs[index].taken {
            return Some(&self.pairs[index].value);
        }

        return None;
    }

    
    fn get_mut(&mut self, key: &Key) -> Option<&mut Value> {
        let index = key.hash() % CAP;
        
        if self.pairs[index].taken {
            return Some(&mut self.pairs[index].value);
        }

        return None;
    }
    
    fn increment_size(&mut self) {
        self.size = (self.size + 1);
    }

    fn insert(&mut self, key: Key, value: Value) -> bool {
        let mut index = key.hash() % CAP;
    
        while self.pairs[index].taken {
            index = index + 1;
        }

        if index == CAP {
            // TODO: Make the table expandable for more elements.
            return false;
        }
        
        self.pairs[index].key   = key;
        self.pairs[index].value = value;
        self.pairs[index].taken = true;
        self.increment_size();
        return true;
    }
    
    fn delete(&mut self) {
        todo!();
    }
    
    fn contains(&mut self, key: Key) {
        todo!();
    }
    
    fn display(&mut self) {
        for i in 0..self.cap {
            let cell = &self.pairs[i];
            if cell.taken {
                println!("{} -> {}", cell.key, cell.value);
            }
        }
    }
    

    fn display_keys(&mut self) {
        let ks = self.keys();
        for i in 0..self.size {
            println!("{}", ks[i])
        }
    }
    
    fn display_values(&mut self) {
        let values = self.values();
        for i in 0..self.size {
            println!("{}", values[i])
        }
    }
    
    fn display_cells(&mut self) {
        for i in 0..self.cap {
            let cell = &self.pairs[i];
            println!("({}, {}, {})", cell.key, cell.value, cell.taken);
        }
    }
}

fn print_table(table: &HashTable<String, String>) {

    for i in 0..CAP {
        let cell = &table.pairs[i];
        
        if cell.taken {
            println!("{} -> {}", cell.key, cell.value);
            continue;
        }
        
        println!("x");
    }

}

#[allow(unused_variables)]
fn main() { 
    let mut table: HashTable<String, String> = HashTable::new();
    

    table.insert("England".to_string(), "London".to_string()); 
    table.insert("USA".to_string(), "NYC".to_string()); 
    table.insert("JAPAN".to_string(), "Tokyo".to_string());
    println!("----CELLS-----"); 
    table.display_cells();
    println!("----KEYS-----"); 
    table.display_keys();
    println!("----VALUES-----"); 
    table.display_values();

}
