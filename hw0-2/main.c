#include "list.h"
#include "hash.h"
#include "bitmap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct list_item{
	struct list_elem elem;
	int data;
};
struct list lists[30];

struct hash_item{
	struct hash_elem elem;
	int data;
};
struct hash hashes[30];

struct bitmap* bitmaps[10];

void menu(int number, char* input);
void printError();
bool list_less(const struct list_elem *a, const struct list_elem *b, void* aux);
void list_swap(struct list_elem* a, struct list_elem* b);
bool hash_less(const struct hash_elem *a, const struct hash_elem *b, void* aux);
unsigned hash_func(const struct hash_elem* a, void* aux);
void hash_square(struct hash_elem* a, void* aux);
void hash_triple(struct hash_elem* a, void* aux);
void hash_destructor(struct hash_elem* a, void* aux);
struct bitmap* bitmap_expand(struct bitmap* bitmap, int size);
void list_shuffle(struct list* list);
unsigned hash_int_2(int i);

int main(void){
	char input[256]={0,}, command[128] = {0,};
	int commandNumber;
	while(1){
		commandNumber = -1;
		fgets(input, sizeof(input), stdin);
		sscanf(input, "%s", command);
		if(!strcmp(command, "create")) {
			commandNumber = 0; menu(commandNumber, input); 
		}
		else if(!strcmp(command, "dumpdata")){
			commandNumber = 1; menu(commandNumber, input);
		}
		else if(!strcmp(command, "delete")){
			commandNumber = 2; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_push_back")){
			commandNumber = 101; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_back")){
			commandNumber = 102; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_pop_back")){
			commandNumber = 103; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_front")){
			commandNumber = 104; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_insert")){
			commandNumber = 105; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_insert_ordered")){
			commandNumber = 106; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_size")){			
			commandNumber = 107; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_max")){			
			commandNumber = 108; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_empty")){			
			commandNumber = 109; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_min")){			
			commandNumber = 110; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_pop_front")){		
			commandNumber = 111; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_push_front")){
			commandNumber = 112; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_remove")){
			commandNumber = 113; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_reverse")){
			commandNumber = 114; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_sort")){		
			commandNumber = 115; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_splice")){	
			commandNumber = 116; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_swap")){		
			commandNumber = 117; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_unique")){
			commandNumber = 118; menu(commandNumber, input);
		}
		else if(!strcmp(command, "list_shuffle")){
			commandNumber = 119; menu(commandNumber, input);
		}
		else if(!strcmp(command, "hash_insert")){	
			commandNumber = 201; menu(commandNumber, input);
		}
		else if(!strcmp(command, "hash_apply")){	
			commandNumber = 202; menu(commandNumber, input);
		}
		else if(!strcmp(command, "hash_delete")){	
			commandNumber = 203; menu(commandNumber, input);
		}
		else if(!strcmp(command, "hash_empty")){	
			commandNumber = 204; menu(commandNumber, input);
		}
		else if(!strcmp(command, "hash_size")){	
			commandNumber = 205; menu(commandNumber, input);
		}
		else if(!strcmp(command, "hash_clear")){
			commandNumber = 206; menu(commandNumber, input);
		}
		else if(!strcmp(command, "hash_find")){	
			commandNumber = 207; menu(commandNumber, input);
		}
		else if(!strcmp(command, "hash_replace")){
			commandNumber = 208; menu(commandNumber, input);
		}
		else if(!strcmp(command, "bitmap_mark")){	
			commandNumber = 301; menu(commandNumber, input);
		}
		else if(!strcmp(command, "bitmap_all")){	
			commandNumber = 302; menu(commandNumber, input);
		}
		else if(!strcmp(command, "bitmap_any")){	
			commandNumber = 303; menu(commandNumber, input);
		}
		else if(!strcmp(command, "bitmap_contains")){		
			commandNumber = 304; menu(commandNumber, input);
		}
		else if(!strcmp(command, "bitmap_count")){
			commandNumber = 305; menu(commandNumber, input);
		}
		else if(!strcmp(command, "bitmap_dump")){		
			commandNumber = 306; menu(commandNumber, input);
		}
		else if(!strcmp(command, "bitmap_expand")){		
			commandNumber = 307; menu(commandNumber, input);
		}
		else if(!strcmp(command, "bitmap_set_all")){		
			commandNumber = 308; menu(commandNumber, input);
		}
		else if(!strcmp(command, "bitmap_flip")){	
			commandNumber = 309; menu(commandNumber, input);
		}
		else if(!strcmp(command, "bitmap_none")){	
			commandNumber = 310; menu(commandNumber, input);
		}
		else if(!strcmp(command, "bitmap_reset")){	
			commandNumber = 311; menu(commandNumber, input);
		}
		else if(!strcmp(command, "bitmap_scan_and_flip")){	
			commandNumber = 312; menu(commandNumber, input);
		}
		else if(!strcmp(command, "bitmap_scan")){		
			commandNumber = 313; menu(commandNumber, input);
		}
		else if(!strcmp(command, "bitmap_set")){		
			commandNumber = 314; menu(commandNumber, input);
		}
		else if(!strcmp(command, "bitmap_set_multiple")){	
			commandNumber = 315; menu(commandNumber, input);
		}
		else if(!strcmp(command, "bitmap_size")){
			commandNumber = 316; menu(commandNumber, input);
		}
		else if(!strcmp(command, "bitmap_test")){		
			commandNumber = 317; menu(commandNumber, input);
		}
		else if(!strcmp(command, "quit"))	break;
		else	menu(commandNumber, input);
		
	}
	return 0;
}

