#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_FABRICANTES 5
#define MAX_PRODUTOS 50

// Definição da struct Fabricante
struct Fabricante {
    char marca[100];
    char site[100];
    char telefone[100];
    char UF[3];
};

// Definição da struct Produto
struct Produto {
    char descricao[100];
    float peso;
    float valorCompra;
    float valorVenda;
    float valorLucro;
    float percentualLucro;
    struct Fabricante fabricante;
};

// Função para obter informações do fabricante
struct Fabricante obterFabricante(int fabricanteNum) {
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
struct Produto obterProduto(int produtoNum, const struct Fabricante* fabricantes, int numFabricantes) {
    struct Produto produto;
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

// Função para exibir as informações dos produtos em formato de tabela
void exibirProdutos(const struct Produto* produtos, int numProdutos) {
    printf("\nInformações dos produtos:\n");
    printf("+------+-------------------------+--------+--------------+--------------+---------+---------+\n");
    printf("|  Nº  |       Descrição         |  Peso  | Valor Compra | Valor Venda  |  Lucro   |  %% Lucro |\n");
    printf("+------+-------------------------+--------+--------------+--------------+---------+---------+\n");

    for (int i = 0; i < numProdutos; i++) {
        printf("| %4d ", i + 1);
        printf("| %-23.23s ", produtos[i].descricao);
        printf("| %6.2f ", produtos[i].peso);
        printf("| %12.2f ", produtos[i].valorCompra);
        printf("| %12.2f ", produtos[i].valorVenda);
        printf("| %7.2f ", produtos[i].valorLucro);
        printf("| %7.2f |\n", produtos[i].percentualLucro);
    }

    printf("+------+-------------------------+--------+--------------+--------------+---------+---------+\n");
}

// Função para exibir o menu e executar a opção selecionada
void exibirMenu(const struct Produto* produtos, int numProdutos, const struct Fabricante* fabricantes, int numFabricantes) {
    int opcao;

    do {
        printf("\n[1] Listar todas as marcas");
        printf("\n[2] Listar todos os produtos");
        printf("\n[3] Listar os produtos de um determinado estado");
        printf("\n[4] Listar os produtos de uma determinada marca");
        printf("\n[5] Apresentar o(s) estado(s) onde está registrado o produto mais caro");
        printf("\n[6] Apresentar o(s) fabricante(s) onde está registrado o produto mais barato");
        printf("\n[7] Listar todos os produtos em ordem crescente de valor");
        printf("\n[8] Listar todos os produtos em ordem crescente de maior 'valor do lucro'");
        printf("\n[9] Listar todos os produtos em ordem crescente de maior 'percentual de lucro'");
        printf("\n[0] Sair do programa");
        printf("\n\nDigite a opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Listar todas as marcas
                printf("\nMarcas cadastradas:\n");
                for (int i = 0; i < numFabricantes; i++) {
                    printf("- %s", fabricantes[i].marca);
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
                    printf("\nDigite o estado desejado: ");
                    fflush(stdin);
                    fgets(estado, sizeof(estado), stdin);

                    printf("\nProdutos do estado %s:\n", estado);
                    printf("+------+-------------------------+--------+--------------+--------------+---------+---------+\n");
                    printf("|  Nº  |       Descrição         |  Peso  | Valor Compra | Valor Venda  |  Lucro   |  %% Lucro |\n");
                    printf("+------+-------------------------+--------+--------------+--------------+---------+---------+\n");

                    for (int i = 0; i < numProdutos; i++) {
                        if (strcmp(produtos[i].fabricante.UF, estado) == 0) {
                            printf("| %4d ", i + 1);
                            printf("| %-23.23s ", produtos[i].descricao);
                            printf("| %6.2f ", produtos[i].peso);
                            printf("| %12.2f ", produtos[i].valorCompra);
                            printf("| %12.2f ", produtos[i].valorVenda);
                            printf("| %7.2f ", produtos[i].valorLucro);
                            printf("| %7.2f |\n", produtos[i].percentualLucro);
                        }
                    }

                    printf("+------+-------------------------+--------+--------------+--------------+---------+---------+\n");
                }
                break;

            case 4:
                // Listar os produtos de uma determinada marca
                {
                    char marca[100];
                    printf("\nDigite a marca desejada: ");
                    fflush(stdin);
                    fgets(marca, sizeof(marca), stdin);

                    printf("\nProdutos da marca %s:\n", marca);
                    printf("+------+-------------------------+--------+--------------+--------------+---------+---------+\n");
                    printf("|  Nº  |       Descrição         |  Peso  | Valor Compra | Valor Venda  |  Lucro   |  %% Lucro |\n");
                    printf("+------+-------------------------+--------+--------------+--------------+---------+---------+\n");

                    for (int i = 0; i < numProdutos; i++) {
                        if (strcmp(produtos[i].fabricante.marca, marca) == 0) {
                            printf("| %4d ", i + 1);
                            printf("| %-23.23s ", produtos[i].descricao);
                            printf("| %6.2f ", produtos[i].peso);
                            printf("| %12.2f ", produtos[i].valorCompra);
                            printf("| %12.2f ", produtos[i].valorVenda);
                            printf("| %7.2f ", produtos[i].valorLucro);
                            printf("| %7.2f |\n", produtos[i].percentualLucro);
                        }
                    }

                    printf("+------+-------------------------+--------+--------------+--------------+---------+---------+\n");
                }
                break;

            case 5:
                // Apresentar o(s) estado(s) onde está registrado o produto mais caro
                {
                    float maxValor = produtos[0].valorVenda;

                    for (int i = 1; i < numProdutos; i++) {
                        if (produtos[i].valorVenda > maxValor) {
                            maxValor = produtos[i].valorVenda;
                        }
                    }

                    printf("\nEstado(s) onde está registrado o produto mais caro:\n");
                    for (int i = 0; i < numProdutos; i++) {
                        if (produtos[i].valorVenda == maxValor) {
                            printf("- %s", produtos[i].fabricante.UF);
                        }
                    }
                }
                break;

            case 6:
                // Apresentar o(s) fabricante(s) onde está registrado o produto mais barato
                {
                    float minValor = produtos[0].valorCompra;

                    for (int i = 1; i < numProdutos; i++) {
                        if (produtos[i].valorCompra < minValor) {
                            minValor = produtos[i].valorCompra;
                        }
                    }

                    printf("\nFabricante(s) onde está registrado o produto mais barato:\n");
                    for (int i = 0; i < numProdutos; i++) {
                        if (produtos[i].valorCompra == minValor) {
                            printf("- %s", produtos[i].fabricante.marca);
                        }
                    }
                }
                break;

            case 7:
                // Listar todos os produtos em ordem crescente de valor
                {
                    struct Produto produtosOrdenados[numProdutos];
                    memcpy(produtosOrdenados, produtos, sizeof(produtos));

                    for (int i = 0; i < numProdutos; i++) {
                        for (int j = i + 1; j < numProdutos; j++) {
                            if (produtosOrdenados[i].valorVenda > produtosOrdenados[j].valorVenda) {
                                struct Produto temp = produtosOrdenados[i];
                                produtosOrdenados[i] = produtosOrdenados[j];
                                produtosOrdenados[j] = temp;
                            }
                        }
                    }

                    exibirProdutos(produtosOrdenados, numProdutos);
                }
                break;

            case 8:
                // Listar todos os produtos em ordem crescente de maior 'valor do lucro'
                {
                    struct Produto produtosOrdenados[numProdutos];
                    memcpy(produtosOrdenados, produtos, sizeof(produtos));

                    for (int i = 0; i < numProdutos; i++) {
                        for (int j = i + 1; j < numProdutos; j++) {
                            if (produtosOrdenados[i].valorLucro > produtosOrdenados[j].valorLucro) {
                                struct Produto temp = produtosOrdenados[i];
                                produtosOrdenados[i] = produtosOrdenados[j];
                                produtosOrdenados[j] = temp;
                            }
                        }
                    }

                    exibirProdutos(produtosOrdenados, numProdutos);
                }
                break;

            case 9:
                // Listar todos os produtos em ordem crescente de maior 'percentual de lucro'
                {
                    struct Produto produtosOrdenados[numProdutos];
                    memcpy(produtosOrdenados, produtos, sizeof(produtos));

                    for (int i = 0; i < numProdutos; i++) {
                        for (int j = i + 1; j < numProdutos; j++) {
                            if (produtosOrdenados[i].percentualLucro > produtosOrdenados[j].percentualLucro) {
                                struct Produto temp = produtosOrdenados[i];
                                produtosOrdenados[i] = produtosOrdenados[j];
                                produtosOrdenados[j] = temp;
                            }
                        }
                    }

                    exibirProdutos(produtosOrdenados, numProdutos);
                }
                break;

            case 0:
                // Sair do programa
                printf("\nEncerrando o programa. Obrigado!\n");
                break;

            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    struct Fabricante fabricantes[MAX_FABRICANTES];
    struct Produto produtos[MAX_PRODUTOS];

    int numFabricantes = 0;
    int numProdutos = 0;

    printf("### Cadastro de Produtos ###\n");

    printf("\nQuantos fabricantes deseja cadastrar (até %d)? ", MAX_FABRICANTES);
    scanf("%d", &numFabricantes);

    // Limpar o buffer de entrada
    while (getchar() != '\n')
        continue;

    for (int i = 0; i < numFabricantes; i++) {
        fabricantes[i] = obterFabricante(i + 1);
    }

    printf("\nQuantos produtos deseja cadastrar (até %d)? ", MAX_PRODUTOS);
    scanf("%d", &numProdutos);

    // Limpar o buffer de entrada
    while (getchar() != '\n')
        continue;

    for (int i = 0; i < numProdutos; i++) {
        produtos[i] = obterProduto(i + 1, fabricantes, numFabricantes);
    }

    exibirMenu(produtos, numProdutos, fabricantes, numFabricantes);

    return 0;
}
