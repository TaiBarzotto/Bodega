#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include "Empresa.h"
#include "Bebidas.h"
#include "Clientes.h"



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
            printf("Opcao invalida, retornando ao menu principal\n");
            return 0;
        }

}


void iniciar_bedida(S_Bebidas *s){
    s->head = NULL;
    s->tail = NULL;
}
void iniciar_cliente(S_Clientes *s){
    s->head = NULL;
    s->tail = NULL;
}

int validar_codigo_cadastro(Bebida *temp, Bebida *aux){
    int opcao = 0; 
    while (temp != NULL)
    {
        if(temp->codigo == aux->codigo){
            printf("Esse codigo já existe!\n");
            printf("0-SAIR\n");
            printf("1-CADASTRAR OUTRO CODIGO\n");
            scanf("%d", &opcao);
            switch (opcao)
            {
            case 0:
                free(aux);
                return 0;
            case 1:
                return 1;
            default:
                printf("Opcao invalida, retornando ao menu principal\n");
                return -1;
            }
        }
        temp = temp->next;
    }
    return 2;
}

int validar_codigo_cadastro_cliente(Cliente *temp, Cliente *aux){
    int opcao = 0; 
    while (temp != NULL)
    {
        if(temp->codigo == aux->codigo){
            printf("Esse codigo já existe!\n");
            printf("0-SAIR\n");
            printf("1-CADASTRAR OUTRO CODIGO\n");
            scanf("%d", &opcao);
            switch (opcao)
            {
            case 0:
                free(aux);
                return 0;
            case 1:
                return 1;
            default:
                printf("Opcao invalida, retornando ao menu principal\n");
                return -1;
            }
        }
        temp = temp->next;
    }
    return 2;
}

void cadastrar_bebida(S_Bebidas *s){
    int validacao = 1;
    Bebida *aux, *temp = s->head, *insertion = s->head;
    aux = (Bebida *) malloc(sizeof(Bebida));

    //Verificar se o codigo já existe
    while (validacao == 1)
    {
        printf("Digite o codigo da bebida: ");
        scanf("%d", &aux->codigo);
        validacao = validar_codigo_cadastro(temp, aux);
    }

    if(validacao != 2){
        return;
    }
    
    printf("Digite o nome da bebida: ");
    scanf("%s", aux->nome_bebida);

    printf("Digite o conteudo liquido (mL): ");
    scanf("%f", &aux->ml);

    printf("Digite o preco da bebida: ");
    scanf("%f", &aux->preco);

    printf("Digite a quantiedade em estoque: ");
    scanf("%d", &aux->quantiedade);

    printf("A bebida e alcoolica? (0-NAO   1-SIM): ");
    scanf("%f", &aux->teor_alcoolico);

    if(aux->teor_alcoolico == 1){
        printf("Digite o teor alcoolico: ");
        scanf("%f", &aux->teor_alcoolico);
    }

    aux->next = NULL;

    if(s->head == NULL){
        s->head = aux;
        s->tail = aux;
    }
    else{
        if(aux->codigo < s->head->codigo){
            aux->next = s->head;
            s->head = aux;
        }
        else if(aux->codigo > s->tail->codigo){
            s->tail->next = aux;
            s->tail = aux;
        }
        else{
            while (insertion != NULL)
            {
                if(aux->codigo > insertion->codigo && aux->codigo < insertion->next->codigo){
                    aux->next = insertion->next;
                    insertion->next = aux;
                }
            }  
        }
    }
    
    printf("Bebida cadastrada com sucesso!\n");
    return;
}

void mostrar_bebida(S_Bebidas *s){
    if(s->head == NULL){
        printf("Nenhuma bebida cadastrada no sistema!\n");
        return;
    }

    Bebida *aux = s->head;
    printf("==== BEBIDAS CADASTRADAS ====\n");
    while (aux!=NULL)
    {
        printf("Codigo: %d\n", aux->codigo);
        printf("Nome: %s\n", aux->nome_bebida);
        printf("Conteudo liquido: %.2f mL\n", aux->ml);
        printf("Quantidade em estoque: %d unidades\n", aux->quantiedade);
        printf("Preco de venda: R$ %.2f\n", aux->preco);
        printf("Alcoolico: %s\n", (aux->teor_alcoolico > 0) ? "Sim" : "Nao");
        aux=aux->next;
        printf("-------------------------------------\n\n");
    }
}

