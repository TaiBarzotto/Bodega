#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include "Auxiliares.h"

int numero_inteiro_valido(const char *str) {
    char *endptr;
    strtol(str, &endptr, 10); 

    return *endptr == '\n' || *endptr == '\0';
}

int ler_inteiro(const char *mensagem) {
    int valor;
    char buffer[100];

    while (1) {
        printf("%s", mensagem);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (strcmp(buffer, "\n") == 0) {
                printf("Entrada vazia. Por favor, digite um numero inteiro.\n");
                continue; 
            }
            if (numero_inteiro_valido(buffer)) {
                valor = strtol(buffer, NULL, 10); // Converte a string para int
                return valor; 
            } else {  
                printf("Entrada invalida. Por favor, digite um numero inteiro.\n");
            }
        } else {
            printf("Erro ao ler a entrada. Tente novamente.\n");
        }
    }
}

int numero_valido(const char *str) {
    char *endptr;
    strtof(str, &endptr); 

    return *endptr == '\n' || *endptr == '\0';
}

float ler_float(const char *mensagem) {
    float valor;
    char buffer[100];

    while (1) {
        printf("%s", mensagem);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (strcmp(buffer, "\n") == 0) {
                printf("Entrada vazia. Por favor, digite um numero decimal.\n");
                continue; 
            }
            if (numero_valido(buffer)) {
                valor = strtof(buffer, NULL); 
                return valor; 
            } else {
                printf("Entrada invalida. Por favor, digite um numero decimal.\n");
            }
        } else {
            printf("Erro ao ler a entrada. Tente novamente.\n");
        }
    }
}

int formatarCPF(char *cpfEntrada, char *cpfFormatado) {
    int j = 0, opcao;

    for (int i = 0; cpfEntrada[i] != '\0'; i++) {
        if (isdigit(cpfEntrada[i])) {
            cpfFormatado[j++] = cpfEntrada[i];
        
        }
    }
    cpfFormatado[j] = '\0'; 

    if (j == 11) {
        // Formata o CPF
        snprintf(cpfFormatado, 15, "%c%c%c.%c%c%c.%c%c%c-%c%c",
                 cpfFormatado[0], cpfFormatado[1], cpfFormatado[2],
                 cpfFormatado[3], cpfFormatado[4], cpfFormatado[5],
                 cpfFormatado[6], cpfFormatado[7], cpfFormatado[8],
                 cpfFormatado[9], cpfFormatado[10]);
        return 2;
    } 
    while (getchar() != '\n'); 
    printf("CPF invalido\n");
    printf("0-SAIR\n");
    printf("1-DIGITAR CPF NOVAMENTE\n");
    opcao = ler_inteiro("");
    switch (opcao){
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            printf("Opcao invalida, retornando ao menu principal\n");
            return 0;
        }

}

int mensagem_erro_codigo(const char *mensagem){
    int opcao;
    printf("%s", mensagem);
    printf("0 - SAIR\n");
    printf("1 - DIGITAR OUTRO CODIGO\n");
    opcao = ler_inteiro("");
    switch (opcao) {
        case 0:
            printf("Voltando ao menu principal...\n");
            return 0; // Sair
        case 1:
            return 1; // Tentar novamente
        default:
            printf("Opcao invalida! Voltando ao menu principal...\n");
            return 0; 
    }
}
