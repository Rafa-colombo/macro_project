#include "macro.h"

// constructor database
db* create_database() {
    db* database = malloc(sizeof(db));
    if (database == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    database->count = 0;
    database->capacity = 10;
    database->macros = malloc(database->capacity * sizeof(macro_str));
    if (database->macros == NULL) {
        printf("Memory allocation error\n");
        free(database);
        exit(1);
    }
    return database;
}

void read_txt_to_database(db* database, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char name[50];
        float calories, protein, carbo, fat;
        if (sscanf(line, "%49[^,],%f,%f,%f,%f", name, &calories, &protein, &carbo, &fat) == 5) {
            macro_str macro = add_macro(name, calories, protein, carbo, fat);
            add_macro_to_database(database, macro);
        }
    }
    fclose(file);
}


void free_database(db* database, const char* filename) { // ensure the db is saved on .txt
    if (database) {
        // Save database to text file
        FILE* file = fopen(filename, "w");
        if (file) {
            for (int i = 0; i < database->count; i++) {
                fprintf(file, "%s,%.2f,%.2f,%.2f,%.2f\n",
                    database->macros[i].name,
                    database->macros[i].calories,
                    database->macros[i].protein,
                    database->macros[i].carbo,
                    database->macros[i].fat);
            }
            fclose(file);
        }
        free(database->macros);
        free(database);
    }
}


// Aux functions

// Create a macro_str struct from given values
macro_str add_macro(const char* name, float calories, float protein, float carbo, float fat) {
    macro_str macro;
    strncpy(macro.name, name, sizeof(macro.name) - 1);
    macro.name[sizeof(macro.name) - 1] = '\0'; // Ensure null-termination
    macro.calories = calories;
    macro.protein = protein;
    macro.carbo = carbo;
    macro.fat = fat;
    return macro;
}

// return id of macro in database or NULL if not found
macro_str* get_macro_by_name(db* database, const char* name) {
    for (int i = 0; i < database->count; i++) {
        if (strcmp(database->macros[i].name, name) == 0) {
            return &database->macros[i];
        }
    }
    return NULL; // Not found
}

// Add a macro to the database, resizing if necessary
int add_macro_to_database(db* database, macro_str macro) {
    if (database->count >= database->capacity) {
        int new_capacity = database->capacity * 2;
        macro_str* new_macros = realloc(database->macros, new_capacity * sizeof(macro_str));
        if (!new_macros) {
            printf("Memory allocation error while resizing database.\n");
            return -1;
        }
        database->macros = new_macros;
        database->capacity = new_capacity;
    }
    database->macros[database->count++] = macro;
    return 0; // Success
}

// Calculates macros for a given food and quantity
int calc_macro(db* database, const char* name, float quantity, macro_str* out_macro) {
    macro_str* macro = get_macro_by_name(database, name);
    if (macro && out_macro) {
        strncpy(out_macro->name, macro->name, sizeof(out_macro->name) - 1);
        out_macro->name[sizeof(out_macro->name) - 1] = '\0'; // Ensure null-termination
        out_macro->calories = macro->calories * quantity;
        out_macro->protein = macro->protein * quantity;
        out_macro->carbo = macro->carbo * quantity;
        out_macro->fat = macro->fat * quantity;
        return 0; // Success
    }
    return -1; // Not found or invalid output pointer
}

// Case-insensitive substring search helper
int strcasestr_simple(const char* haystack, const char* needle) {
    if (!*needle) return 1;
    size_t needle_len = strlen(needle);
    for (size_t i = 0; haystack[i]; i++) {
        if (strncasecmp(&haystack[i], needle, needle_len) == 0) {
            return 1;
        }
    }
    return 0;
}

// Smart search: find all similar macro names and mark the correct one
int find_similar_macros(db* database, const char* query, int* out_indices, int max_results) {
    int found = 0;

    for (int i = 0; i < database->count && found < max_results; i++) {
        if (strcasestr_simple(database->macros[i].name, query)) {
            out_indices[found++] = i;
        }
    }

    if (found == 0) return -1; // nothing similar found

    system("cls");
    printf("Macro not found. Did you mean:\n");
    for (int i = 0; i < found; i++) {
        printf("%d. %s\n", i + 1, database->macros[out_indices[i]].name);
    }
    printf("Enter the number of the macro to select (0 to cancel): ");

    int choice = 0;
    scanf("%d", &choice);
    getchar(); // consume newline

    if (choice < 1 || choice > found) return -1; // cancelled or invalid
    system("cls");
    return out_indices[choice - 1]; // return the actual database index
}

// CRUD functions

