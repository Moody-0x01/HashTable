use std::fmt::Display;
use std::cmp::PartialEq;

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
    cap: usize, // Allocated.
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

impl<Key: Default + Clone + PartialEq + Hashable + Display, Value: Default + Clone + Display> HashTable<Key, Value> {
    fn new() -> Self {
        Self {
            pairs: vec![Cell::new(); CAP], // CAP == 10
            cap: CAP,// 10
            size: 0, // 0 because ylh drna table.
        }
    }
    
    fn new_with_cap(cap: usize) -> Self {
        Self {
            pairs: vec![Cell::new(); cap],
            cap: cap,
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
        // same thing..
        return self.pairs.iter() 
            .filter(|cell| cell.taken)
            .map(|cell| cell.value.clone())
            .collect::<Vec<Value>>();
    }
    
    fn expand(&mut self) -> bool {
        let mut new_ = vec![Cell::new(); self.cap + CAP];
        
        for i in 0..self.cap {
            new_[i] = self.pairs[i].clone();
        }
        
        self.pairs = new_;
        self.cap = self.cap + CAP;
        return true;
    }

    fn get(&mut self, key: &Key) -> Option<&Value> {
        
        if let Some(cell) = self.get_cell_mut(key) {
            return  Some(&cell.value); 
        }        

        return None;
    }

    
    fn get_mut(&mut self, key: &Key) -> Option<&mut Value> {
        if let Some(cell) = self.get_cell_mut(key) {
            return Some(&mut cell.value); 
        }

        return None;
    }
    
    fn increment_size(&mut self) {
        self.size = self.size + 1;
    }

    fn insert(&mut self, key: Key, value: Value) -> bool {
        let mut exists: bool = false;
        let mut index = key.hash() % self.cap;
         
        while self.pairs[index].taken {
            
            if key == self.pairs[index].key {
                exists = true;
                break;
            }

            index = index + 1;
        }

        if index >= self.cap {
            // TODO: Make the table expandable for more elements.
            self.expand();
            return self.insert(key, value);
        }
        if !exists {
            // Add the key value pair
            self.pairs[index].key   = key;
            self.pairs[index].value = value;
            self.pairs[index].taken = true;
            self.increment_size();
        } else {
            // Overwrite the value associated with key.
            match self.get_mut(&key) {
                Some(mut cell_value) => {
                    *cell_value = value;
                },
                None    => {
                    return false;
                }
            }
        }
        
        return true;
    }
    fn get_cell_mut(&mut self, key: &Key)  -> Option<&mut Cell<Key, Value>> {
        let mut index = key.hash() % self.cap;          
        while *key != self.pairs[index].key && index < self.cap {

            index += 1;
            if index == self.cap {
                return None;
            }
        }
       if *key == self.pairs[index].key {
            return Some(&mut self.pairs[index]);
        }

        return None;
    }

    fn delete(&mut self, key: &Key) -> bool {
        if let Some(mut cell) = self.get_cell_mut(key) {
            *cell = Cell::new();            
            return true;    
        }

        return false;
    }
    
    fn contains(&mut self, key: Key) -> bool{
        if let Some(val) = self.get(&key) {
            return true;
        }

        return false;
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
    let mut table: HashTable<String, String> = HashTable::new_with_cap(32);


    table.insert("USA".to_string(), "New York.".to_string());
    table.insert("Japan".to_string(), "Tokyo.".to_string());
    table.insert("England".to_string(), "London.".to_string());
    
    println!("Keys");
    table.display_keys();
    println!("values.");

    println!("values.");
    table.display_values();
}

