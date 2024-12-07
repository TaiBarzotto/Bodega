#ifndef EMPRESA_H
#define EMPRESA_H

#include "Clientes.h"
#include "Bebidas.h"
#include "Auxiliares.h"

typedef struct Empresa 
{
    char cnpj[20]; // Utilizei o tipo char, para poder armazenar com a formatação adequada XX.XXX.XXX/XXXX-XX
    char nome_empresa[255];
    //cada empresa tem seus proprios clientes e bebidas cadastrados
    S_Bebidas lista_bebidas;
    S_Clientes lista_clientes;
    struct Empresa *next;
} Empresa;

typedef struct S_Empresa
{
    Empresa *head;
    Empresa *tail;
}S_Empresa;

Empresa *logar_bodega(S_Empresa *s);
void iniciar_empresa(S_Empresa *s);
int validar_cnpj(Empresa *temp, Empresa *aux);
void cadastrar_bodega(S_Empresa *s);
#endif
