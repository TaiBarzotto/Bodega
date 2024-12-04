//dividir em 3 objetos 

typedef struct 
{
    char cnpj[20]; // Utilizei o tipo char, para poder armazenar com a formatação adequada XX.XXX.XXX/XXXX-XX
    char nome_empresa[255];
} Empresa;

typedef struct Bebida 
{
    int codigo;
    char nome_bebida[255];
    float ml;
    float preco;
    int quantiedade;
    float teor_alcoolico;
    struct Bebida *next;
} Bebida;

typedef struct Sentinela_b
{
    Bebida *head;
    Bebida *tail;
} S_Bebidas;

typedef struct Cliente 
{
    int codigo;
    char nome_cliente[255];
    char cpf[15]; // Utilizei o tipo char, para poder armazenar com a formatação adequada XXX.XXX.XXX-XX
    int idade;
    int fiado;
    struct Cliente *next;
} Cliente;

typedef struct Sentinela_c
{
    Cliente *head;
    Cliente *tail;
} S_Clientes;

