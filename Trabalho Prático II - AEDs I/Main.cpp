#include <iostream>
#include <windows.h>
#include <fstream>

#include "TAD_Pilha.cpp"

using namespace std;

int main()
{

    UINT CPAGE_UTF8 = 65001;        // Função de interface.
    SetConsoleOutputCP(CPAGE_UTF8); // Função de interface.

    Pedido pedidos;
    Pilha mochila;

    CriaPilhaVazia(&mochila); // Função para criar a pilha zerada.

    Pilha aux1, aux2; // Variáveis para criar duas pilhas vazias auxiliares, para organizar
                      // os pedidos em ordem de distância.
    int tamanhoPilha;
    int maiorDistancia, idMaiorDistancia;
    int tamanhoMochila;
    int codPedido = 0;
    int codProduto = 0;
    float precos[] = {NULL, 2.5, 5, 12.5};
    int x;

    // A função abaixo cria o arquivo binário para, no fim do programa, salvar as informações
    // passadas durante a execução do código.

    FILE *file = fopen("lanchonete.bin", "r");
    if (file != NULL)
    {
        while (fread(&pedidos, sizeof(Pedido), 1, file))
        {
            if (pedidos.pedido > codPedido)
            {
                codPedido = pedidos.pedido;
            }
            Empilha(&mochila, pedidos);
        }
    }

    codPedido++;
    system("cls");

    int escolha;

    do
    {
        ImprimeMenu();
        cout << "Opção escolhida: ";
        cin >> escolha;
        system("cls");
        switch (escolha)
        {

            // No caso 1, o usuário irá adicionar um novo pedido, por meio da função para empilhar, indo para o fundo
            // da pilha. Os pedidos subsequentes serão colocados por cima do primeiro pedido.

        case 1:

            pedidos.pedido = codPedido;
            pedidos.tamPilha = 0;

            do
            {
                ImprimeCardapio();
                cout << "Escolha um produto: ";
                cin >> codProduto;
                if (codProduto > 3)
                {
                    cout << "Produto inexistente.\n\n";
                    system("pause");
                    system("cls");
                }
                else if (codProduto != 0)
                {
                    pedidos.produtos[pedidos.tamPilha] = codProduto;
                    pedidos.tamPilha++;
                    pedidos.valor_pedido += precos[codProduto];
                }
                system("cls");
            } while (codProduto != 0 and pedidos.tamPilha < MAXTAM);

            cout << "Distância p/ entrega: ";
            cin >> pedidos.distancia;

            Empilha(&mochila, pedidos);
            codPedido = codPedido + 1;
            system("pause");
            system("cls");

            break;

            // No caso 2, serão mostrados os pedidos realizados e seus respectivos códigos
            // na ordem em que foram feitos (empilhados).

        case 2:

            if (VerificaPilhaVazia(&mochila))
            {
                cout << "Lista de pedidos vazia.\n\n";
                system("pause");
                system("cls");
            }
            else
            {
                ImprimePilha(&mochila);
                system("pause");
                system("cls");
            }

            break;

            // No caso 3, apenas uma função para imprimir o cardápio.

        case 3:

            ImprimeCardapio();
            system("pause");
            system("cls");

            break;

            // No caso 4, a função "Consulta" irá percorrer toda a pilha, com um "for" para imprimir
            // apenas um pedido específico, de acordo com ID apresentado pelo usuário.

        case 4:

            int id;

            cout << "Digite o ID do pedido: ";
            cin >> id;

            x = Consulta(&mochila, id);
            cout << "ID do pedido: " << mochila.ped[x].pedido << endl;
            cout << "Distância: " << mochila.ped[x].distancia << endl;
            cout << "Valor total do pedido: " << mochila.ped[x].valor_pedido << endl;
            cout << "Código dos pedidos: ";
            for (int i = 0; i < MAXTAM; i++)
            {
                cout << mochila.ped[x].produtos[i] << " ";
            }

            system("pause");
            system("cls");

            break;

            // O caso 5 é o mais importante para o entregador.
            // A função serve para criar 2 pilhas auxiliares para receber a pilha anteriormente criada.
            // Nelas serão organizados os pedidos em ordem de distância: o mais distante será entregue por último, e o menos
            // distante, obviamente será colocado no topo da pilha, como prioritário.

        case 5:

            if (VerificaPilhaVazia(&mochila))
            {
                cout << "Pilha Vazia!" << endl;
                break;
            }

            CriaPilhaVazia(&aux1);
            CriaPilhaVazia(&aux2);

            tamanhoPilha = mochila.tamanho;

            while (mochila.tamanho != 0)
            {
                Desempilha(&mochila, &pedidos);
                Empilha(&aux1, pedidos);
            }

            for (int i = 0; i < tamanhoPilha; i++)
            {
                maiorDistancia = -1;
                idMaiorDistancia = 0;

                while (aux1.tamanho != 0)
                {
                    Desempilha(&aux1, &pedidos);
                    Empilha(&aux2, pedidos);
                    if (maiorDistancia < pedidos.distancia)
                    {
                        maiorDistancia = pedidos.distancia;
                        idMaiorDistancia = pedidos.pedido;
                    }
                }
                while (aux2.tamanho != 0)
                {
                    Desempilha(&aux2, &pedidos);
                    if (pedidos.pedido == idMaiorDistancia)
                    {
                        Empilha(&mochila, pedidos);
                    }
                    else
                    {
                        Empilha(&aux1, pedidos);
                    }
                }
            }
            cout << "Mochila organizada. (Acessar <Listar pedidos> no menu)\n\n"
                 << endl;

            break;

            // O caso 6 coloca o caso 5 em prática:
            // A cada vez que o caso 6 é seleciondo, a entrega que está no topo da pilha será realizada.

        case 6:

            if (VerificaPilhaVazia(&mochila))
            {
                cout << "Mochila vazia.\n\n";
            }
            else
            {
                Desempilha(&mochila, &pedidos);
                cout << "ID do pedido entregue: " << pedidos.pedido << endl
                     << endl;
            }
            system("pause");
            system("cls");

            break;

            // O "default" receberá qualquer número maior que 6 para fechar o programa e salvar as
            // informações registradas num arquivo binário com o nome "lanchonete.bin".

        default:

            cout << "\n\nVolte sempre!\n\n";
            system("pause");
        }

    } while (escolha != 7);

    file = fopen("lanchonete.bin", "w");
    tamanhoMochila = mochila.tamanho;
    for (int i = 0; i < tamanhoMochila; i++)
    {
        Desempilha(&mochila, &pedidos);
        fwrite(&pedidos, sizeof(Pedido), 1, file);
    }
}