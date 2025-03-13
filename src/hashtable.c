#include <hashtable.h>

unsigned long djb2_hash(unsigned char *key)
{
	unsigned long hash_ = 5381;
	int c;
	while ((c = *key++))
		hash_ = ((hash_ << 5) + hash_) + c;
	return hash_;
}

void expand_table(HashTable *self) 
{
	self->cells = realloc(self->cells, self->cap * 2 * self->cells[0]);
	self->cap *= 2;
}

bool get(HashTable *self, char *key, Cell *bucket)
{
	
	size_t 	index = djb2_hash((unsigned char *)key) % self->cap;
	while(strcmp(key, self->cells[index].key) != 0) {
		index++;
		if(index == self->cap)
			return false;	
	}
	if (strcmp(key, self->cells[index].key ) == 0) {
		bucket->key   = key;
		bucket->value = self->cells[index].value;
		bucket->taken = self->cells[index].taken;
		return true;
	}
	return false;
}

bool contains(HashTable *self, char *key)
{
	
	size_t 	index  = djb2_hash((unsigned char *)key) % self->cap;
	while(strcmp(key, self->cells[index].key) != 0) {
		index++;

		if(index == self->cap)
			return false;	
		
	}
	if (strcmp(key, self->cells[index].key ) == 0) 
		return true;
	return false;
}

bool insert(HashTable *self, char *key, int value)
{
	bool    exists = false;
	Cell    *cell;
	size_t 	index  = djb2_hash((unsigned char *)key) % self->cap;

	while(self->cells[index].taken)
	{
		if(strcmp(self->cells[index].key, key) == 0)
		{
			exists = true;
			break;
		}

		index++;
		if (index >= self->cap)
			expand_table(self);
	}

	if(index >= self->cap)
		expand_table(self);
	cell = (self->cells + index);
	if (!exists) {
		
		cell->key   = strdup(key);
		cell->value = value;
		cell->taken = true;
		self->size++;
	} else
		cell->value = value;
	return true;
}

HashTable *new_hash_table(void)
{
	HashTable *table = calloc(1, sizeof(*table));
	if (!table)
		return (NULL);
	table->cells = calloc(CAP, sizeof(table->cells[0]));
	if (!table->cells)
	{
		free(table);
		return (NULL);
	}
	table->size = 0;
	table->cap  = CAP;
	return (table);
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
	char **ks = TD_alloc(self->size + 1);
	size_t it = 0;

	for(size_t n = 0; n < self->cap; n++)
	{
		if(self->cells[n].taken)
			ks[it++] = self->cells[n].key;
	}
	ks[it++] = NULL;
	return (ks);
}

int *values(HashTable *self) 
{
	int *vs = (int *) calloc(self->size, sizeof(int));
	for(size_t n = 0, it = 0; n < self->cap; n++)
	{
		if(self->cells[n].taken)
			vs[it++] = self->cells[n].value;	
	}
	return vs;
}

void display_cells(HashTable *table) {
	for(size_t i = 0; i < table->cap; i++)
	{
		Cell cell = table->cells[i];
		printf("%zu  -> (%s, %i, %i)\n", 
			i, cell.key, cell.value, cell.taken);
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
