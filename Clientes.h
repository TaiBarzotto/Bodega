typedef struct Cliente {
    int codigo;
    char nome_cliente[100];
    char cpf[15];
    int idade;
    int fiado;
    struct Cliente *next; // Ponteiro para o próximo cliente
} Cliente;

// Estrutura para gerenciar a lista de clientes
typedef struct S_Clientes {
    Cliente *head; // Cabeça da lista
    Cliente *tail; // Cauda da lista
} S_Clientes;

// Funções para gerenciar clientes
int liberar_clientes(S_Clientes *s);
void iniciar_cliente(S_Clientes *s);
int formatarCPF(char *cpfEntrada, char *cpfFormatado);
int validar_cpf(Cliente *temp, Cliente *aux);
void cadastrar_cliente(S_Clientes *s);
void mostrar_cliente(S_Clientes *s);

// Variável global para o último código de cliente
extern int ultimo_codigo;

