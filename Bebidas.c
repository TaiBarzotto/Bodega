#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "Bebidas.h"

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

// Função para liberar a estrutura de bebidas
void liberar_bebidas_root(S_Bebidas *s, int *contador) {
    liberar_bebidas(s->root, contador);
    s->root = NULL; // Limpa a raiz
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
    // Se o código não for encontrado, continue a busca
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
        printf("Digite o codigo da bebida: ");
        scanf("%d", &codigo);
        temp = validar_codigo(s->root, codigo);
        if (temp == NULL) {
            aux->codigo = codigo;
            break;
        }else{
            printf("Esse codigo ja existe!\n");
            printf("0-SAIR\n");
            printf("1-CADASTRAR OUTRO CODIGO\n");
            scanf("%d", &opcao);
            switch (opcao)
            {
            case 0:
                free(aux);
                return;
            case 1:
                continue;
            default:
                printf("Opcao invalida, retornando ao menu principal\n");
                return;
            }
        }
    }

    printf("Digite o nome da bebida: ");
    scanf("%s", aux->nome_bebida);

    printf("Digite o conteudo liquido (mL): ");
    scanf("%f", &aux->ml);

    printf("Digite o preço da bebida: ");
    scanf("%f", &aux->preco);

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &aux->quantidade);

    printf("A bebida e alcoolica? (0-NAO   1-SIM): ");
    scanf("%f", &aux->teor_alcoolico);

    if (aux->teor_alcoolico == 1) {
        printf("Digite o teor alcoolico: ");
        scanf("%f", &aux->teor_alcoolico);
    }

    // Insere a bebida na árvore
    s->root = insertBebida(s->root, aux->codigo, aux->nome_bebida, aux->ml, aux->preco, aux->quantidade, aux->teor_alcoolico);
    
    free(aux); // Libera a memória do auxiliar
    printf("Bebida cadastrada com sucesso!\n");

}

void mostrar_bebida(Bebida *node){
    if (node == NULL) {
        return;
    }
    mostrar_bebida(node->left);
    printf("Codigo: %d\n", node->codigo);
    printf("Nome: %s\n", node->nome_bebida);
    printf("Conteudo liquido: %.2f mL\n", node->ml);
    printf("Quantidade em estoque: %d unidades\n", node->quantidade);
    printf("Preco de venda: R$ %.2f\n", node->preco);
    printf("Alcoolico: %s\n", (node->teor_alcoolico > 0) ? "Sim" : "Nao");
    printf("-------------------------------------\n");
    mostrar_bebida(node->right);
}

void exibir_bebidas(S_Bebidas *s) {
    if (s->root == NULL) {
        printf("Nenhuma bebida cadastrada no sistema!\n");
        return;
    }
    printf("==== BEBIDAS CADASTRADAS ====\n");
    mostrar_bebida(s->root);
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
        printf("Digite o codigo da bebida: ");
        scanf("%d", &codigo);
        bebida = validar_codigo(s->root, codigo);
        if (bebida == NULL) {
            printf("Erro: Esse codigo nao existe!\nO que deseja fazer?\n");
            printf("0 - SAIR\n");
            printf("1 - DIGITAR OUTRO CODIGO\n");
            scanf("%d", &opcao);
            switch (opcao) {
                case 0:
                    printf("Voltando ao menu principal...\n");
                    return; // Sair
                case 1:
                    continue; // Tentar novamente
                default:
                    printf("Opcao invalida! Voltando ao menu principal...\n");
                    return; // Sair
            }
        }

        break;
     
    }
    printf("Digite quantas unidades foram compradas: ");
    scanf("%d", &quantidade);
    // Atualiza a quantidade em estoque
    bebida->quantidade += quantidade; 
    printf("Estoque atualizado! Nova quantidade: %d unidades\n", bebida->quantidade);
}

