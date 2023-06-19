#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_FABRICANTES 5
#define MAX_PRODUTOS 50

// Definição da struct Fabricante
struct Fabricante
{
    char marca[100];
    char site[100];
    char telefone[100];
    char UF[3];
};

// Definição da struct Produto
struct Produto
{
    char descricao[100];
    float peso;
    float valorCompra;
    float valorVenda;
    float valorLucro;
    float percentualLucro;
    struct Fabricante fabricante;
};

// Função para obter informações do fabricante
struct Fabricante obterFabricante(int fabricanteNum)
{
    struct Fabricante fabricante;
    printf("\nFabricante %d:\n", fabricanteNum);
    printf("Marca: ");
    fflush(stdin);
    fgets(fabricante.marca, sizeof(fabricante.marca), stdin);
    printf("Site: ");
    fflush(stdin);
    fgets(fabricante.site, sizeof(fabricante.site), stdin);
    printf("Telefone: ");
    fflush(stdin);
    fgets(fabricante.telefone, sizeof(fabricante.telefone), stdin);
    printf("UF: ");
    fflush(stdin);
    fgets(fabricante.UF, sizeof(fabricante.UF), stdin);
    return fabricante;
}

// Função para obter informações do produto
struct Produto obterProduto(int produtoNum, const struct Fabricante *fabricantes, int numFabricantes)
{
    struct Produto produto;
    fflush(stdin);
    printf("\nProduto %d:\n", produtoNum);
    printf("Descrição: ");
    fflush(stdin);
    fgets(produto.descricao, sizeof(produto.descricao), stdin);
    printf("Peso: ");
    scanf("%f", &produto.peso);
    printf("Valor de Compra: ");
    scanf("%f", &produto.valorCompra);
    printf("Valor de Venda: ");
    scanf("%f", &produto.valorVenda);

    // Limpar o buffer de entrada
    while (getchar() != '\n')
        continue;

    // Calcular o valor do lucro e o percentual de lucro
    produto.valorLucro = produto.valorVenda - produto.valorCompra;
    produto.percentualLucro = (produto.valorLucro / produto.valorCompra) * 100;

    // Obter o número do fabricante do produto
    int numFabricante;
    printf("Número do Fabricante (1-%d): ", numFabricantes);
    scanf("%d", &numFabricante);

    if (numFabricante < 1)
        numFabricante = 1;
    else if (numFabricante > numFabricantes)
        numFabricante = numFabricantes;

    // Limpar o buffer de entrada
    while (getchar() != '\n')
        continue;

    // Associar o fabricante ao produto
    produto.fabricante = fabricantes[numFabricante - 1];

    return produto;
}

// Função para exibir as Informações dos produtos em formato de tabela
void exibirProdutos(const struct Produto *produtos, int numProdutos)
{
    int i;
    printf("\nInformações dos produtos:\n");
    printf("+------+-------------------------+--------+--------------+--------------+---------+---------+\n");
    printf("|  Nï¿½  |       Descrição       |  Peso  | Valor Compra | Valor Venda  |  Lucro  |  %% Lucro |\n");
    printf("+------+-------------------------+--------+--------------+--------------+---------+---------+\n");

    for (i = 0; i < numProdutos; i++)
    {
        printf("|%4d", i + 1);
        printf("|%-23.23s", produtos[i].descricao);
        printf("|%6.2f", produtos[i].peso);
        printf("|%12.2f", produtos[i].valorCompra);
        printf("|%12.2f", produtos[i].valorVenda);
        printf("|%7.2f", produtos[i].valorLucro);
        printf("|%7.2f|\n", produtos[i].percentualLucro);
    }

    printf("+------+-------------------------+--------+--------------+--------------+---------+---------+\n");
}

