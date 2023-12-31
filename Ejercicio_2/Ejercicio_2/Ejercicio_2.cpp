#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <omp.h>

int main() {
    char frase[] = "tres tristes tigres trigaban trigo por culpa del bolivar";
    char primera_parte[100] = "";
    char segunda_parte[100] = "";

    int longitud = strlen(frase);
    int inicio = 0;
    bool intercambiar = true;

#pragma omp parallel for
    for (int i = 0; i <= longitud; ++i) {
        if (frase[i] == ' ' || frase[i] == '\0') {
            frase[i] = '\0';
            if (intercambiar) {
#pragma omp critical
                {
                    strcat(primera_parte, &frase[inicio]);
                    strcat(primera_parte, " ");
                }
            }
            else {
#pragma omp critical
                {
                    strcat(segunda_parte, &frase[inicio]);
                    strcat(segunda_parte, " ");
                }
            }
            inicio = i + 1;
            intercambiar = !intercambiar;
        }
    }

    printf("Primera parte: %s\n", primera_parte);
    printf("Segunda parte: %s\n", segunda_parte);

    return 0;
}