int validar_codigo(Bebida *temp, int codigo){
    int opcao;
    while (temp != NULL)
    {
        if(temp->codigo == codigo){
            return 1;
        }
        temp = temp->next;
    }
    printf("Esse codigo nao existe!\nO que deseja fazer?\n");
    printf("0-SAIR\n");
    printf("1-DIGITAR OUTRO CODIGO\n");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 0:
        printf("Voltando ao menu principal...\n");
        return 0;
    case 1:
        return 2;
    default:
        printf("Opcao invalida! Voltando ao menu principal...\n");
        return 0;
    }
}

void comprar_bebida(S_Bebidas *s){
    int validacao = 2;
    Bebida *temp = s->head;    
    int codigo, quantidade;

    if(s->head == NULL){
        printf("Nenhuma bebida cadastrada!");
        return;
    }

    while (validacao == 2)
    {
        printf("Digite o codigo da bebida: ");
        scanf("%d", &codigo);
        validacao = validar_codigo(temp, codigo);
    }
    if(validacao == 0){
        return;
    }

    printf("Digite a quantidade de unidades compradas: ");
    scanf("%d",&quantidade);
    

    temp->quantiedade += quantidade;
    printf("Estoque atualizado!\n");
    return;
}

void vender_bebida(S_Bebidas *b, S_Clientes *c){
    char cpf_digitado[15], cpf[20];
    int cod_bebida, validacao = 2, qntd, opcao;
    Cliente *temp_c = c->head;
    Bebida *temp_b = b->head;

    if(b->head == NULL){
        printf("Nenhuma bebida cadastrada no sistema!\nPor favor, cadastre as bebidas antes de realizar as vendas\n");
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
        printf("%p", temp_c);
    }

    if(temp_c == NULL){
        printf("Cliente nao cadastrado! \nVoltando ao menu principal...\n");
        return;
    }

    while (validacao == 2)
    {
        printf("Digite o codigo da bebida: ");
        scanf("%d", &cod_bebida);
        validacao = validar_codigo(temp_b, cod_bebida);
    }
    if(validacao == 0){
        return;
    }

    while (temp_b != NULL) {
        if (temp_b->codigo == cod_bebida) {
            break; 
        }
        temp_b = temp_b->next;
    }

    if (temp_b == NULL) {
        printf("Bebida não encontrada! \nVoltando ao menu principal...\n");
        return;
    }

    if(temp_b->teor_alcoolico>0 && temp_c ->idade <18){
        printf("O cliente tem menos de 18 anos e a bebida é alcoolica!\n");
        return;
    }

    printf("Digite a quantidadde de bebida que deseja vender: ");
    scanf("%d", &qntd);

    if(temp_b->quantiedade <= 0 || temp_b->quantiedade < qntd){
        printf("Bebida com estoque insuficiente\n");
        printf("Quantidade atual: %d", temp_b->quantiedade);
        return;
    }

    temp_b->quantiedade -= qntd;
    printf("Bebida vendida!\n");
    return;
}

void cadastrar_cliente(S_Clientes *s){
    int validacao = 1, opcao =1;
    char cpf_digitado[15], cpf[20];
    Cliente *aux;
    aux = (Cliente *) malloc(sizeof(Cliente));
    Cliente *temp = s->head, *insertion = s->head;

    
    while (validacao == 1)
    {
        printf("Digite o codigo do cliente: ");
        scanf("%d", &aux->codigo);
        validacao = validar_codigo_cadastro_cliente(temp, aux);
    }

    if(validacao != 2){
        return;
    }
    

    printf("Digite o nome do cliente: ");
    scanf("%s", aux->nome_cliente);
    while (opcao == 1)
    {
        printf("Digite o CPF do cliente: ");
        scanf("%s", cpf_digitado);
        opcao = formatarCPF(cpf_digitado,cpf);
        strcpy(aux->cpf, cpf);
    }
    if (opcao == 0)
    {
        return;
    }

    printf("Digite a idade do cliente: ");
    scanf("%d", &aux->idade);

    printf("Vender fiado (0-NAO 1-SIM): ");
    scanf("%d", &aux->fiado);

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

void mostrar_cliente(S_Clientes *s){
    if(s->head == NULL){
        printf("Nenhum cliente cadastrado no sistema!\n");
        return;
    }

    Cliente *aux = s->head;
    printf("==== CLIENTES CADASTRADOS ====\n");
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

int main(){
    S_Bebidas lista_bebidas;
    S_Clientes lista_clientes;

    iniciar_bedida(&lista_bebidas);
    iniciar_cliente(&lista_clientes);

    cadastrar_bebida(&lista_bebidas);
    mostrar_bebida(&lista_bebidas);
    cadastrar_cliente(&lista_clientes);
    mostrar_cliente(&lista_clientes);
    vender_bebida(&lista_bebidas, &lista_clientes);    

    return 0;
}
