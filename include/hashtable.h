#ifndef HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define CAP 64

typedef struct Cell {
	char *key;
	int  value;
	bool taken;
} Cell;

typedef struct HashTable {
	Cell *cells;
	size_t size;
	size_t cap;
} HashTable;

unsigned long djb2_hash(unsigned char *key);
void expand_table(HashTable *self) ;
void fill_cells(Cell *cells, size_t size) ;
bool get(HashTable *self, char *key, Cell *bucket);
bool contains(HashTable *self, char *key);
bool insert(HashTable *self, char *key, int value);
HashTable *new_hash_table(void);
char **TD_alloc(size_t size);
char **keys(HashTable *self);
int *values(HashTable *self);
void display_cells(HashTable *table);
void display_keys(HashTable *self) ;
void display_values(HashTable *self) ;
#endif // !HASH_TABLE_H
