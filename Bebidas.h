typedef struct Bebida 
{
    int codigo;
    char nome_bebida[255];
    float ml;
    float preco;
    int quantiedade;
    float teor_alcoolico;
    struct Bebida *left;
    struct Bebida *right;
    int height;
} Bebida;

typedef struct Sentinela_b
{
    Bebida *head;
    Bebida *tail;
} S_Bebidas;