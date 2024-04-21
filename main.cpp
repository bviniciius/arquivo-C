#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define SIZE 20

int menu();
void cria_arquivo();
void cadastro(int);
void consulta();
void exibe();

int menu(){
	int op;
	
	system("CLS");
	printf("1. CADASTRAR NUMEROS\n");
	printf("2. CONSULTAR NUMERO\n");
	printf("3. EXIBIR TODOS OS NUMEROS\n");
	printf("4. SAIR\n\n");
	printf("Sua opcao: ");
	scanf("%d",&op);
	return op;
}

void cria_arquivo(){
	FILE *f;
	
	f = fopen("numeros.dat","rb");
	if(f==NULL){
		f = fopen("numeros.dat","wb");
		printf("Arquivo criado com sucesso!\n");
		system("PAUSE");
	}
	fclose(f);

}

void cadastro(int qt){
	int num[SIZE], i;
	FILE *f;
	
	system("CLS");
	printf("**** Digite os numeros ****\n\n");
	for(i=0; i<qt; i++){
		printf("Numero[%d]: ",i+1);
		scanf("%d",&num[i]);
	}
	
	f = fopen("numeros.dat","ab");
	if(f==NULL){
		printf("Erro ao tentar abrir o arquivo!\n");
		return;
	}
	fwrite(&num,sizeof(int),qt,f);
	fclose(f);
	printf("\n===> Registro cadastrado com sucesso!\n");
}

void consulta(){
	int num, x;
	FILE *f;
	
	system("CLS");
	printf("Digite o numero: ");
	scanf("%d",&x);
	
	f = fopen("numeros.dat","rb");
	
	if(f==NULL){
		printf("Erro ao tentar abrir o arquivo!\n");
		return;
	}
	while(!feof(f)){
		fread(&num,sizeof(int),1,f);
		if(x==num){
			printf("Numero encontrado\n");
			fclose(f);
			return;
		}
	}
	fclose(f);
	printf("===> Produto nao cadastrado!\n");
}

void exibe(){
	int num, cont=1;
	FILE *f;
	
	system("CLS");
	printf("**** LISTA DE NUMEROS **** \n\n");
	f = fopen("numeros.dat","rb");
	if(f==NULL){
		printf("Erro ao tentar abrir o arquivo!\n");
		return;
	}
	printf(" ------------------\n");
	printf("|  ID  |   Numero  |\n");
	printf(" ------------------\n");
	while(!feof(f)){
		if(fread(&num,sizeof(int),1,f)){
			printf("| %2d   ",cont++);
			printf("|  %4d     |\n",num);
		}
		else{
			break;
		}
	}
	printf(" ------------------\n");
	fclose(f);
}

int main(){
	int op,qt;
	setlocale(LC_ALL,"");
	
	cria_arquivo();	
	
	do{
		op = menu();
		switch(op){
			case 1:
				printf("Quantidade de numeros para cadastrar: ");
				scanf("%d",&qt);
				if(qt>SIZE){
					printf("Tamanho invalido!\n");
				}
				else{
					cadastro(qt);
				}
				
				break;
			case 2:
				consulta();
				break;
			case 3:
				exibe();
				break;
			case 4:
				break;
			default:
				printf("\n===> Opcao invalida!");
		}
		system("PAUSE");
	}while(op!=4);
	
	return 0;
}