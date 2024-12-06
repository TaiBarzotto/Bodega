#include "Clientes.h"
#include "Bebidas.h"

typedef struct Empresa 
{
    char cnpj[20]; // Utilizei o tipo char, para poder armazenar com a formatação adequada XX.XXX.XXX/XXXX-XX
    char nome_empresa[255];
    //cada empresa tem seus proprios clientes e bebidas cadastrados
    Bebida *root; 
    Cliente *head;
    struct Empresa *next;
} Empresa;
