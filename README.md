# README - Sistema de Gerenciamento de Bebidas

## Descrição do Projeto

Este projeto foi desenvolvido como trabalho final da disciplina de Estruturas de Dados do segundo semestre do curso de Ciência da Computação. O sistema é um gerenciador de bebidas e clientes, implementado em C, que utiliza estruturas de dados como árvores binárias de busca (AVL) e listas encadeadas. O objetivo é permitir o cadastro, visualização e gerenciamento de bebidas e clientes, além de possibilitar a venda de bebidas, respeitando as regras de idade para a venda de bebidas alcoólicas.

## Status do Projeto

**Encerrado**: Este projeto foi concluído, mas ainda existem oportunidades de refinamento e melhorias. Sugestões e contribuições são bem-vindas!

## Funcionalidades

- **Cadastro de Bebidas**: Registro de novas bebidas com informações como código, nome, volume, preço, quantidade em estoque e teor alcoólico.
- **Cadastro de Clientes**: Registro de clientes com informações como CPF, nome, idade e se podem comprar fiado.
- **Gerenciamento de Estoque**: Reposição de estoque de bebidas e venda de bebidas, com validações para garantir a integridade dos dados.
- **Validação de CPF e CNPJ**: Funções para validar e formatar CPF e CNPJ.
- **Exibição de Dados**: Funções para exibir as bebidas e clientes cadastrados de forma organizada.

## Tecnologias Utilizadas

- **Linguagem de Programação**: C
- **Estruturas de Dados**: Árvores AVL, Listas Encadeadas
- **Bibliotecas**: `stdio.h`, `stdlib.h`, `string.h`, `ctype.h`