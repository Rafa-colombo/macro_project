# Macro Nutritional Database

A command-line application for managing and calculating nutritional macronutrients (calories, protein, carbohydrates, and fat) of food items. Built in C with a persistent text-based database.

## Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Building](#building)
- [Running](#running)
- [Usage Guide](#usage-guide)
- [Database Format](#database-format)
- [API Documentation](#api-documentation)
- [Technical Details](#technical-details)

## Features

✨ **Core Functionality:**
- **CRUD Operations**: Create, Read, Update, and Delete food macros
- **Database Persistence**: Automatically saves data to `database.txt`
- **Dynamic Memory Management**: Automatically grows database capacity as needed
- **Smart Search**: Case-insensitive fuzzy search with suggestions for misspelled food names
- **Meal Calculator**: Calculate total macros for meals with multiple food items
- **Data Reference**: All nutritional values stored per 1 gram for accurate calculations

## Project Structure

```
macro/
├── main.c              # Main application entry point and menu system
├── macro.c             # Core database and macro management functions
├── macro.h             # Header file with struct definitions and function declarations
├── database.txt        # Persistent database file (food name, calories, protein, carbs, fat)
├── populate\populateDB.c        # Utility to populate database with initial food items
├── gcc.bat             # Windows batch script for compilation with GCC
├── run.exe             # Compiled executable (Windows)
├── .gitignore          # Git ignore file for compiled binaries and temporary files
└── README.md           # This file
```

## Requirements

- **C Compiler**: GCC or compatible C99 compiler
- **Platform**: Windows (with gcc) or any UNIX-like system with make/gcc
- **Memory**: Minimal (~100KB base + dynamic allocation for food items)

## Building

The application is pre-compiled and ready to use. If you need to rebuild from source:

### On Windows (using gcc.bat):

```bash
.\gcc macro.c macro.h main.c -o run.exe
```

### On Linux/macOS:

```bash
gcc -std=c99 -Wall -Wextra macro.c macro.h main.c -o run
```

### Compiling populateDB.c (to populate initial database):

```bash
# Windows
.\gcc populateDB.c -o populate.exe
.\populate.exe

# Linux/macOS
gcc populateDB.c -o populate
./populate
```

## Running

Simply execute the pre-compiled executable:

### On Windows:

```bash
run.exe
```

Or double-click `run.exe` in Windows Explorer.

### On Linux/macOS:

```bash
./run
```

The application will:
1. Load existing data from `database.txt` if it exists
2. Display the main menu
3. Accept user input for menu selection

## Database Population

### Using populateDB.c

The `populateDB.c` utility allows you to quickly populate the database with a predefined set of food items (56 Brazilian foods) for testing and initial setup. This is much faster than manually adding each food one by one.

**When to use:**
- First-time setup to get a working database with sample foods
- Testing the application with a complete dataset
- Resetting database to default foods

**Compilation:**

```bash
# Windows
.\gcc populateDB.c -o populate.exe

# Linux/macOS
gcc populateDB.c -o populate
```

**Usage:**

```bash
# Windows
.\populate.exe

# Linux/macOS
./populate
```

**What it does:**
- Reads food data from the `populateDB.c` source code
- Appends all items to `database.txt` in CSV format
- Creates `database.txt` if it doesn't exist
- Prints confirmation message with number of items added

**Output:**
```
Database populated with 56 new macros.
```

**Note:** Running `populate` multiple times will **append** items, potentially creating duplicates. To reset:
1. Delete or backup `database.txt`
2. Run `populate` again to create a fresh database

## Usage Guide

### Main Menu Options

```
1. List all macros
   - Displays all food items in the database with their nutritional values
   - Shows: name, calories, protein, carbohydrates, fat (all per 1g)

2. Add macro
   - Add a new food item to the database
   - Requires: name, calories, protein, carbs, fat per 1g
   - Values are automatically saved to database.txt

3. Update macro
   - Modify an existing food item's nutritional values
   - Enter the food name and new values

4. Delete macro
   - Remove a food item from the database
   - Enter the food name to delete

5. Show macro by name
   - Display details of a specific food item
   - Features smart search: if exact match not found, shows similar options
   - User can select from suggested matches

6. Meal calculator
   - Calculate total macros for a meal with multiple items
   - Steps:
     a. Enter number of foods in the meal
     b. For each food:
        - Enter food name (with smart search suggestions)
        - Enter quantity in grams
     c. Display calculated macros for each item
     d. View total meal composition

0. Exit
   - Save all changes and exit the application
```

### Smart Search Feature

When you enter a food name that doesn't exactly match:
1. App searches for similar items (case-insensitive substring matching)
2. Shows numbered list of suggestions
3. Enter the number to select a food
4. Enter 0 to cancel

**Example:**
```
Enter name of macro to show: banana
Macro not found. Did you mean:
1. Banana Prata
2. Maçã
Enter the number of the macro to select (0 to cancel): 1
```

## Database Format

### File: `database.txt`

Plain text file with comma-separated values. Each line represents one food item:

```
[name],[calories],[protein],[carbs],[fat]
```

**Important**: All nutritional values are per **1 gram** for accurate portion-based calculations.

**Example entries:**
```
Frango Grelhado,1.59,0.32,0.00,0.025
Ovo Cozido,1.55,0.13,0.011,0.11
Arroz Integral,1.11,0.026,0.23,0.009
Banana Prata,0.89,0.013,0.23,0.003
```

### Loading Custom Database

Place a `database.txt` file in the application directory with your custom food items in the above format.

## API Documentation

### Core Data Structures

#### `macro_str`
```c
typedef struct macro_nutri {
    char name[50];        // Food name (max 49 chars)
    float calories;       // Per 1g
    float protein;        // Per 1g (grams)
    float carbo;          // Per 1g (grams)
    float fat;            // Per 1g (grams)
} macro_str;
```

#### `db`
```c
typedef struct database {
    macro_str* macros;    // Dynamic array of food items
    int count;            // Current number of items
    int capacity;         // Allocated capacity
} db;
```

### Key Functions

#### Database Management
- `db* create_database()` - Initialize an empty database
- `void free_database(db* database, const char* filename)` - Save and free all resources
- `void read_txt_to_database(db* database, const char* filename)` - Load foods from file

#### CRUD Operations
- `macro_str add_macro(...)` - Create new macro struct
- `int add_macro_to_database(db* database, macro_str macro)` - Add to database
- `macro_str* get_macro_by_name(db* database, const char* name)` - Retrieve by name
- `int update_macro_in_database(db* database, const char* name, macro_str new_macro)` - Update existing
- `int delete_macro_from_database(db* database, const char* name)` - Remove food item

#### Calculation & Display
- `int calc_macro(db* database, const char* name, float quantity, macro_str* out_macro)` - Calculate macros for given quantity
- `void print_all_macros(db* database)` - Display all foods
- `void print_macro_by_name_smart(char* name, db* database)` - Display with smart search
- `void meal(db* database)` - Multi-item meal calculator

#### Search
- `int find_similar_macros(db* database, const char* query, int* out_indices, int max_results)` - Fuzzy search
- `int strcasestr_simple(const char* haystack, const char* needle)` - Case-insensitive substring search

## Technical Details

### Memory Management

- **Dynamic Array**: Database uses dynamic allocation with automatic resizing
- **Capacity Doubling**: When full, capacity doubles (10 → 20 → 40 → ...)
- **Cleanup**: `free_database()` saves changes and releases all allocated memory

### Data Persistence

- Changes are automatically written to `database.txt` on exit
- File format is human-readable and can be edited manually
- On startup, database is loaded from file (or created empty if file doesn't exist)

### Calculation Reference

All macronutrient values in the database are stored **per 1 gram**. When calculating for a meal:

```
result = database_value × quantity_in_grams
```

**Example:**
```
Banana (0.89 cal/g) × 100g = 89 calories
Chicken (1.59 cal/g) × 150g = 238.5 calories
```

### Search Algorithm

**Smart Search Process:**
1. First attempts exact match using `strcmp()`
2. If not found, searches for case-insensitive substring matches
3. Returns up to 10 matches for user selection
4. User can interactively select the correct item

## Future Improvements

- [ ] Support for meal templates/favorites
- [ ] Nutritional goals tracking (daily intake goals)
- [ ] Export meal history to CSV
- [ ] Graphical user interface (GTK/SDL)
- [ ] Recipe builder (combine multiple meals)
- [ ] Barcode scanner integration
- [ ] Mobile app companion
- [ ] SQLite database backend (replace text file)

## Notes

- Ensure `database.txt` is in the same directory as the executable
- Maximum food name length: 49 characters
- Maximum foods in database: Limited only by available RAM
- Decimal precision: 2 decimal places displayed, float precision internally

## Author

Rafael Colombo Miranda

## License

MIT License - Feel free to use and modify

---

**Version**: 1.0  
**Last Updated**: April 2026
