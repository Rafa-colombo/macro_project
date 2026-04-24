#include <stdio.h>

int main() {
    // Example macros to add
    const char* macros[][5] = {

    // PROTEINAS
    {"Frango Sassami", "1.20", "0.23", "0.0", "0.012"},
    {"Ovo Frito", "1.96", "0.13", "0.01", "0.15"},
    {"Carne Moida (Patinho)", "2.17", "0.26", "0.0", "0.12"},
    {"Carne Moida (Acem)", "2.50", "0.25", "0.0", "0.20"},
    {"Bife (Alcatra)", "2.40", "0.31", "0.0", "0.11"},
    {"Bife (Contra-file)", "2.80", "0.26", "0.0", "0.21"},

    // CARBOIDRATOS BASE
    {"Arroz Integral", "1.11", "0.026", "0.23", "0.009"},
    {"Arroz Branco", "1.30", "0.027", "0.28", "0.003"},
    {"Pao Integral 50%", "2.50", "0.09", "0.43", "0.04"},
    {"Aveia", "3.89", "0.17", "0.66", "0.07"},

    // LEGUMINOSAS
    {"Feijao Carioca", "0.76", "0.048", "0.136", "0.005"},
    {"Feijao Preto", "0.77", "0.045", "0.14", "0.005"},
    {"Lentilha", "1.16", "0.09", "0.20", "0.004"},

    // LATICINIOS E DERIVADOS
    {"Leite Desnatado", "0.35", "0.034", "0.05", "0.001"},
    {"Leite Integral", "0.61", "0.033", "0.048", "0.033"},
    {"Requeijao Light", "1.80", "0.08", "0.06", "0.14"},
    {"Queijo Minas", "2.43", "0.174", "0.032", "0.175"},
    {"Queijo Mussarela", "3.00", "0.22", "0.03", "0.22"},

    // GORDURAS / PASTAS
    {"Pasta de Amendoim Dr Peanut", "6.00", "0.25", "0.20", "0.50"},

    // VERDURAS
    {"Alface", "0.15", "0.014", "0.029", "0.002"},
    {"Tomate", "0.18", "0.009", "0.039", "0.002"},
    {"Cenoura", "0.41", "0.009", "0.096", "0.002"},
    {"Beterraba", "0.43", "0.016", "0.10", "0.002"},
    {"Repolho", "0.25", "0.013", "0.058", "0.001"},

    // FRUTAS
    {"Banana", "0.89", "0.011", "0.23", "0.003"},
    {"Maca", "0.52", "0.003", "0.14", "0.002"},
    {"Uva", "0.67", "0.006", "0.17", "0.004"},

    // JUNK
    {"Pizza", "2.66", "0.11", "0.33", "0.10"},
    {"Hamburguer", "2.95", "0.17", "0.30", "0.14"},
    {"Shawarma", "2.20", "0.15", "0.25", "0.08"},
    {"Pao de Queijo", "3.00", "0.06", "0.34", "0.18"},
    {"Salgado Assado", "2.80", "0.10", "0.35", "0.12"},

    // DOCES
    {"Chocolate Barra", "5.35", "0.07", "0.60", "0.30"},
    {"Mel", "3.04", "0.0", "0.82", "0.0"},

    // BEBIDAS
    {"Cafe Preto", "0.02", "0.003", "0.0", "0.0"}
};
    int n = sizeof(macros) / sizeof(macros[0]);

    FILE* file = fopen("../macro/database.txt", "a"); // Mudar para w se for refazer
    if (!file) {
        printf("Could not open database.txt for appending.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        fprintf(file, "%s,%s,%s,%s,%s\n", macros[i][0], macros[i][1], macros[i][2], macros[i][3], macros[i][4]);
    }
    fclose(file);
    printf("Database populated with %d new macros.\n", n);
    return 0;
}
