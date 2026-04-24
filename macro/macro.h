#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifndef MACRO_H
#define MACRO_H

typedef struct macro_nutri {
    char name[50];
    float calories;
    float protein;
    float carbo;
    float fat;
} macro_str;


typedef struct database {
    macro_str* macros;
    int count;      // current number of macros
    int capacity;   // allocated size
} db;


// database functions
db* create_database();
void free_database(db* database, const char* filename);
void read_txt_to_database(db* database, const char* filename);


// aux functions
macro_str add_macro(const char* name, float calories, float protein, float carbo, float fat);
macro_str* get_macro_by_name(db* database, const char* name);
int add_macro_to_database(db* database, macro_str macro);
int calc_macro(db* database, const char* name, float quantity, macro_str* out_macro);
int strcasestr_simple(const char* haystack, const char* needle);
int find_similar_macros(db* database, const char* query, int* out_indices, int max_results);


// CRUD
int update_macro_in_database(db* database, const char* name, macro_str new_macro);
int delete_macro_from_database(db* database, const char* name);
void print_all_macros(db* database);


// main functions
void print_macro_by_name_smart(const char* name, db* database);
macro_str meal(db* database);
void day_macro(db* database);    


#endif