// Funï¿½ï¿½o para exibir o menu e executar a opï¿½ï¿½o selecionada
void exibirMenu(const struct Produto *produtos, int numProdutos, const struct Fabricante *fabricantes, int numFabricantes)
{
    int opcao;
    int i, j;

    do
    {
        printf("\n[1] Listar todas as marcas\n");
        printf("[2] Listar todos os produtos\n");
        printf("[3] Listar os produtos de um determinado estado\n");
        printf("[4] Listar os produtos de uma determinada marca\n");
        printf("[5] Apresentar o(s) estado(s) onde estão registrado o produto mais caro\n");
        printf("[6] Apresentar o(s) fabricante(s) onde estão registrado o produto mais barato\n");
        printf("[7] Listar todos os produtos em ordem crescente de valor\n");
        printf("[8] Listar todos os produtos em ordem crescente de maior 'valor do lucro'\n");
        printf("[9] Listar todos os produtos em ordem crescente de maior 'percentual de lucro'\n");
        printf("[0] Sair do programa\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            // Listar todas as marcas
            printf("\nMarcas:\n");
            for (i = 0; i < numFabricantes; i++)
            {
                printf("%s\n", fabricantes[i].marca);
            }
            break;

        case 2:
            // Listar todos os produtos
            exibirProdutos(produtos, numProdutos);
            break;

        case 3:
            // Listar os produtos de um determinado estado
            {
                char estado[3];
                printf("\nDigite o estado (UF) desejado: ");
                fflush(stdin);
                fgets(estado, sizeof(estado), stdin);
                estado[strlen(estado) - 1] = '\0'; // Remover o caractere de nova linha

                printf("\nProdutos do estado (%s):\n", estado);
                for (i = 0; i < numProdutos; i++)
                {
                    if (strcmp(produtos[i].fabricante.UF, estado) == 0)
                    {
                        printf("%s\n", produtos[i].descricao);
                    }
                }
            }
            break;

        case 4:
            // Listar os produtos de uma determinada marca
            {
                char marca[100];
                printf("\nDigite a marca desejada: ");
                fflush(stdin);
                fgets(marca, sizeof(marca), stdin);
                marca[strlen(marca) - 1] = '\0'; // Remover o caractere de nova linha

                printf("\nProdutos da marca (%s):\n", marca);
                for (i = 0; i < numProdutos; i++)
                {
                    if (strcmp(produtos[i].fabricante.marca, marca) == 0)
                    {
                        printf("%s\n", produtos[i].descricao);
                    }
                }
            }
            break;

        case 5:
            // Apresentar o(s) estado(s) onde estão registrado o produto mais caro
            {
                float maiorValor = produtos[0].valorVenda;

                for (i = 1; i < numProdutos; i++)
                {
                    if (produtos[i].valorVenda > maiorValor)
                    {
                        maiorValor = produtos[i].valorVenda;
                    }
                }

                printf("\nEstado(s) onde estão registrado o produto mais caro:\n");
                for (i = 0; i < numProdutos; i++)
                {
                    if (produtos[i].valorVenda == maiorValor)
                    {
                        printf("%s\n", produtos[i].fabricante.UF);
                    }
                }
            }
            break;

        case 6:
            // Apresentar o(s) fabricante(s) onde estï¿½ registrado o produto mais barato
            {
                float menorValor = produtos[0].valorVenda;

                for (i = 1; i < numProdutos; i++)
                {
                    if (produtos[i].valorVenda < menorValor)
                    {
                        menorValor = produtos[i].valorVenda;
                    }
                }

                printf("\nFabricante(s) onde estão registrado o produto mais barato:\n");
                for (i = 0; i < numProdutos; i++)
                {
                    if (produtos[i].valorVenda == menorValor)
                    {
                        printf("%s\n", produtos[i].fabricante.marca);
                    }
                }
            }
            break;

        case 7:
            // Listar todos os produtos em ordem crescente de valor
            {
                struct Produto produtosOrdenados[MAX_PRODUTOS];
                memcpy(produtosOrdenados, produtos, sizeof(struct Produto) * numProdutos);

                // Bubble Sort
                for (i = 0; i < numProdutos - 1; i++)
                {
                    for (j = 0; j < numProdutos - i - 1; j++)
                    {
                        if (produtosOrdenados[j].valorVenda > produtosOrdenados[j + 1].valorVenda)
                        {
                            struct Produto temp = produtosOrdenados[j];
                            produtosOrdenados[j] = produtosOrdenados[j + 1];
                            produtosOrdenados[j + 1] = temp;
                        }
                    }
                }

                printf("\nProdutos em ordem crescente de valor:\n");
                exibirProdutos(produtosOrdenados, numProdutos);
            }
            break;

        case 8:
            // Listar todos os produtos em ordem crescente de maior "valor do lucro"
            {
                struct Produto produtosOrdenados[MAX_PRODUTOS];
                memcpy(produtosOrdenados, produtos, sizeof(struct Produto) * numProdutos);

                // Bubble Sort
                for (i = 0; i < numProdutos - 1; i++)
                {
                    for (j = 0; j < numProdutos - i - 1; j++)
                    {
                        if (produtosOrdenados[j].valorLucro > produtosOrdenados[j + 1].valorLucro)
                        {
                            struct Produto temp = produtosOrdenados[j];
                            produtosOrdenados[j] = produtosOrdenados[j + 1];
                            produtosOrdenados[j + 1] = temp;
                        }
                    }
                }

                printf("\nProdutos em ordem crescente de maior 'valor do lucro':\n");
                exibirProdutos(produtosOrdenados, numProdutos);
            }
            break;

        case 9:
            // Listar todos os produtos em ordem crescente de maior "percentual de lucro"
            {
                struct Produto produtosOrdenados[MAX_PRODUTOS];
                memcpy(produtosOrdenados, produtos, sizeof(struct Produto) * numProdutos);

                // Bubble Sort
                for (i = 0; i < numProdutos - 1; i++)
                {
                    for (j = 0; j < numProdutos - i - 1; j++)
                    {
                        if (produtosOrdenados[j].percentualLucro > produtosOrdenados[j + 1].percentualLucro)
                        {
                            struct Produto temp = produtosOrdenados[j];
                            produtosOrdenados[j] = produtosOrdenados[j + 1];
                            produtosOrdenados[j + 1] = temp;
                        }
                    }
                }

                printf("\nProdutos em ordem crescente de maior 'percentual de lucro':\n");
                exibirProdutos(produtosOrdenados, numProdutos);
            }
            break;

        
        case 'A':
		case 'a':
    		// Listar todos os produtos em ordem alfabética crescente A-Z
    		ordenarProdutosAlfabeticamente(produtos, numProdutos);
    	break;

		case 'Z':
		case 'z':
    		// Listar todas as marcas em ordem alfabética decrescente Z-A
    		ordenarMarcasAlfabeticamente(fabricantes, numFabricantes);
    	break;

        case 0:
            // Sair do programa
            printf("\nEncerrando o programa...\n");
            break;
            
        default:
            printf("\nOpção inválida! Tente novamente.\n");
            break;
        }
    } while (opcao != 0);
}

