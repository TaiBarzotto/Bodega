typedef struct Cliente 
{
    int codigo;
    char nome_cliente[255];
    char cpf[15]; // Utilizei o tipo char, para poder armazenar com a formatação adequada XXX.XXX.XXX-XX
    int idade;
    int fiado;
    struct Cliente *left;
    struct Cliente *right;
    int height;
} Cliente;

typedef struct Sentinela_c
{
    Cliente *head;
    Cliente *tail;
} S_Clientes;
