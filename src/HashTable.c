#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CAP 10
// f, No generics in C so I probably need to make the same struct for every type I need hh...
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

// Hash func.
size_t hash(char *key) {
	
	size_t hash_ = 5381;
	for(;*key != '\0';*key++)
	{
		hash_ = ((hash_ << 5) + hash_) + (size_t) *key;
	}

	return hash_;
}

void expand_table(HashTable *self) 
{
	Cell *cells = malloc(sizeof(Cell) * (self->cap + CAP)); // Allocate 10 more cells in the heap.

														  
	for(size_t i = 0; i < self->cap; i++)
	{
		cells[i] = *(self->Cells + i);
	}
	
	self->Cells = cells;
	self->cap += CAP;

}

void fill_cells(Cell *cells, size_t size) 
{
	for(size_t n = 0; n < size; n++) 
	{
		Cell *cell = (cells + n);
		cell->key   = "";
		cell->value = 0;
		cell->taken = false;
	}
}

bool get(HashTable *self, char *key, Cell *bucket) {
	
	size_t 	index  = hash(key) % self->cap;
	
	while(strcmp(key, self->Cells[index].key) != 0) {
		index++;

		if(index == self->cap)
		{
			return false;	
		}
	}

	if (strcmp(key, self->Cells[index].key ) == 0) {
		
		bucket->key   = key;
		bucket->value = self->Cells[index].value;
		bucket->taken = self->Cells[index].taken;

		return true;
	}

	return false;
}

bool contains(HashTable *self, char *key){
	
	size_t 	index  = hash(key) % self->cap;
	while(strcmp(key, self->Cells[index].key) != 0) {
		index++;

		if(index == self->cap)
			return false;	
		
	}

	if (strcmp(key, self->Cells[index].key ) == 0) 
		return true;

	return false;
}

bool insert(HashTable *self, char *key, int value)
{
	bool    exists = false;
	size_t 	index  = hash(key) % self->cap;

	while(self->Cells[index].taken)
	{
		if(strcmp(self->Cells[index].key, key) == 0)
		{
			exists = true;
			break;
		}

		index++;
	}

	if(index >= self->cap) {
		// TODO: expand the table.
		expand_table(self);
		return insert(self, key, value);
	}

	// mut now because it is a reference.
	Cell *cell = (self->Cells + index);

	if (!exists) {
		
		cell->key   = key;
		cell->value = value;
		cell->taken = true;
		self->size++;

		return true;
	}

	// if it exists we just change the value.
	cell->value = value;

}

HashTable *new_hash_table(void) {
	
	HashTable *table = malloc(sizeof(HashTable));
	Cell *cells      = malloc(sizeof(Cell) * CAP); // Allocate 10 cells in the stack.
	fill_cells(cells, CAP); // Fills cells with the diffult .

	table->size = 0;
	table->cap  = CAP;
	table->Cells  = cells;

	return table;
}

char **TD_alloc(size_t size)
{
	char **TD = (char**) calloc(size, sizeof(char*));

	for(size_t i = 0; i < size; i++)
		TD[i] = (char *) calloc(128, 1);	

	return TD;
}

char **keys(HashTable *self) 
{
	char **ks = TD_alloc(self->size);
	
	
	for(size_t n = 0, it = 0; n < self->cap; n++)
	{
		if(self->Cells[n].taken)
			ks[it++] = self->Cells[n].key;
	}
	
	return ks;
}

int *values(HashTable *self) 
{
	int *vs = (int *) calloc(self->size, sizeof(int));


	
	for(size_t n = 0, it = 0; n < self->cap; n++)
	{
		if(self->Cells[n].taken)
			vs[it++] = self->Cells[n].value;	
	}

	return vs;
}

void display_cells(HashTable *table) {
	// Fails here..
	for(size_t i = 0; i < table->cap; i++)
	{
		Cell cell = table->Cells[i];
		printf("%i  -> (%s, %i, %i)\n", i, cell.key, cell.value, cell.taken);
	}
}

void display_keys(HashTable *self) 
{
	char **ks = keys(self);
	for(size_t i = 0; i < self->size; i++)
	{
		printf("%s\n", ks[i]);
	}
}

void display_values(HashTable *self) 
{
	int *vs = values(self);
	
	for(size_t i = 0; i < self->size; i++)
	{
		printf("%i\n", vs[i]);
	}
}

int main() {
	
	HashTable *table = new_hash_table();
	
	insert(table, "New York", 70);
	insert(table, "London", 10);
	insert(table, "Casablanca", 400);
	
	Cell c = { 0 };

	
	if(get(table, "New York", &c)) {
		printf("Val: %i\n", c.value);

	}
	
	if(get(table, "Casablanca", &c)) {
		printf("Val: %i\n", c.value);

	}


	return 0;

}



