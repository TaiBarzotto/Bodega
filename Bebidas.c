#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "Bebidas.h"
#include "Auxiliares.h"

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Bebida *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Função para criar um novo nó Bebida
Bebida *newBebida(int codigo, const char *nome_bebida, float ml, float preco, int quantidade, float teor_alcoolico) {
    Bebida *node = (Bebida *)malloc(sizeof(Bebida));
    node->codigo = codigo;
    strcpy(node->nome_bebida, nome_bebida);
    node->ml = ml;
    node->preco = preco;
    node->quantidade = quantidade;
    node->teor_alcoolico = teor_alcoolico;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; 
    return node;
}

// Função para obter o fator de balanceamento de um nó
int getBalance(Bebida *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Função para realizar uma rotação à direita
Bebida *rightRotate(Bebida *y) {
    Bebida *x = y->left;
    Bebida *f = x->right;

    // Realiza a rotação
    x->right = y;
    y->left = f;

    // Atualiza as alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Retorna o novo nó raiz
    return x;
}

// Função para realizar uma rotação à esquerda
Bebida *leftRotate(Bebida *x) {
    Bebida *y = x->right;
    Bebida *f = y->left;

    // Realiza a rotação
    y->left = x;
    x->right = f;

    // Atualiza as alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Retorna o novo nó raiz
    return y;
}

// Função para inserir um novo nó na árvore AVL
Bebida *insertBebida(Bebida *node, int codigo, const char *nome_bebida, float ml, float preco, int quantiedade, float teor_alcoolico) {
    // 1. Realiza a inserção normal na árvore binária de busca
    if (node == NULL)
        return newBebida(codigo, nome_bebida, ml, preco, quantiedade, teor_alcoolico);

    if (codigo < node->codigo)
        node->left = insertBebida(node->left, codigo, nome_bebida, ml, preco, quantiedade, teor_alcoolico);
    else if (codigo > node->codigo)
        node->right = insertBebida(node->right, codigo, nome_bebida, ml, preco, quantiedade, teor_alcoolico);
    else // Códigos duplicados não são permitidos
        return node;

    // 2. Atualiza a altura do nó ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Obtém o fator de balanceamento deste nó ancestral para verificar se ele se tornou desbalanceado
    int balance = getBalance(node);

    // Se o nó se tornar desbalanceado, existem 4 casos

    // Caso 1: Rotação à direita
    if (balance > 1 && codigo < node->left->codigo)
        return rightRotate(node);

    // Caso 2: Rotação à esquerda
    if (balance < -1 && codigo > node->right->codigo)
        return leftRotate(node);

     // Caso 3: Rotação à esquerda seguida de rotação à direita (LR)
    if (balance > 1 && codigo > node->left->codigo) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso 4: Rotação à direita seguida de rotação à esquerda (RL)
    if (balance < -1 && codigo < node->right->codigo) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Retorna o ponteiro do nó (não alterado)
    return node;
}

void liberar_bebidas(Bebida *node, int *contador) {
    if (node == NULL) {
        return;
    }

    liberar_bebidas(node->left, contador);  // Libera a subárvore esquerda
    liberar_bebidas(node->right, contador); // Libera a subárvore direita
    free(node); // Libera o nó atual
    (*contador)++;
}

void liberar_bebidas_root(S_Bebidas *s, int *contador) {
    liberar_bebidas(s->root, contador);
    s->root = NULL; 
}

void iniciar_bebida(S_Bebidas *s) {
    s->root = NULL;
}

Bebida* validar_codigo(Bebida *node, int codigo) {
    if (node == NULL) {
        return NULL; 
    }
    if (node->codigo == codigo) {
        return node; 
    }

    if (codigo < node->codigo) {
        return validar_codigo(node->left, codigo); 
    } else {
        return validar_codigo(node->right, codigo); 
    }
}

void cadastrar_bebida(S_Bebidas *s) {
    int codigo, opcao = 1;
    Bebida *aux = (Bebida *)malloc(sizeof(Bebida)), *temp;
    if (aux == NULL) {
        printf("Erro ao alocar memoria para a bebida.\n");
        return;
    }

    // Verificar se o código já existe
    while (1) {
        codigo = ler_inteiro("Digite o codigo da bebida: ");

        temp = validar_codigo(s->root, codigo);
        if (temp == NULL) {
            aux->codigo = codigo;
            break;
        }else{
            opcao = mensagem_erro_codigo("Esse codigo ja existe!\n");
            if (opcao == 0){
                free(aux);
                return;
            }
            else{
                continue;
            }
        }
    }

    printf("Digite o nome da bebida: ");
    scanf("%s", aux->nome_bebida);
    while (getchar() != '\n'); 

    while (1) {
        aux->ml = ler_float("Digite o conteudo liquido (mL): ");
    
        if (aux->ml < 0) {
            printf("Medida invalida. Insira um numero maior ou igual a 0\n");
            continue;
        }
        break;
    } 
    
    while (1) {
        aux->preco = ler_float("Digite o preco da bebida: ");
    
        if (aux->preco < 0) {
            printf("Valor invalido. Insira um valor maior ou igual a 0\n");
            continue;
        }
        break;
    }

    while (1) {
        aux->quantidade = ler_inteiro("Digite a quantidade em estoque: ");
    
        if (aux->quantidade < 0) {
            printf("Estoque invalido. Insira um valor maior ou igual a 0\n");
            continue;
        }
        break;
    }
    
    while (1) {
        aux->teor_alcoolico = ler_float("A bebida eh alcoolica? (0-NAO   1-SIM): ");

        if(aux->teor_alcoolico != 0 && aux->teor_alcoolico != 1){
            printf("Opcaoo invalida! Por favor, insira 0 para NAO ou 1 para SIM.\n");
            continue;
        }
        break;
    }

    if (aux->teor_alcoolico == 1) aux->teor_alcoolico = ler_float("Digite o teor alcoolico: ");
    
    s->root = insertBebida(s->root, aux->codigo, aux->nome_bebida, aux->ml, aux->preco, aux->quantidade, aux->teor_alcoolico);
    
    free(aux); 
    printf("Bebida cadastrada com sucesso!\n");

}

void exibir_bebidas(Bebida *node){
    if (node == NULL) {
        return;
    }
    exibir_bebidas(node->left);
    printf("Codigo: %d\n", node->codigo);
    printf("Nome: %s\n", node->nome_bebida);
    printf("Conteudo liquido: %.2f mL\n", node->ml);
    printf("Quantidade em estoque: %d unidades\n", node->quantidade);
    printf("Preco de venda: R$ %.2f\n", node->preco);
    printf("Alcoolico: %s\n", (node->teor_alcoolico > 0) ? "Sim" : "Nao");
    if(node->teor_alcoolico > 0){
        printf("Teor Alcoolico: %.2f \n", node->teor_alcoolico > 0);  
    }
    printf("-------------------------------------\n");
    exibir_bebidas(node->right);
}

void mostrar_bebida(S_Bebidas *s) {
    if (s->root == NULL) {
        printf("Nenhuma bebida cadastrada no sistema!\n");
        return;
    }
    printf("\n==== BEBIDAS CADASTRADAS ====\n");
    exibir_bebidas(s->root);
}

void comprar_bebida(S_Bebidas *s) {
    Bebida *bebida;
    int codigo, quantidade, opcao = 1;

    if (s->root == NULL) {
        printf("Nenhuma bebida cadastrada!\n");
        return;
    }

    while (1)
    {   
        codigo = ler_inteiro("Digite o codigo da bebida: ");
        bebida = validar_codigo(s->root, codigo);
        if (bebida == NULL) {
            opcao = mensagem_erro_codigo("Erro: Esse codigo nao existe!\nO que deseja fazer?\n");
            if(opcao == 0) return; // Sair
            else continue;// Tentar novamente
        }
        break;
    }
    
    while (1) {
        quantidade = ler_inteiro("Digite quantas unidades foram compradas: ");
    
        if (quantidade < 1) {
            printf("Compra invalida. Insira um valor maior ou igual 1\n");
            continue;
        }
        break;
    }
    
    bebida->quantidade += quantidade; 
    printf("Estoque atualizado! Nova quantidade: %d unidades\n", bebida->quantidade);
}