// 101 ~ 119 : list
// 201 ~ 208 : hash
// 301 ~ 317 : bitmap
// -1 : error
void menu(int number, char* input){
	char *arg[10], *token, * hash_func_name;
	int argNum = 1, num, pos;
	struct list_elem* e1 = (struct list_elem*)malloc(sizeof(struct list_elem));
	struct list_elem* temp_elem, *temp_elem1, *temp_elem2;
	struct list_item* temp_item;
	struct hash_elem* h1 = (struct hash_elem*)malloc(sizeof(struct hash_elem));
	struct hash_item* temp_hash_item;
	struct hash_elem* temp_hash_elem;
	struct hash_iterator temp_hash_iterator;
	struct hash_item t;
	size_t temp, count;
	bool value;

	token = strtok(input, " ");
	while(token != NULL){
		token = strtok(NULL, " ");
		arg[argNum++] = token;
	}
	arg[argNum] = NULL;

	if(number == -1)	printError();
	else if( number < 10){
		if(number == 0){ //create
			if(!strcmp(arg[1], "list")){
				num = atoi(&arg[2][4]);
				list_init(&lists[num]);
			}
			else if(!strcmp(arg[1], "hashtable")){
				num = atoi(&arg[2][4]);
				hash_init(&hashes[num], hash_func, hash_less, NULL);
			}
			else if(!strcmp(arg[1], "bitmap")){
				num = atoi(&arg[2][2]);
				count = atoi(&arg[3][0]);
				bitmaps[num] = bitmap_create(count);
			}
		}
		else if(number == 1){ //dumpdata
			if(strstr(arg[1], "list")){
				num = atoi(&arg[1][4]);
				
				for(temp_elem = list_begin(&lists[num]); temp_elem != list_end(&lists[num]); temp_elem = list_next(temp_elem)){
					temp_item = list_entry(temp_elem, struct list_item, elem);
					printf("%d ", temp_item->data);
				}
				if(!list_empty(&lists[num])) puts("");
			}
			else if(strstr(arg[1], "hash")){
				num = atoi(&arg[1][4]);
				hash_first(&temp_hash_iterator, &hashes[num]);
				for( ; hash_next(&temp_hash_iterator); ){
					temp_hash_item = hash_entry(hash_cur(&temp_hash_iterator), struct hash_item, elem);
					printf("%d ", temp_hash_item->data);
				}
				if(!hash_empty(&hashes[num]))	printf("\n");
			}
			else if(strstr(arg[1], "bm")){
				num = atoi(&arg[1][2]);
				count = bitmap_size(bitmaps[num]);
				for(temp = 0; temp < count; temp++)	printf("%d", bitmap_test(bitmaps[num], temp));
				puts("");
			}
		}
		else if(number == 2){ //delete
			if(strstr(arg[1], "list")){
				num = atoi(&arg[1][4]);

				for(temp_elem = list_begin(&lists[num]); temp_elem != list_end(&lists[num]); temp_elem = list_remove(temp_elem));
				list_init(&lists[num]);
			}
			else if(strstr(arg[1], "hash")){
				num = atoi(&arg[1][4]);
				hash_clear(&hashes[num], hash_destructor);
			}
			else if(strstr(arg[1], "bm")){
				num = atoi(&arg[1][2]);
				bitmap_destroy(bitmaps[num]);
			}
		}
	}
	else if(101 <= number && number <= 119){ //list
		if(number == 101){ //list_push_back
			temp_item = list_entry(e1, struct list_item, elem);
			temp_item->data = atoi(&arg[2][0]);

			num = atoi(&arg[1][4]);
			list_push_back(&lists[num], e1);
		}
		else if(number == 102){ //list_back
			num = atoi(&arg[1][4]);
			temp_elem = list_back(&lists[num]);
			temp_item = list_entry(temp_elem, struct list_item, elem);
			printf("%d\n", temp_item->data);
		}
		else if(number == 103){ //list_pop_back
			num = atoi(&arg[1][4]);
			temp_elem = list_pop_back(&lists[num]);
		}
		else if(number == 104){ //list_front
			num = atoi(&arg[1][4]);
			temp_elem = list_front(&lists[num]);
			temp_item = list_entry(temp_elem, struct list_item, elem);
			printf("%d\n", temp_item->data);
		}
		else if(number == 105){ //list_insert
			temp_item = list_entry(e1, struct list_item, elem);	
			temp_item->data = atoi(&arg[3][0]);
			
			num = atoi(&arg[1][4]);
			pos = atoi(&arg[2][0]);
		
			temp_elem = list_begin(&lists[num]);
			while(pos-- > 0)	temp_elem = list_next(temp_elem);
			list_insert(temp_elem, e1);
		}
		else if(number == 106){ //list_insert_ordered
			num = atoi(&arg[1][4]);
			temp_item = list_entry(e1, struct list_item, elem);
			temp_item->data = atoi(&arg[2][0]);
			list_insert_ordered(&lists[num], e1, list_less, NULL);
		}
		else if(number == 107){ //list_size
			num = atoi(&arg[1][4]);
			temp = list_size(&lists[num]);
			printf("%zu\n", temp);
		}
		else if(number == 108){ //list_max
			num = atoi(&arg[1][4]);
			
			temp_elem = list_max(&lists[num], list_less, NULL);	
			
			temp_item = list_entry(temp_elem, struct list_item, elem);
			printf("%d\n", temp_item->data);
		}
		else if(number == 109){ //list_empty
			num = atoi(&arg[1][4]);
			temp = list_empty(&lists[num]);
			if(temp == 0)	printf("false\n");
			else printf("true\n");
		}
		else if(number == 110){ //list_min
			num = atoi(&arg[1][4]);

			temp_elem = list_min(&lists[num], list_less, NULL);
			temp_item = list_entry(temp_elem, struct list_item, elem);
			printf("%d\n", temp_item->data);
		}
		else if(number == 111){ //list_pop_front
			num = atoi(&arg[1][4]);
			temp_elem = list_pop_front(&lists[num]);
		}
		else if(number == 112){ //list_push_front
			temp_item = list_entry(e1, struct list_item, elem);
			temp_item->data = atoi(&arg[2][0]);

			num = atoi(&arg[1][4]);
			list_push_front(&lists[num], e1);
		}
		else if(number == 113){ //list_remove
			num = atoi(&arg[1][4]);
			pos = atoi(&arg[2][0]);

			temp_elem = list_begin(&lists[num]);
			while(pos-- > 0)	temp_elem = list_next(temp_elem);

			temp_elem = list_remove(temp_elem);
		}
		else if(number == 114){ //list_reverse
			num = atoi(&arg[1][4]);
			list_reverse(&lists[num]);
		}
		else if(number == 115){ //list_sort
			num = atoi(&arg[1][4]);
			list_sort(&lists[num], list_less, NULL);
		}
		else if(number == 116){ //list_splice
			num = atoi(&arg[1][4]);
			pos = atoi(&arg[2][0]);
			temp_elem = list_begin(&lists[num]);
			while(pos-- > 0)	temp_elem = list_next(temp_elem);

			num = atoi(&arg[3][4]);
			pos = atoi(&arg[4][0]);
			temp_elem1 = list_begin(&lists[num]);
			while(pos-- > 0)	temp_elem1 = list_next(temp_elem1);

			pos = atoi(&arg[5][0]);
			temp_elem2 = list_begin(&lists[num]);
			while(pos-- > 0)	temp_elem2 = list_next(temp_elem2);

			list_splice(temp_elem, temp_elem1, temp_elem2);
		}
		else if(number == 117){ //list_swap
			num = atoi(&arg[1][4]);
			pos = atoi(&arg[2][0]);
			temp_elem1 = list_begin(&lists[num]);
			while(pos-- > 0) temp_elem1 = list_next(temp_elem1);

			pos = atoi(&arg[3][0]);
			temp_elem2 = list_begin(&lists[num]);
			while(pos-- > 0) temp_elem2 = list_next(temp_elem2);

			list_swap(temp_elem1, temp_elem2);
		}
		else if(number == 118){ //list_unique
			num = atoi(&arg[1][4]);
			if(arg[2] == NULL)	list_unique(&lists[num], NULL, list_less, NULL);
			else list_unique(&lists[num], &lists[atoi(&arg[2][4])], list_less, NULL);
		}
		else if(number == 119){ //list_shuffle 
			num = atoi(&arg[1][4]);
			list_shuffle(&lists[num]);
		}
	}
	else if(201 <= number && number <= 208){ //hash
		if(number == 201){ //hash_insert
			temp_hash_item = hash_entry(h1, struct hash_item, elem);
			temp_hash_item->data = atoi(&arg[2][0]);
			num = atoi(&arg[1][4]);
			temp_hash_elem = hash_insert(&hashes[num], h1);
		}
		else if(number == 202){ //hash_apply
			num = atoi(&arg[1][4]);
			hash_func_name = arg[2];
			if(strstr(hash_func_name, "square")){
				hash_apply(&hashes[num], hash_square);
			}
			else if(strstr(hash_func_name, "triple")){
				hash_apply(&hashes[num], hash_triple);
			}
		}
		else if(number == 203){ //hash_delete
			num = atoi(&arg[1][4]);
			t.data = atoi(&arg[2][0]);
			temp_hash_elem = hash_find(&hashes[num], &(t.elem));
			
			if(temp_hash_elem != NULL ) hash_delete(&hashes[num], temp_hash_elem);
		}
		else if(number == 204){ //hash_empty
			num = atoi(&arg[1][4]);
			if(hash_empty(&hashes[num]))	printf("true\n");
			else printf("false\n");
		}
		else if(number == 205){ //hash_size
			num = atoi(&arg[1][4]);
			printf("%zu\n", hash_size(&hashes[num]));
		}
		else if(number == 206){ //hash_clear
			num = atoi(&arg[1][4]);
			hash_clear(&hashes[num], hash_destructor);
		}
		else if(number == 207){ //hash_find
			num = atoi(&arg[1][4]);
			t.data = atoi(&arg[2][0]);
			temp_hash_elem = hash_find(&hashes[num], &(t.elem));
			if(temp_hash_elem != NULL)	printf("%d\n", hash_entry(temp_hash_elem, struct hash_item, elem)->data);
		}
		else if(number == 208){ //hash_replace
			num = atoi(&arg[1][4]);
			temp_hash_item = hash_entry(h1, struct hash_item, elem);
			temp_hash_item->data = atoi(&arg[2][0]);

			hash_replace(&hashes[num], h1);

		}
	} 
	else if(301 <= number && number <= 317){ //bitmap
		if(number == 301){ //bitmap_mark
			num = atoi(&arg[1][2]);
			temp = atoi(&arg[2][0]);

			bitmap_set(bitmaps[num], temp, true);
		}
		else if(number == 302){ //bitmap_all
			num = atoi(&arg[1][2]);
			temp = atoi(&arg[2][0]);
			count = atoi(&arg[3][0]);
			if(bitmap_all(bitmaps[num], temp, count)) printf("true\n");
			else printf("false\n");
		}
		else if(number == 303){ //bitmap_any
			num = atoi(&arg[1][2]);
			temp = atoi(&arg[2][0]);
			count = atoi(&arg[3][0]);
			if(bitmap_any(bitmaps[num], temp, count)) printf("true\n");
			else printf("false\n");
		}
		else if(number == 304){ //bitamp_contains
			num = atoi(&arg[1][2]);
			temp = atoi(&arg[2][0]);
			count = atoi(&arg[3][0]);

			if(strstr(arg[4], "true") != NULL){
				if(bitmap_contains(bitmaps[num], temp, count, true) == true)	printf("true\n");
				else	printf("false\n");
			}
			else{
				if(bitmap_contains(bitmaps[num], temp, count, false) == false)	printf("false\n");
				else	printf("true\n");
			}
		}	
		else if(number == 305){ //bitmap_count
			num = atoi(&arg[1][2]);
			temp = atoi(&arg[2][0]);
			count = atoi(&arg[3][0]);
			if(strstr(arg[4], "true") != NULL) printf("%zu\n", bitmap_count(bitmaps[num], temp, count, true));
			else  printf("%zu\n", bitmap_count(bitmaps[num], temp, count, false));
		}
		else if(number == 306){ //bitmap_dump
			num = atoi(&arg[1][2]);
			bitmap_dump(bitmaps[num]);
		}
		else if(number == 307){ //bitmap_expand
			num = atoi(&arg[1][2]);
			temp = atoi(&arg[2][0]);
			bitmaps[num] = bitmap_expand(bitmaps[num], temp);
		}
		else if(number == 308){ //bitmap_set_all
			num = atoi(&arg[1][2]);
			if(strstr(arg[2], "true") != NULL)	bitmap_set_all(bitmaps[num], true);
			else bitmap_set_all(bitmaps[num], false);
		}
		else if(number == 309){ //bitmap_flip
			num = atoi(&arg[1][2]);
			temp = atoi(&arg[2][0]);

			bitmap_flip(bitmaps[num], temp);
		}
		else if(number == 310){ //bitmap_none
			num = atoi(&arg[1][2]);
			temp = atoi(&arg[2][0]);
			count = atoi(&arg[3][0]);

			if(bitmap_none(bitmaps[num], temp, count)) printf("true\n");
			else printf("false\n");
		}
		else if(number == 311){ //bitmap_reset
			num = atoi(&arg[1][2]);
			temp = atoi(&arg[2][0]);

			bitmap_reset(bitmaps[num], temp);
		}
		else if(number == 312){ //bitmap_scan_and_flip
			num = atoi(&arg[1][2]);
			temp = atoi(&arg[2][0]);
			count = atoi(&arg[3][0]);

			if(strstr(arg[4], "true") != NULL)	value = true;
			else value = false;

			printf("%u\n", (unsigned int)bitmap_scan_and_flip(bitmaps[num], temp, count, value));
		}
		else if(number == 313){ //bitmap_scan
			num = atoi(&arg[1][2]);
			temp = atoi(&arg[2][0]);
			count = atoi(&arg[3][0]);
			
			if(strstr(arg[4], "true")!=NULL) printf("%u\n",(unsigned int) bitmap_scan(bitmaps[num], temp, count, true));
			else printf("%u\n", (unsigned int)bitmap_scan(bitmaps[num], temp, count, false));
		} 
		else if(number == 314){ //bitmap_set
			num = atoi(&arg[1][2]);
			temp = atoi(&arg[2][0]);
			if(strstr(arg[3], "true") != NULL) value = true;
			else value = false;
			bitmap_set(bitmaps[num], temp, value);
		}	
		else if(number == 315){ //bitmap_set_multiple
			num = atoi(&arg[1][2]);
			temp = atoi(&arg[2][0]);
			count = atoi(&arg[3][0]);
			if(strstr(arg[4], "true") != NULL) value = true;
			else value = false;

			bitmap_set_multiple(bitmaps[num], temp, count, value);
		}
		else if(number == 316){ //bitmap_size
			num = atoi(&arg[1][2]);
			printf("%zu\n", bitmap_size(bitmaps[num]));
		}
		else if(number == 317){ //bitmap_test
			num = atoi(&arg[1][2]);
			temp = atoi(&arg[2][0]);
			if(bitmap_test(bitmaps[num], temp))	printf("true\n");
			else printf("false\n");
		}
	}
}

