#include <hashtable.h>

// TESTS
int main()
{
	Cell c = { 0 };
	HashTable *table = new_hash_table();
	insert(table, "New York", 70);
	insert(table, "London", 10);
	insert(table, "Casablanca", 400);
	get(table, *iter, &c);
	/*char **keys_ = keys(table);*/

	/*for (char **iter = keys_; (*iter != NULL); iter++)*/
	/*{*/
	/*	if(get(table, *iter, &c))*/
	/*		printf("Val: %i\n", c.value);*/
	/*	free(*iter);*/
	/*}*/
	/*free(keys_);*/
	return 0;
}
