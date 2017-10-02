#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tipoelemento int;

typedef struct 
{
	int id,preco;
	char *descricao;
	struct itemCardapio *prox;
} itemCardapio;

typedef struct 
{
	itemCardapio *inicioCardapio;
	itemCardapio *finalCardapio;
} tipoLista;


void inicLista(	tipoLista *cardapio)
{
	cardapio->inicioCardapio = malloc (sizeof (itemCardapio));
	cardapio->finalCardapio = cardapio->inicioCardapio;
	cardapio->inicioCardapio->prox = NULL;	
};

void insereLista(tipoLista *cardapio){
	int cod=1;
	while(cod<10/*quiser adicionar itens no cardapio*/){
		cardapio->finalCardapio->prox = malloc (sizeof (itemCardapio));
		cardapio->finalCardapio = cardapio->finalCardapio->prox;
		cardapio->finalCardapio->id = cod;
		cod++;
		fputs("Digite o nome do item a ser inserido no cardapio: \n",stdout);
		fputs("Digite a descrição do item inserido: \n",stdout);
		fputs("Digite o preço do item inserido: \n",stdout);
		fputs("Deseja adicionar outro item? Digite 1 para sim e 0 par não: \n",stdout);
		cardapio->finalCardapio->prox = NULL;
	}
}


tipoLista cardapio;
int main(int argc, char const *argv[])
{

	inicLista(&cardapio);
	insereLista(&cardapio);

	return 0;
}