int update_macro_in_database(db* database, const char* name, macro_str new_macro) {
    macro_str* macro = get_macro_by_name(database, name);
    if (macro) {
        *macro = new_macro;
        return 0; // Success
    }
    return -1; // Not found
}

int delete_macro_from_database(db* database, const char* name) {
    for (int i = 0; i < database->count; i++) {
        if (strcmp(database->macros[i].name, name) == 0) {
            for (int j = i; j < database->count - 1; j++) {
                database->macros[j] = database->macros[j + 1];
            }
            database->count--;
            return 0; // Success
        }
    }
    return -1; // Not found
}

void print_all_macros(db* database) {
    printf("All macros in database:\n");
    for (int i = 0; i < database->count; i++) {
        printf("%s: %.2f kcal, %.2f g protein, %.2f g carbo, %.2f g fat\n",
            database->macros[i].name,
            database->macros[i].calories,
            database->macros[i].protein,
            database->macros[i].carbo,
            database->macros[i].fat);
    }
}


// main functions

macro_str meal(db* database) {
    float qnt_f;
    printf("Enter number of foods in meal: ");
    scanf("%f", &qnt_f);
    getchar();

    macro_str total = {"Total", 0, 0, 0, 0};
    for (int i = 0; i < (int)qnt_f; i++) {
        char line[256];
        while (1) {
            char input[256];
            printf("{%d} Enter name of food: ", i + 1);
            
            if (fgets(input, sizeof(input), stdin) == NULL) continue;
            input[strcspn(input, "\n")] = '\0'; // Limpa o \n do input

            macro_str* exact = get_macro_by_name(database, input);

            if (exact) {
                strncpy(line, input, sizeof(line) - 1);
                line[sizeof(line) - 1] = '\0';
                break; 
            }

            int indices[10];
            int chosen = find_similar_macros(database, input, indices, 10);
            
            if (chosen >= 0) {
                // Copia o nome oficial do banco de dados para 'line'
                strncpy(line, database->macros[chosen].name, sizeof(line) - 1);
                line[sizeof(line) - 1] = '\0';
                break;
            } else {
                printf("Macro not found: %s\n", input);
            }
        } 

            float qnt_g;
            printf("Enter quantity in grams: ");
            scanf("%f", &qnt_g);
            getchar();

            macro_str result;
            if (calc_macro(database, line, qnt_g, &result) == 0) {
                total.calories += result.calories;
                total.protein += result.protein;
                total.carbo += result.carbo;
                total.fat += result.fat;
                printf("For meal: Calories: %.2f kcal, Protein: %.2f g, Carbohydrates: %.2f g, Fat: %.2f g\n",
                    result.calories, result.protein, result.carbo, result.fat);
            }
    }
    printf("------------------------------------\n");
    printf("Total for the meal: Calories: %.2f kcal, Protein: %.2f g, Carbohydrates: %.2f g, Fat: %.2f g\n",
            total.calories, total.protein, total.carbo, total.fat); 
    printf("------------------------------------\n");
    return total;
}

void day_macro(db* database) {
    macro_str day = {"Day", 0, 0, 0, 0};

    while(1){
        int input;
        macro_str total = meal(database);

        day.calories += total.calories;
        day.protein += total.protein;
        day.carbo += total.carbo;
        day.fat += total.fat;

        printf("\nNew meal? 0/1: ");
        scanf("%d", &input);
        if (input == 0) break;
    }
    printf("------------------------------------\n");
    printf("Total for the day: Calories: %.2f kcal, Protein: %.2f g, Carbohydrates: %.2f g, Fat: %.2f g\n",
            day.calories, day.protein, day.carbo, day.fat); 
    printf("------------------------------------\n");
    return;
}

// Updated print_macro_by_name with smart search
void print_macro_by_name_smart(const char* name, db* database) {
    macro_str* macro = get_macro_by_name(database, name);
    if (macro) {
        printf("Name: %s\n",          macro->name);
        printf("Calories: %.2f\n",    macro->calories);
        printf("Protein: %.2f g\n",   macro->protein);
        printf("Carbohydrates: %.2f g\n", macro->carbo);
        printf("Fat: %.2f g\n",       macro->fat);
        return;
    }

    // Not found — search for similar
    int indices[10];
    int chosen = find_similar_macros(database, name, indices, 10);

    if (chosen >= 0) {
        system("cls");
        macro_str* sel = &database->macros[chosen];
        printf("Name: %s\n",          sel->name);
        printf("Calories: %.2f\n",    sel->calories);
        printf("Protein: %.2f g\n",   sel->protein);
        printf("Carbohydrates: %.2f g\n", sel->carbo);
        printf("Fat: %.2f g\n",       sel->fat);
    } else {
        printf("Macro not found or selection cancelled.\n");
    }
}