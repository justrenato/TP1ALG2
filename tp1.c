#include <stdio.h>
#include <stdlib.h>

#define numMaxItens 50
#define tamMax 200
typedef struct itemCardapio
{
	int id;
	char nome[100];
	char descricao[500];
	float preco;
	struct itemCardapio *ant;
	struct itemCardapio *prox;
} itemCardapio;

itemCardapio inicioCardapio;

/*FUNÇÕES PARA LISTA DE ITENS DO CARDAPIO*/

void inicLista(itemCardapio* cardapio)
{
	cardapio->prox = cardapio;
	cardapio->ant = cardapio;

	/*	printf("endereço cardapio: %p\n",cardapio );
		printf("ponteiro prox: %p\n",cardapio->prox );
		printf("ponteiro aux: %p\n",cardapio->ant);
		printf("id: %d\n",cardapio->id );
		printf("preço: %2.2f\n",cardapio->preco );
	*/
};

void insereLista(itemCardapio* cardapio)
{
	int continua=1, numItens=0;
	while(continua){
		/*Esta parte cria e adiciona um novo elemento ao fim da lista*/
		numItens++;
		cardapio->ant->prox = (itemCardapio*) malloc (sizeof (itemCardapio));
		cardapio->ant->prox->prox = cardapio;
		cardapio->ant->prox->ant = cardapio->ant;
		cardapio->ant = cardapio->ant->prox;

		/*Esta parte Le os valores do ultimo item como nome, descrição, preço etc*/
		cardapio->ant->id = numItens;
		printf("Digite o nome do item: ");
		scanf("%[^\n]%*c",cardapio->ant->nome);
		printf("Digite a descrição do item: ");
		scanf("%[^\n]%*c",cardapio->ant->descricao);
		printf("Digite o preço do item: ");
		scanf("%f",&cardapio->ant->preco);
		scanf("%*c");//essa linha limpa a entrada de dados para o programa nao pular nenhuma leitura de dado

		/*Infos sobre o ultimo item registrado */
		// printf("\n");
		// printf("\t\tItem Registrado com sucesso:\n\n");
		// printf("\t\tItem numero %d\n",cardapio->ant->id);
		// printf("\tNome: %s\n",cardapio->ant->nome );
		// printf("\tDescrição: %s\n",cardapio->ant->descricao );
		// printf("\tPreço: %2.2f\n", cardapio->ant->preco);
		// printf("\n");

		printf("Deseja inserir novo item? Digite 1 para sim ou 0 para não\n");
		scanf("%d",&continua);
		scanf("%*c");
	}
}

int vaziaLista(itemCardapio* cardapio)
{
	/*se o ponteiro prox apontar pro proprio cardapio, entao lista vazia.*/
	return (cardapio->prox==cardapio);
}

void imprimeLista (itemCardapio* cardapio)
{
	itemCardapio* aux;
	if (vaziaLista(&inicioCardapio)) puts("Nenhum item na lista"); 
	else {
		aux = cardapio->prox;
		while (aux != cardapio){
		printf("\n");
		printf("\t\tItem numero %d\n",aux->id);
		printf("\tNome: %s\n",aux->nome );
		printf("\tDescrição: %s\n",aux->descricao );
		printf("\tPreço: %2.2f\n", aux->preco);
		printf("\n");

		aux = aux->prox;

		}
	}
}




/*FUNÇOES PARA FILA DE CLIENTES*/
typedef struct filaClientes
{
	int posicaoFila;
	char nome[100];
	float conta;
	int qntItens;
	int codItens[numMaxItens];
	struct filaClientes* prox;
} filaClientes;

typedef struct tipoFila
{
	filaClientes* frente;
	filaClientes* final;
} tipoFila;

tipoFila inicioClientes;

void inicFila(tipoFila* fila)
{
	fila->frente = (filaClientes*) malloc (sizeof (filaClientes));
	fila->final = fila->frente;
	fila->final->prox = NULL;
}

int numcliente=0;
void enfileira(tipoFila* fila,itemCardapio* cardapio){
	int inserirCliente=1,insereItem=1,qntItens=0;
	itemCardapio* aux;
	while(inserirCliente){
		int i=0;
		aux=cardapio->prox;
		numcliente++;
		fila->final->prox = (filaClientes*) malloc (sizeof(filaClientes));
		fila->final = fila->final->prox;
		fila->final->prox=NULL;
		// scanf("%*c");
		fila->final->posicaoFila = numcliente;
		fila->final->qntItens=0;
		printf("Digite o nome do cliente:\n");
		scanf("%[^\n]",fila->final->nome);
		insereItem=1;
		while((insereItem)&&(i<numMaxItens)){
			fila->final->qntItens++;
			printf("Digite o numero do item consumido pelo cliente\n");
			scanf("%d",&fila->final->codItens[i]);

			while(aux->id!=fila->final->codItens[i]){
				aux=aux->prox;
			}
			fila->final->conta = fila->final->conta + aux->preco;


			i++;
			printf("O cliente consumiu outro item? 1- Sim. 0- Não.\n");
			scanf("%d",&insereItem);
			scanf("%*c");
		}

		printf("Adicionar outro cliente? 1- Sim. 0- Não.\n");
		scanf("%d",&inserirCliente);
		scanf("%*c");
	}
}




/*FUNÇOES PILHA DE CHOCOLATE*/
typedef struct tipipilha
{
	int vet[tamMax];
	int topo;
} tipoPilha;

tipoPilha pilhaChoco;
void inicPilha(tipoPilha* pilha){
	pilha->topo=0;
}

void push (int choco, tipoPilha* pilha){
	if (pilha->topo == tamMax) puts("pilha cheia");
	else{
		pilha->vet[pilha->topo]=choco;
		pilha->topo ++;
	}
}

int vaziaPilha (tipoPilha* pilha){
	return (pilha->topo ==0);
}

int pop (tipoPilha* pilha){
	if (vaziaPilha(&pilhaChoco)) puts("pilha vazia");
	else{
		pilha->topo --;
		printf("Chocolate oferecido: %d\n",pilha->vet[pilha->topo]);
		return(pilha->vet[pilha->topo]);
	}
}


int main(int argc, char const *argv[])
{
	/*iniciando cardapio*/
	inicLista(&inicioCardapio);
	insereLista(&inicioCardapio);
	imprimeLista(&inicioCardapio);

	/*recebendo os clientes*/
	inicFila(&inicioClientes);
	enfileira(&inicioClientes,&inicioCardapio);

	/*pilha choco*/
	for (int i = 0; i < numcliente; ++i)
	{
		push(1,&pilhaChoco);
	}

	filaClientes* aux = inicioClientes.frente->prox;
	for (int i = 0; i < numcliente; ++i )
	{
		printf("cliente: %s\n",aux->nome );
		pop(&pilhaChoco);
		printf("conta: R$ %2.2f\n",aux->conta );

		aux = aux->prox;
	}



	return 0;
}