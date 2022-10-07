#ifndef HEADER_TAD
#define HEADER_TAD
#define MAXTAM 10
#define MAX_PEDIDOS 7


typedef struct Pedido
{
    int pedido;
    int produtos[MAXTAM];
    float distancia;
    int tamPilha;
    float valor_pedido = 0;
};

typedef struct Pilha
{
    Pedido ped[MAX_PEDIDOS];
    int topo;
    int tamanho;
};

bool CriaPilhaVazia(Pilha *pilha);
bool VerificaPilhaVazia(Pilha *pilha);
bool VerificaPilhaCheia(Pilha *pilha);
bool Empilha(Pilha *pilha, Pedido ped);
void Desempilha(Pilha *pilha, Pedido *ped);
void ImprimePilha(Pilha *pilha);
void ImprimeMenu();
void ImprimeCardapio();
int Consulta(Pilha *pilha, int codigo);

#endif