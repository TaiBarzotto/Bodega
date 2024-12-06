#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include "Empresa.h"
#include "Bebidas.h"
#include "Clientes.h"
#include "Auxiliares.h"

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
        opcao = ler_inteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                cadastrar_bebida(&lista_bebidas);
                break;
            case 2:
                mostrar_bebida(&lista_bebidas);
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
                printf("Opcao invalida! Tente novamente.\n");
                continue;
        }
    } while(opcao != 0);

    return 0;
}

void vender_bebida(S_Bebidas *b, S_Clientes *c){
    char cpf_digitado[15], cpf[20];
    int cod_bebida, validacao = 2, qntd, opcao, pagamento;
    Cliente *cliente = c->head;
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
        if (opcao == 0) {   
        
            return; 
        }
        if (opcao == 2) break; // CPF válido
    }

    while (cliente != NULL)
    {
        if(strcmp(cliente->cpf, cpf)==0){
            break;
        }
        cliente = cliente->next;
    }

    if(cliente == NULL){
        printf("Cliente nao cadastrado! \nVoltando ao menu principal para que possa cadastra-lo...\n");
    
        return;
    }


    while (1)
    {
        printf("Digite o codigo da bebida: ");
        scanf("%d", &cod_bebida);
        bebida = validar_codigo(b->root, cod_bebida);

        if (bebida == NULL) {
            while (getchar() != '\n');
            opcao = mensagem_erro_codigo("Erro: Esse codigo nao existe!\nO que deseja fazer?\n");
            if(opcao == 0) return; // Sair
            else continue; // Tentar novamente
        }
        break;
    }

    if(bebida->teor_alcoolico>0 && cliente ->idade <18){
        printf("O cliente tem menos de 18 anos e a bebida eh alcoolica!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    qntd = ler_inteiro("Digite a quantidadde de bebida que deseja vender: ");
    while (1){
        if(bebida->quantidade <= 0 || bebida->quantidade < qntd){
            printf("Bebida com estoque insuficiente\n");
            printf("Quantidade atual: %d\n", bebida->quantidade);
            printf("0-SAIR\n");
            printf("1-ATUALIZAR ESTOQUE\n");
            printf("2-ALTERAR QUANTIDADE A VENDER\n");
            opcao = ler_inteiro("");
            switch (opcao){
                case 0:
                    return;
                case 1:
                    comprar_bebida(b);
                    continue;
                case 2:
                    qntd = ler_inteiro("Digite nova quantidade de bebida a vender: ");
                    continue;
                default:
                    printf("Opcao invalida, retornando ao menu principal\n");
                    return;
            }
        }
        break;
    }

    printf("\n--- FORMAS DE PAGAMENTO ---\n");
    printf("1-PAGAMENTO EM DINHEIRO\n");
    printf("2-PAGAMENTO COM CARTAO DE CREDITO\n");
    printf("3-PAGAMENTO COM CARTAO DE DEBITO\n");
    printf("4-PIX\n");
    printf("5-FIADO\n");
    pagamento = ler_inteiro("Selecione a forma de pagamento: ");

    while (1){
        if(pagamento == 5 && cliente->fiado == 0){
            printf("Erro: Nao pode vender fiado para esse cliente!\n");
            printf("0-SAIR\n");
            printf("1-SELECIONAR OUTRA FORMA DE PAGAMENTO\n");
            opcao = ler_inteiro("");
            switch (opcao){
                case 0:
                    return;
                case 1:
                    pagamento = ler_inteiro("Nova forma de pagamento: ");
                    continue;
                default:
                    printf("Opcao invalida, retornando ao menu principal\n");
                    return;
            }
        }
        break;
    }

    bebida->quantidade -= qntd;
    printf("Bebida vendida!\n");
}
