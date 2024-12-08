#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include "Empresa.h"
#include "Bebidas.h"
#include "Clientes.h"
#include "Auxiliares.h"

void iniciar_empresa(S_Empresa *s){
    s->head = NULL;
    s->tail = NULL;
}

int validar_cnpj(Empresa *temp, Empresa *aux){
    int opcao; 
    while (temp != NULL)
    {
        if(strcmp(temp->cnpj, aux->cnpj) == 0){ // Verifica se esse CNPJ já foi cadastrado
            while (getchar() != '\n'); 
            printf("Esse CNPJ ja foi cadastrado!\n");
            printf("0-SAIR\n");
            printf("1-CADASTRAR OUTRO CNPJ\n");
            opcao = ler_inteiro("");
            switch (opcao)
            {
            case 0:
                free(aux);
                return 0;
            case 1:
                return 1;
            default:
                while (getchar() != '\n');
                printf("Opcao invalida, retornando ao menu principal\n");
                return 0;
            }
        }
        temp = temp->next;
    }
    return 2;
}

void cadastrar_bodega(S_Empresa *s){
    int opcao;
    char cnpj_digitado[15], cnpj[20]; //Vetores para formatar o CNPJ
    Empresa *aux = (Empresa *) malloc(sizeof(Empresa));
    Empresa *temp = s->head;
    
    while (1){
        printf("Digite o CNPJ da Bodega: ");
        scanf("%s", cnpj_digitado);
        opcao = formatarCNPJ(cnpj_digitado,cnpj);
        if (opcao == 0){
            free(aux);
            return;
        }
        else if (opcao == 1){
            continue;
        }

        strcpy(aux->cnpj, cnpj);
        opcao = validar_cnpj(temp, aux);
        if (opcao == 0){
            free(aux);
            return;
        }
        else if (opcao == 1){
            continue;
        }
        break;
    }

    printf("Digite o nome da bodega: ");
    scanf("%s", &aux->nome_empresa);
    while (getchar() != '\n'); 

    iniciar_bebida(&aux->lista_bebidas);
    iniciar_cliente(&aux->lista_clientes);
    aux->next = NULL;

    if(s->head == NULL){
        s->head = aux;
        s->tail = aux;
    }else{
        s->tail->next = aux;
        s->tail = aux;
    }
    printf("Bodega cadastrada!\n");
}

//Le o cnpj e retorna o ponteiro da empresa que possui esse cnpj
Empresa *logar_bodega(S_Empresa *s){
    int opcao;
    char cnpj[20], cnpj_digitado[25];
    Empresa *empresa = s->head;

    while (1) {
        printf("Digite o CNPJ da bodega para login: ");
        scanf("%s", cnpj_digitado);
        opcao = formatarCNPJ(cnpj_digitado, cnpj);
        if (opcao == 0) {   
            printf("Voltando ao menu inicial...\n");
            return NULL; 
        }
        if (opcao == 2) break;
    }

    while (empresa != NULL)
    {
        if(strcmp(empresa->cnpj, cnpj)==0){
            return empresa;
        }
        empresa = empresa->next;
    }
    printf("Erro: CNPJ nao encontrado. Por favor cadastre-se\n");
    while (getchar() != '\n');
    return NULL;
}