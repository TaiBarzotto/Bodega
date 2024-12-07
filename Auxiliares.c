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

int 
ler_inteiro(const char *mensagem) {
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

int formatarCPF(char *cpf_entrada, char *cpf_formatado) {
    int j = 0, a, b=0, opcao;

    for (int i = 0; cpf_entrada[i] != '\0'; i++) {
        if (isalnum(cpf_entrada[i])) {
            cpf_formatado[j++] = cpf_entrada[i];
        
        }
    }
    for (a = 0; cpf_entrada[a] != '\0'; a++) {
        if (isdigit(cpf_entrada[a])) {
            cpf_formatado[b++] = cpf_entrada[a];
        
        }
    }
    cpf_formatado[b] = '\0'; 

    if (j == 11 && b == 11) {
        // Formata o CPF
        snprintf(cpf_formatado, 15, "%c%c%c.%c%c%c.%c%c%c-%c%c",
                 cpf_formatado[0], cpf_formatado[1], cpf_formatado[2],
                 cpf_formatado[3], cpf_formatado[4], cpf_formatado[5],
                 cpf_formatado[6], cpf_formatado[7], cpf_formatado[8],
                 cpf_formatado[9], cpf_formatado[10]);
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

int formatarCNPJ(char *cnpj_entrada, char *cnpj_Formatado) {
    int j = 0, a,b=0, opcao;

    for (int i = 0; cnpj_entrada[i] != '\0'; i++) {
        if (isalnum(cnpj_entrada[i])) {
            cnpj_Formatado[j++] = cnpj_entrada[i];
        
        }
    }

    for (int a = 0; cnpj_entrada[a] != '\0'; a++) {
        if (isdigit(cnpj_entrada[a])) {
            cnpj_Formatado[b++] = cnpj_entrada[a];
        
        }
    }
    cnpj_Formatado[b] = '\0'; 

    if (b == 14 && j == 14) {
        // Formata o CNPJ
        snprintf(cnpj_Formatado, 19, "%c%c.%c%c%c.%c%c%c/%c%c%c%c-%c%c",
                 cnpj_Formatado[0], cnpj_Formatado[1], cnpj_Formatado[2],
                 cnpj_Formatado[3], cnpj_Formatado[4], cnpj_Formatado[5],
                 cnpj_Formatado[6], cnpj_Formatado[7], cnpj_Formatado[8],
                 cnpj_Formatado[9], cnpj_Formatado[10], cnpj_Formatado[11],
                 cnpj_Formatado[12], cnpj_Formatado[13]);
        return 2;
    } 
    while (getchar() != '\n'); 
    printf("CNPJ invalido\n");
    printf("0-SAIR\n");
    printf("1-DIGITAR CNPJ NOVAMENTE\n");
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