// Função para comparar dois produtos para ordenação alfabética
int compararProdutos(const void *produto1, const void *produto2)
{
    const struct Produto *p1 = (const struct Produto *)produto1;
    const struct Produto *p2 = (const struct Produto *)produto2;
    return strcmp(p1->descricao, p2->descricao);
}

// Função para comparar duas marcas para ordenação alfabética
int compararMarcas(const void *marca1, const void *marca2)
{
    const struct Fabricante *m1 = (const struct Fabricante *)marca1;
    const struct Fabricante *m2 = (const struct Fabricante *)marca2;
    return strcmp(m2->marca, m1->marca);
}

// Função para listar todos os produtos em ordem alfabética crescente A-Z
void ordenarProdutosAlfabeticamente(struct Produto *produtos, int numProdutos)
{
    qsort(produtos, numProdutos, sizeof(struct Produto), compararProdutos);
    printf("\nProdutos em ordem alfabética crescente A-Z:\n");
    exibirProdutos(produtos, numProdutos);
}

// Função para listar todas as marcas em ordem alfabética decrescente Z-A
void ordenarMarcasAlfabeticamente(struct Fabricante *fabricantes, int numFabricantes)
{
	int i;
	
    qsort(fabricantes, numFabricantes, sizeof(struct Fabricante), compararMarcas);
    printf("\nMarcas em ordem alfabética decrescente Z-A:\n");
    for (i= 0; i < numFabricantes; i++)
    {
        printf("%s\n", fabricantes[i].marca);
    }
}


int main()
{
    setlocale(LC_ALL, "Portuguese");
    struct Fabricante fabricantes[MAX_FABRICANTES];
    struct Produto produtos[MAX_PRODUTOS];

    int numFabricantes, numProdutos;
    int i;

    // Obter o número de fabricantes
    do
    {
        printf("Digite o número de fabricantes (2-%d): ", MAX_FABRICANTES);
        scanf("%d", &numFabricantes);
        while (getchar() != '\n')
            continue;
    } while (numFabricantes < 1 || numFabricantes > MAX_FABRICANTES);

    // Obter informações dos fabricantes
    for (i = 0; i < numFabricantes; i++)
    {
        fabricantes[i] = obterFabricante(i + 1);
    }

    // Obter o número de produtos
    do
    {
        printf("\nDigite o número  de produtos (5-%d): ", MAX_PRODUTOS);
        scanf("%d", &numProdutos);
        while (getchar() != '\n')
            continue;
    } while (numProdutos < 1 || numProdutos > MAX_PRODUTOS);

    // Obter informações dos produtos
    for (i = 0; i < numProdutos; i++)
    {
        produtos[i] = obterProduto(i + 1, fabricantes, numFabricantes);
    }

    // Exibir as informações dos produtos em formato de tabela
    // exibirProdutos(produtos, numProdutos);

    // Exibir o menu e executar a opção selecionada
    exibirMenu(produtos, numProdutos, fabricantes, numFabricantes);

    return 0;
}
