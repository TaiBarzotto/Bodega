#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include "Empresa.h"
#include "Bebidas.h"
#include "Clientes.h"

void vender_bebida(S_Bebidas *b, S_Clientes *c);

int main(){
    int opcao = -1, clientes, bebidas;
    S_Bebidas lista_bebidas;
    S_Clientes lista_clientes;

    iniciar_bebida(&lista_bebidas);
    iniciar_cliente(&lista_clientes);
    do {
        printf("\n==== MENU DE OPCOES ====\n");
        printf("1 - CADASTRAR NOVA BEBIDA\n");
        printf("2 - MOSTRAR BEBIDAS CADASTRADAS\n");
        printf("3 - REPOR ESTOQUE BEBIDA (COMPRA DE BEBIDA)\n");
        printf("4 - VENDER BEBIDA\n");
        printf("5 - CADASTRAR CLIENTE\n");
        printf("6 - MOSTRAR CLIENTES CADASTRADOS\n");
        printf("0 - SAIR DO SISTEMA\n\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida! Por favor, insira um numero.\n");
            while (getchar() != '\n'); 
            continue; 
        }

        switch (opcao) {
            case 1:
                cadastrar_bebida(&lista_bebidas);
                break;
            case 2:
                printf("\n==== BEBIDAS CADASTRADAS ====\n");
                mostrar_bebida(lista_bebidas.root);
                break;
            case 3:
                comprar_bebida(&lista_bebidas);
                break;
            case 4:
                vender_bebida(&lista_bebidas, &lista_clientes); 
                break;
            case 5:
                cadastrar_cliente(&lista_clientes);
                break;
            case 6:
                mostrar_cliente(&lista_clientes);
                break;
            case 0:
                clientes = liberar_clientes(&lista_clientes);
                liberar_bebidas(lista_bebidas.root, &bebidas);
                printf("Elementos liberados: %d\n", clientes+bebidas);
                printf("Saindo do sistema...\n");
                return 0;
            default:
                printf("Opção invalida! Tente novamente.\n");
                continue;
        }
    } while(opcao != 0);

    return 0;
}

void vender_bebida(S_Bebidas *b, S_Clientes *c){
    char cpf_digitado[15], cpf[20];
    int cod_bebida, validacao = 2, qntd, opcao;
    Cliente *temp_c = c->head;
    Bebida *bebida;

    if(b->root == NULL){
        printf("Nenhuma bebida cadastrada no sistema!\nPor favor, cadastre as bebidas antes de realizar as vendas\n");
        return;
    }
    if(c->head == NULL){
        printf("Nenhum cliente cadastrado no sistema!\nPor favor, cadastre faça o cadastro antes de realizar vendas\n");
        return;
    }

    while (1) {
        printf("Digite o CPF do cliente: ");
        scanf("%s", cpf_digitado);
        opcao = formatarCPF(cpf_digitado, cpf);
        if (opcao == 0) return; 
        if (opcao == 2) break; // CPF válido
    }

    while (temp_c != NULL)
    {
        if(strcmp(temp_c->cpf, cpf)==0){
            break;
        }
        temp_c = temp_c->next;
    }

    if(temp_c == NULL){
        printf("Cliente nao cadastrado! \nVoltando ao menu principal...\n");
        return;
    }


    while (1)
    {
        printf("Digite o codigo da bebida: ");
        scanf("%d", &cod_bebida);
        bebida = validar_codigo(b->root, cod_bebida);
        
        if (bebida == NULL) {
            printf("Erro: Esse código não existe!\nO que deseja fazer?\n");
            printf("0 - SAIR\n");
            printf("1 - DIGITAR OUTRO CÓDIGO\n");
            scanf("%d", &opcao);
            switch (opcao) {
                case 0:
                    printf("Voltando ao menu principal...\n");
                    return; // Sair
                case 1:
                    continue; // Tentar novamente
                default:
                    printf("Opção inválida! Voltando ao menu principal...\n");
                    return; // Sair
            }
        }
        break;
    }
    
    if (bebida == NULL) {
        printf("Bebida não encontrada! \nVoltando ao menu principal...\n");
        return;
    }

    if(bebida->teor_alcoolico>0 && temp_c ->idade <18){
        printf("O cliente tem menos de 18 anos e a bebida é alcoolica!\n");
        return;
    }

    printf("Digite a quantidadde de bebida que deseja vender: ");
    scanf("%d", &qntd);

    if(bebida->quantidade <= 0 || bebida->quantidade < qntd){
        printf("Bebida com estoque insuficiente\n");
        printf("Quantidade atual: %d", bebida->quantidade);
        return;
    }

    bebida->quantidade -= qntd;
    printf("Bebida vendida!\n");
    return;
}
