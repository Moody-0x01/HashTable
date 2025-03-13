
CAP = 10


def Hash(s: str) -> int:
    H = 5381

    for c in s:
        H = ((H << 5) + H) + ord(c)
    
    return H

class Cell:
    def __init__(self, K: any, V: any, taken: bool =False):
        self.key   = K
        self.value = V
        self.taken = taken
    
    def print_cell(self) -> None:
        print(f"({self.key}, {self.value}, {self.taken})")

    def new():
        return Cell("", 0)

class HashTable:
    def __init__(self, cells: list[Cell], cap: int):

        self.cells = cells
        self.cap   = cap
        self.size  = 0
    def expand(self):
        new = [Cell.new() for i in range(0, self.cap + CAP)]
        
        for i in range(0, self.cap):
            new[i] = self.cells[i]
        
        self.cells = new
        self.cap   = self.cap + CAP
        return True
    
    def get(self, k):
        index = Hash(k) % self.cap
        while self.cells[index].key != k and index < self.cap:
            index += 1

            if index == self.cap: return

        if k == self.cells[index].key: return self.cells[index].value

    def insert(self, k, v):
        exists: bool = False
        index = Hash(k) % self.cap

        while self.cells[index].taken:
            if k == self.cells[index].key:
                exists = True
                break
            
            index += 1
        
        if index >= self.cap:
            self.expand()
            self.insert(k, v)
        
        if not exists:
            self.cells[index] = Cell(k, v, True)
            self.size += 1
            return
        
        self.cells[index] = Cell(k, v, True)
        self.size += 1

    def print_cells(self):
        for i in range(0, self.cap): 
            self.cells[i].print_cell()

def make_hash_table(c: int = 0) -> HashTable:
    if c == 0: c = CAP
    cells = [Cell.new() for _ in range(0, CAP)]
    return HashTable(cells, CAP)


def main():
    h: HashTable = make_hash_table()
    h.insert("ahmed", 123)
    h.insert("Omar", 342)

    ahmed = h.get("ahmed")
    Omar  = h.get("Omar")
    h.print_cells()
    print("Ahmed ", ahmed)
    print("Omar ", Omar)

if __name__ == '__main__': main()

