#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>

int numero_inteiro_valido(const char *str) {
    char *endptr;
    strtol(str, &endptr, 10); // Tenta converter a string para int

    // Verifica se a conversão foi bem-sucedida e se não há caracteres restantes
    return *endptr == '\n' || *endptr == '\0';
}

int ler_inteiro(const char *mensagem) {
    int valor;
    char buffer[100];

    while (1) {
        printf("%s", mensagem);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Verifica se a entrada é um número inteiro válido
            if (numero_inteiro_valido(buffer)) {
                valor = strtol(buffer, NULL, 10); // Converte a string para int
                return valor; // Retorna o valor lido
            } else {
                // Se a conversão falhou, avise o usuário
                printf("Entrada inválida. Por favor, digite um número inteiro.\n");
            }
        } else {
            // Se fgets falhar, avise o usuário
            printf("Erro ao ler a entrada. Tente novamente.\n");
        }
    }
}

int numero_valido(const char *str) {
    char *endptr;
    strtof(str, &endptr); // Tenta converter a string para float

    // Verifica se a conversão foi bem-sucedida e se não há caracteres restantes
    return *endptr == '\n' || *endptr == '\0';
}

// Função para ler um float com validação
float ler_float(const char *mensagem) {
    float valor;
    char buffer[100];

    while (1) {
        printf("%s", mensagem);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Verifica se a entrada é um número válido
            if (numero_valido(buffer)) {
                valor = strtof(buffer, NULL); // Converte a string para float
                return valor; // Retorna o valor lido
            } else {
                // Se a conversão falhou, avise o usuário
                printf("Entrada inválida. Por favor, digite um número decimal.\n");
            }
        } else {
            // Se fgets falhar, avise o usuário
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
    printf("CPF invalido\n");
    printf("0-SAIR\n");
    printf("1-DIGITAR CPF NOVAMENTE\n");
    scanf("%d", &opcao);
    switch (opcao){
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            while (getchar() != '\n');
            printf("Opcao invalida, retornando ao menu principal\n");
            return 0;
        }

}

int mensagem_erro_codigo(const char *mensagem){
    int opcao;
    printf("%s", mensagem);
    printf("0 - SAIR\n");
    opcao = ler_inteiro("1 - DIGITAR OUTRO CODIGO\n");
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