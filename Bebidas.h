#ifndef BEBIDAS_H
#define BEBIDAS_H

struct Bebida 
{
    int codigo;
    char nome_bebida[255];
    float ml;
    float preco;
    int quantidade;
    float teor_alcoolico;
    struct Bebida *left;
    struct Bebida *right;
    int height;
};
typedef struct Bebida Bebida;

typedef struct S_bebida{
    Bebida *root;
} S_Bebidas;

// Funções para manipulação de bebidas
void iniciar_bebida(S_Bebidas *s);
Bebida* validar_codigo(Bebida *node, int codigo);
void cadastrar_bebida(S_Bebidas *s);
void exibir_bebidas(Bebida *node);
void mostrar_bebida(S_Bebidas *s);
void comprar_bebida(S_Bebidas *s);
void liberar_bebidas(Bebida *node, int *contador);

// Funções auxiliares para a árvore AVL
int max(int a, int b);
int height(Bebida *N);
Bebida *newBebida(int codigo, const char *nome_bebida, float ml, float preco, int quantidade, float teor_alcoolico);
int getBalance(Bebida *N);
Bebida *rightRotate(Bebida *y);
Bebida *leftRotate(Bebida *x);
Bebida *insertBebida(Bebida *node, int codigo, const char *nome_bebida, float ml, float preco, int quantidade, float teor_alcoolico);

#endif