void printError(){
	printf("Wrong command!\n");
}


bool list_less(const struct list_elem *a, const struct list_elem *b, void* aux){
	struct list_item* t1, *t2;

	t1 = list_entry(a, struct list_item, elem);
	t2 = list_entry(b, struct list_item, elem);
	return (t1->data) < (t2->data);
}

void list_swap(struct list_elem* a, struct list_elem* b){
	struct list_item* item1 = list_entry(a, struct list_item, elem);
	struct list_item* item2 = list_entry(b, struct list_item, elem);
	int temp;

	temp = item1->data;
	item1->data = item2->data;
	item2->data = temp;
}

bool hash_less(const struct hash_elem* a, const struct hash_elem* b, void* aux){
	struct hash_item* item1 = hash_entry(a, struct hash_item, elem);
	struct hash_item* item2 = hash_entry(b, struct hash_item, elem);

	return (item1->data) < (item2->data);
}

unsigned hash_func(const struct hash_elem* a, void* aux){
	return hash_int((hash_entry(a, struct hash_item, elem))->data);
}

void hash_square(struct hash_elem* a, void *aux){
	int data;
	struct hash_item* item = hash_entry(a, struct hash_item, elem);
	data = item->data;
	item->data = data*data;
}

void hash_triple(struct hash_elem* a, void* aux){
	int data;
	struct hash_item* item = hash_entry(a, struct hash_item, elem);
	data = item->data;
	item->data = data*data*data;
}

void hash_destructor(struct hash_elem* a, void* aux){
	struct hash_item* item = hash_entry(a, struct hash_item, elem);
	free(item);
}

struct bitmap* bitmap_expand(struct bitmap* bitmap, int size){
	size_t temp_size, i;
	struct bitmap* temp;

	temp = bitmap_create(bitmap_size(bitmap) + (size_t)size);
	
	if(size < 0 || size > 65536) return NULL;

	for(i = 0; i < (int)bitmap_size(bitmap); i++){
		if(bitmap_test(bitmap, i) == true)	bitmap_mark(temp, i);
	}

	return temp;
}
void list_shuffle(struct list* list){
	struct list_elem *e1, *e2;
	int i = list_size(list), j;

	srand(time(NULL));
	for(e1 = list_begin(list); e1 != list_end(list); e1 = list_next(e1)){
		j = rand() % (i + 1);
		e2 = list_begin(list);
		while(j-- > 0)	e2 = list_next(e2);
		list_swap(e1, e2);
		i--;
	}
}

unsigned hash_int_2(int i){
	i = (i*256) % 13;
	return hash_bytes(&i, sizeof i);
}
