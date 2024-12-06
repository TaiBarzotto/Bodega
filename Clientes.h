typedef struct Cliente {
    int codigo;
    char nome_cliente[100];
    char cpf[15];
    int idade;
    int fiado;
    struct Cliente *next; 
} Cliente;

typedef struct S_Clientes {
    Cliente *head;
    Cliente *tail; 
} S_Clientes;

// Funções para gerenciar clientes
int liberar_clientes(S_Clientes *s);
void iniciar_cliente(S_Clientes *s);
int validar_cpf(Cliente *temp, Cliente *aux);
void cadastrar_cliente(S_Clientes *s);
void mostrar_cliente(S_Clientes *s);

// Variável global para o último código de cliente
extern int ultimo_codigo;

