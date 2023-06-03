#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>


	typedef struct {
		char descricao[1000];
		char fabricante[49];
		float peso;
		float valorCompra;
		float valorVenda;
		float lucro; 
		float lucroPercent;
	}Produto;
	
	typedef struct {
		char nomeMarca[50];
		char site[50];
		char uf[3];
		float telefone;
	}Fabricante;
	
int main(){
	
	setlocale(LC_ALL, "Portuguese");
	
	int i=0, numProdutos=0;	
	Produto produto;
	Fabricante fabricante;
	
	produto = valida_produto();
	fabricante = valida_fabricante();
	menu();
	
}

Produto valida_produto(){
	
	int i=0, numProdutos=0;
	Produto produto[49];

	printf("\t\t\t-----CADASTRO DO PRODUTO-----\n\n");
			
	do{
		printf("Quantas unidades serão cadastradas?\n\n");
		printf("--> ");
		scanf("%d", &numProdutos);
			if(numProdutos<2 || numProdutos>50){
				system("cls");
				printf("\t\t\t------CADASTRO DE PRODUTO-----\n\n");
				printf("!!Mínimo de 2 e máximo de 50 unidades!!\n\n");
				fflush(stdin);
			}
	}while(numProdutos<2 || numProdutos>50);
	
	for(i=0;i<numProdutos;i++){
		system("cls");
		fflush(stdin);
		printf("\n\nDescrição do produto %d--> ", i+1);
		scanf("%[^\n]s", &produto[i].descricao);
		fflush(stdin);
		system("cls");
			
		printf("\nPeso(g) --> ");
		scanf("%f", &produto[i].peso);
		system("cls");
			
		printf("\nValor de compra --> R$ ");
		scanf("%f", &produto[i].valorCompra);			
		system("cls");
			
		printf("\nValor de venda --> R$ ");
		scanf("%f", &produto[i].valorVenda);
		system("cls");	
	}
	return produto;
}

Fabricante valida_fabricante(){
	
	int j=0, numFabricantes=0;
	Fabricante fabricante[5];
	
		printf("\t\t\t-----CADASTRO DO FABRICANTE-----\n\n");
			
	do{
		printf("Quantos fabricantes serão cadastrados?\n\n");
		printf("--> ");
		scanf("%d", &numFabricantes);
			if(numFabricantes<2 || numFabricantes>5){
				system("cls");
				printf("\t\t\t-----CADASTRO DO FABRICANTE-----\n\n");
				printf("!!Mínimo de 2 e máximo de 5 fabricantes!!\n\n");
				fflush(stdin);
			}
	}while(numFabricantes<2 || numFabricantes>5);
	
	for(j=0;j<numFabricantes;j++){
		system("cls");
		fflush(stdin);
		printf("Marca %d\n\n --> ", j+1);
		scanf("%[^\n]s", &fabricante[j].nomeMarca);
		system("cls");
		
		fflush(stdin);
		printf("Site da marca\n\n --> ");
		scanf("%[^\n]s", &fabricante[j].site);
		system("cls");
		
		fflush(stdin);
		printf("Telefone\n\n --> ");
		scanf("%f", &fabricante[j].telefone);
		system("cls");
		
		fflush(stdin);
		printf("UF (Ex: UF, GO, SP, RJ)\n\n --> ");
		scanf("%[^\n]s", &fabricante[j].uf);
		system("cls");				
	}
	return fabricante;
}

int menu(int numFabricantes){
	
	int t=0, seletor=0;
	char copiaNome[50];
	struct Fabricante fabricante[5];
	
	printf("\t\t\t--------------MENU----------------\n\n");
	
	do{
		printf("Selecione uma das opções abaixo.\n\n");
		printf("[1]Lista das marcas\n");
		scanf("%d", &seletor);
			if(seletor<0 || seletor>9){
				printf("\t\t\t--------------MENU----------------\n\n");
				printf("!!Escolha uma opção válida!!\n\n");
			}
	}while(seletor<0 || seletor>9);
	
	switch(seletor){
		case 1: 
					printf("----------Marcas----------\n\nENTROU");
					strcpy(copiaNome, fabricante[t].nomeMarca);
		
			break;
	}
}
/*
#include <stdlib.h>
#include <stdio.h>
struct product {
  char *description;
  float weight;
  float purchase_value;
  float sale_value;
  float profit_value;
  float profit_percentage;
  struct manufacturer *manufacturer;
};
struct manufacturer {
  char *brand;
  char *website;
  char *phone;
  char *uf;
};

int main() {
  // Crie uma matriz de produtos.
  struct product products[50];

  // Crie uma matriz de fabricantes.
  struct manufacturer manufacturers[5];

  // Obtenha o número de produtos do usuário.
  int num_products;
  printf("Enter the number of products: ");
  scanf("%d", &num_products);

  //Obtenha os dados do produto do usuário.
  for (int i = 0; i < num_products; i++) {
    printf("Enter the product description: ");
    char *description = malloc(100 * sizeof(char));
    scanf("%s", description);

    printf("Enter the product weight: ");
    float weight;
    scanf("%f", &weight);

    printf("Enter the product purchase value: ");
    float purchase_value;
    scanf("%f", &purchase_value);

    printf("Enter the product sale value: ");
    float sale_value;
    scanf("%f", &sale_value);

    // Calculate the profit value and profit percentage.
    products[i].profit_value = sale_value - purchase_value;
    products[i].profit_percentage = products[i].profit_value / purchase_value * 100;

    // Get the manufacturer from the user.
    int manufacturer_index;
    printf("Enter the manufacturer index (0-4): ");
    scanf("%d", &manufacturer_index);

    products[i].manufacturer = manufacturers[manufacturer_index];
  }

  // Print the product data.
  for (int i = 0; i < num_products; i++) {
    printf("Product %d:\n", i + 1);
    printf("Description: %s\n", products[i].description);
    printf("Weight: %.2f\n", products[i].weight);
    printf("Purchase value: %.2f\n", products[i].purchase_value);
    printf("Sale value: %.2f\n", products[i].sale_value);
    printf("Profit value: %.2f\n", products[i].profit_value);
    printf("Profit percentage: %.2f%%\n", products[i].profit_percentage);
    printf("Manufacturer: %s\n", products[i].manufacturer->brand);
  }

  // Free the memory allocated for the products and manufacturers.
  for (int i = 0; i < num_products; i++) {
    free(products[i].description);
  }

  return 0;
}*/
