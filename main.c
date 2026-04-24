#include "macro.h"


// Ordem de dados -> nome, calorias, proteina, carboidrato, gordura

int main() {
    const char* db_txt = "database.txt";
    db* database = create_database();
    read_txt_to_database(database, db_txt);

    int running = 1;
    while (running) {
        printf(
            "\n------------------------------------\n"
            "Macro Database Menu:\n"
            "1. List all macros\n"
            "2. Add macro\n"
            "3. Update macro\n"
            "4. Delete macro\n"
            "5. Show macro by name\n"
            "6. Meal calculator\n"
            "7. Day use (Loop for n meals)\n"
            "0. Exit\n"
            "------------------------------------\n"
            "Choose an option: "
        );

        int option = -1;
        scanf("%d", &option);
        getchar(); // consume newline

        switch (option) {
            case 1: {
                print_all_macros(database);
                break;
            }
            case 2: {
                char name[50];
                float calories, protein, carbo, fat;
                printf("Enter name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Enter calories: ");
                scanf("%f", &calories);
                printf("Enter protein: ");
                scanf("%f", &protein);
                printf("Enter carbohydrates: ");
                scanf("%f", &carbo);
                printf("Enter fat: ");
                scanf("%f", &fat);
                getchar(); // consume newline
                macro_str macro = add_macro(name, calories, protein, carbo, fat);
                if (add_macro_to_database(database, macro) == 0) {
                    printf("Macro added successfully.\n");
                } else {
                    printf("Failed to add macro.\n");
                }
                break;
            }
            case 3: {
                char name[50];
                float calories, protein, carbo, fat;
                printf("Enter name of macro to update: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Enter new calories: ");
                scanf("%f", &calories);
                printf("Enter new protein: ");
                scanf("%f", &protein);
                printf("Enter new carbohydrates: ");
                scanf("%f", &carbo);
                printf("Enter new fat: ");
                scanf("%f", &fat);
                getchar(); // consume newline
                macro_str macro = add_macro(name, calories, protein, carbo, fat);
                if (update_macro_in_database(database, name, macro) == 0) {
                    printf("Macro updated successfully.\n");
                } else {
                    printf("Macro not found.\n");
                }
                break;
            }
            case 4: {
                char name[50];
                printf("Enter name of macro to delete: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                if (delete_macro_from_database(database, name) == 0) {
                    printf("Macro deleted successfully.\n");
                } else {
                    printf("Macro not found.\n");
                }
                break;
            }
            case 5: {
                char name[50];
                printf("Enter name of macro to show: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                print_macro_by_name_smart(name, database);
                break;
            }
            case 6: {
                printf("Selected meal option.\n");
                meal(database);
                char input[100];
                fgets(input, sizeof(input), stdin);
                break;
            }

            case 7: {
                printf("Day use selected!\n");
                day_macro(database);
                char input[100];
                fgets(input, sizeof(input), stdin);
                break;
            }
            case 0:
                running = 0;
                break;
            default:
                printf("Invalid option. Try again.\n");
                break;
        }
    }

    free_database(database, db_txt);
    return 0;
}