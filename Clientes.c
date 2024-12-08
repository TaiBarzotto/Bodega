#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include "Clientes.h"
#include "Auxiliares.h"

int liberar_clientes(S_Clientes *s) {
    Cliente *atual = s->head;
    Cliente *temp;
    int contador = 0;

    while (atual != NULL) {
        temp = atual;
        atual = atual->next;
        free(temp);
        contador++;
    }

    s->head = NULL; 
    s->tail = NULL;

    return contador; 
}

void iniciar_cliente(S_Clientes *s){
    s->head = NULL;
    s->tail = NULL;
}

// Verifica se esse CPF já foi cadastrado
int validar_cpf(Cliente *temp, Cliente *aux){
    int opcao; 
    while (temp != NULL)
    {
        if(strcmp(temp->cpf, aux->cpf) == 0){ 
            while (getchar() != '\n'); 
            printf("Esse CPF ja foi cadastrado!\n");
            printf("0-SAIR\n");
            printf("1-CADASTRAR OUTRO CPF\n");
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

int ultimo_codigo = 0; //Armazenar o codigo do ultimo cliente cadastrado

void cadastrar_cliente(S_Clientes *s){
    int validacao = 1, opcao;
    char cpf_digitado[15], cpf[20]; //Vetor para formatar CPF
    Cliente *aux = (Cliente *) malloc(sizeof(Cliente)); //Armazenar os valores dos atributos
    Cliente *temp = s->head, *insertion = s->head; //Auxiliares para percorrer a lista
    
    while (1){
        printf("Digite o CPF do cliente: ");
        scanf("%s", cpf_digitado);
        opcao = formatarCPF(cpf_digitado,cpf);
        if (opcao == 0){
            free(aux);
            return;
        }
        else if (opcao == 1){
            continue;
        }

        strcpy(aux->cpf, cpf);
        opcao = validar_cpf(temp, aux);
        if (opcao == 0){
            free(aux);
            return;
        }
        else if (opcao == 1){
            continue;
        }
        break;
    }

    aux->codigo = ++ultimo_codigo;


    printf("Digite o nome do cliente: ");
    scanf("%s", &aux->nome_cliente);
    while (getchar() != '\n'); 

    while (1) {
        aux->idade = ler_inteiro("Digite a idade do cliente: ");

        if (aux->idade < 0) {
            printf("Idade invalida! A idade deve ser um numero positivo.\n");
            continue;
        }
        break;
    } 

    while(1) {
        aux->fiado = ler_inteiro("Vender fiado (0-NAO 1-SIM): ");

        if (aux->fiado != 0 && aux->fiado != 1) {
            printf("Opcao invalida! Por favor, insira 0 para NAO ou 1 para SIM.\n");
            continue;
        }
        break;
    } 

    aux->next = NULL;

    if(s->head == NULL){
        s->head = aux;
        s->tail = aux;
    }
    else{
        if(aux->idade < s->head->idade){
            aux->next = s->head;
            s->head = aux;
        }
        else if(aux->idade > s->tail->idade){
            s->tail->next = aux;
            s->tail = aux;
        }
        else{
            while (insertion != NULL)
            {
                if(aux->idade > insertion->idade && aux->idade < insertion->next->idade){
                    aux->next = insertion->next;
                    insertion->next = aux;
                }
            }  
        }
    }

    printf("Cliente cadastrado\n");
    return;
}

//Percorre a lista
void mostrar_cliente(S_Clientes *s){
    if(s->head == NULL){
        printf("Nenhum cliente cadastrado no sistema!\n");
        return;
    }

    Cliente *aux = s->head;
    printf("\n==== CLIENTES CADASTRADOS ====\n");
    while (aux!=NULL)
    {
        printf("Codigo: %d\n", aux->codigo);
        printf("Nome: %s\n", aux->nome_cliente);
        printf("CPF: %s\n", aux->cpf);
        printf("Idade: %d\n", aux->idade);
        printf("Vender fiado: %s\n", (aux->fiado == 1) ? "Sim" : "Nao");
        aux=aux->next;
        printf("-------------------------------------\n\n");
    }
    return;
}
