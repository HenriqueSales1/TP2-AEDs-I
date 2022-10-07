#include <iostream>

#include "Header_TAD.hpp"

using namespace std;

bool CriaPilhaVazia(Pilha *pilha)
{
    // if (pilha->topo == -1 && pilha->tamanho == 0)
    // {
        pilha->topo = -1;
        pilha->tamanho = 0;
    // }
    return 0;
}

bool VerificaPilhaVazia(Pilha *pilha)
{
    if (pilha->topo == -1 && pilha->tamanho == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool VerificaPilhaCheia(Pilha *pilha)
{
    if (pilha->tamanho == MAX_PEDIDOS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Empilha(Pilha *pilha, Pedido ped)
{
    if (VerificaPilhaCheia(pilha))
    {
        return false;
    }
    else
    {
        pilha->ped[pilha->tamanho] = ped;
        pilha->topo++;
        pilha->tamanho++;
        return true;
    }
}

void Desempilha(Pilha *pilha, Pedido *ped)
{
    *ped = pilha->ped[pilha->tamanho - 1];
    pilha->ped[pilha->tamanho - 1] = pilha->ped[pilha->tamanho];
    pilha->tamanho--;
    pilha->topo--;
    return;
}

void ImprimePilha(Pilha *pilha)
{
    for (int i = pilha->topo; i >= 0; i--)
    {
        cout << "ID do pedido: " << pilha->ped[i].pedido << endl;
        cout << "Distância: " << pilha->ped[i].distancia << endl;
        cout << "Valor total do pedido: " << pilha->ped[i].valor_pedido << endl;
        cout << "Código dos pedidos: ";
        for (int j = 0; j < MAXTAM; j++)
        {
            cout << pilha->ped[i].produtos[j] << " ";
        }
        cout << endl << endl;
    }
    cout << endl;
}

void ImprimeMenu()
{
    cout << "---- MENU ----\n\n";
    cout << "1. Incluir pedido\n";
    cout << "2. Listar pedidos\n";
    cout << "3. Mostrar cardápio\n";
    cout << "4. Consultar pedido\n";
    cout << "5. Organizar lista de entrega\n";
    cout << "6. Lançar entrega\n\n";
}

void ImprimeCardapio()
{
    cout << "---- CARDÁPIO DA LANCHONETE ----\n\n";
    cout << "ID do Produto:\t\tProduto:\n\n";
    cout << "1.\t\t\tSuco\n";
    cout << "2.\t\t\tRefrigerante\n";
    cout << "3.\t\t\tComidas\n\n";
}

int Consulta(Pilha *pilha, int codigo)
{
    for (int i = 0; i < pilha->tamanho; i++)
    {
        if (pilha->ped[i].pedido == codigo)
        {
            return i;
        }
    }
    return -1;
}