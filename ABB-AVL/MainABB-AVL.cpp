#include<stdlib.h>
#include<conio2.h>
#include<ctype.h>
#include<string.h>

#include "pilha.h"

struct tree
{
	int info;
	struct tree *esq, *dir;
};
typedef struct tree Tree;

// --- tad da minha pilha ---

//estrutura da pilha
struct TpPilha
{
	Tree *no;
	struct TpPilha *prox;
};
typedef struct TpPilha Pilha;

//funcao que inicializa minha pilha
void initPilha(Pilha **p)
{
	*p = NULL;
}

//funcao que verifica se a pilha e vazia
char isEmptyPilha(Pilha *p)
{
	return p == NULL;
}

//funcao que insere na pilha
void push(Pilha **p, Tree *raiz)
{
	Pilha *nova = (Pilha*)malloc(sizeof(Pilha));
	nova->no = raiz;
	nova->prox = *p;
	*p = nova;
}

//funcao que retira da pilha
void pop(Pilha **p, Tree **raiz)
{
	if(!isEmptyPilha(*p))
	{
		Pilha *aux = *p;
		*raiz = (*p)->no;
		*p = (*p)->prox;
		free(aux);
	}
}


// --- tad da minha arvore ABB ---

//funcao que cria um novo nó para arvore
Tree *criaNo(int info)
{
	Tree novo = (Tree*)malloc(sizeof(Tree));
	novo->info = info;
	novo->esq = novo->dir = NULL;
	return novo;
}

//inserir na arvore modelo abb e avl INTERATIVO
void inserir(Tree **raiz, int info)
{
	Tree *ant, *aux;
	
	if(*raiz == NULL)
		*raiz = criaNo(info);
	else
	{
		aux = *raiz;
		while(aux != NULL)
		{
			ant = aux;
			if(info > aux->info)
				aux = aux->dir;
			else
			if(info < aux->info)
				aux = aux->esq;
		}
		if(info > ant->info)
			ant->dir = criaNo(info);
		else
		if(info < ant->info)
			ant->esq = criaNo(info);
	}
}

//inserir um valor na arvore ABB de maneira RECURSIVA
void inserirRec(Tree **raiz, int info)
{
	if(*raiz == NULL) //criterio de parada da recursividade
		*raiz = criaNo(info);
	else
	{
		if(info > (*raiz)->info)
			inserirRec(&(*raiz)->dir, info);
		else
		if(info < (*raiz)->info)
			inserirRec(&(*raiz)->esq, info);
	}
}

//quantidade de nó na arvore RECURSIVO - pós ordem
void quantidadeNo(Tree *raiz, int *qtde)
{
	if(raiz != NULL)
	{
		quantidadeNo(raiz->esq, &*qtde);
		quantidadeNo(raiz->dir, &*qtde);
		(*qtde)++;
	}
}

//quantidade de nó na arvore INTERATIVO
void quantidadeNoInt(Tree *raiz, int *qtde) //utiliza o pre ordem interativo
{
	Pilha *p;
	init(&p);
	push(&p, raiz);
	
	while(!isEmpty(p))
	{
		pop(&p, &raiz);
		
		while(raiz != NULL)
		{
			(*qtde)++;
			push(&p, raiz);
			raiz = raiz->esq;
		}
		pop(&p, &raiz);
		raiz = raiz->dir;
		if(raiz != NULL)
			push(&p, raiz);
	}
}

//buscar um nó da arvore de maneira INTERATIVA
Tree *buscarNo(Tree *raiz, int info)
{	
	if(raiz == NULL)
		return NULL;
	else
	{
		while(raiz != NULL && info != raiz->info)
		{
			if(info > raiz->info)
				raiz = raiz->dir;
			else
				raiz = raiz->esq;
		}
		if(raiz != NULL && info == raiz->info)
			return raiz;
		else
			return NULL;
	}
}

//funcao que busca o pai de um no na arvore
void buscarPai(Tree *raiz, int info, Tree **pai)
{
	if(raiz == NULL)
	{
		*pai = NULL;
		printf("\nArvore vazia!");
	}
	else
	{
		Tree *auxPai = raiz;
		while(raiz != NULL && info != raiz->info)
		{
			auxPai = raiz;
			if(info > raiz->info)
				raiz = raiz->dir;
			else
				raiz = raiz->esq;
		}
		
		if(raiz != NULL)
			*pai = auxPai;
		else
			*pai = NULL;
	}
}

//buscar um nó na arvore de maneira RECURSIVA
void buscarNoRec(Tree *raiz, int info, Tree **no)
{
	if(raiz != NULL)
	{
		if(info == raiz->info)
			*no = raiz;
		else
		if(info > raiz->info)
			buscarNoRec(raiz->dir, info, &*no);
		else
			buscarNoRec(raiz->esq, info, &*no);
	}
}

/*
		Ligacoes para ser tratadas:
		1- e é folha
			1.1- e != pai
				1.1.1- e->info > pai->info (lado direito)
					pai->dir = NULL;
					free(e);
		
				1.1.2- e->info < pai->info (lado esquerdo)
					pai->esq = NULL;
					free(e);
		
			1.2- e == pai
				*raiz = NULL;
				free(e);
		
		2- e tem 1 filho
			2.1- e != pai
				2.1.1- e->info > pai->info
					2.1.1.1- e->esq != NULL
						pai->dir = e->esq;
						free(e);
					
					2.1.1.2- e->dir != NULL
						pai->dir = e->dir;
						free(e);
						
				2.1.2- e->info < pai->info
					2.1.2.1- e->esq != NULL
						pai->esq = e->esq;
						free(e);
					
					2.1.2.2- e->dir != NULL
						pai->esq = pai->dir;
						free(e);
			2.2- e == pai
				2.2.1- e->esq != NULL
					*raiz = e->esq;
					free(e);
					
				2.2.2- e->dir != NULL
				*raiz = e->dir;
				free(e);
		
		3- e tem 2 filhos
		else
		{
			paiSub = e;
			sub = e->dir;
			while(sub->esq != NULL)
			{
				paiSub = sub;
				sub = sub->esq;
			}
			aux = sub->info;
			exclusao(&*raiz, sub, paiSub);
			e->info = aux;
		}
					
			
quando um no tem 2 filhos e a exclusao for para o lado esquerdo temos que procurar o maior no do lado
esquerdo e se caso for para direita temos que procurar o menor no da direita do no
*/

//excluir um nodo da arvore 
void exclusao(Tree **raiz, Tree *e, Tree *pai) //e = o nodo que queremos excluir
{
	if(e->esq == NULL && e->dir == NULL) //1 - no folha é quando ele não tem filhos
	{
		if(e != pai) // 1.1
		{
			if(e->info > pai->info) //1.1.1
				pai->dir = NULL;
			else //1.2
				pai->esq = NULL;
		}
		else //1.2
			*raiz = NULL;
		free(e);
	}
	else
	if(e->esq == NULL  || e->dir == NULL) //2 - o no tem pelo menos um filho
	{
		if(e != pai) //2.1
		{
			if(e->info > pai->info) //2.1.1
			{
				if(e->esq != NULL) //2.1.1.1
					pai->dir = e->esq;
				else
				if(e->dir != NULL) //2.1.1.2
					pai->dir = e->dir;
			}
			else //2.1.2
			{
				if(e->esq != NULL) //2.1.2.1
					pai->esq = e->esq;
				else
				if(e->dir != NULL) //2.1.2.2
					pai->esq = e->dir; 
			}
		}
		else //2.2
		{
			if(e->esq != NULL) //2.2.1
				*raiz = e->esq;
			else
			if(e->dir != NULL) //2.2.2
				*raiz = e->dir;
		}
		free(e);
	}
	else // 3
	{
		int aux;
		Tree *paiSub = e;
		Tree *sub = e->dir;
		
		while(sub->esq != NULL)
		{
			paiSub = sub;
			sub = sub->esq;
		}
		aux = sub->info;
		exclusao(&*raiz, sub, paiSub);
		e->info = aux;
	}
}

//funcao principal para exclusao
void excluirNo(Tree **raiz)
{
	int auxInfo;
	Tree *e = NULL, *pai = NULL;
	
	printf("\nInfo para exclusao: ");
	scanf("%d",&auxInfo);
	
	buscarPai(*raiz, auxInfo, &pai);
	
	if(pai != NULL) //achou
	{
		if(pai->esq->info == auxInfo) //se o valor que vamos excluir é o da direita
			e = pai->esq;
		else
		if(pai->dir->info == auxInfo)
			e = pai->dir;
		
		exclusao(&*raiz, e, pai);
		
		printf("\nExclusao finalizada!");
		getch();
	}
	else
		printf("\nInfo nao encontrada!");
}

//funcao que exibe uma arvore montada
void exibe(Tree *raiz, int x, int y, int dist)
{
	if(raiz != NULL)
	{
		gotoxy(x,y);
		printf("%d",raiz->info);
		
		if(raiz->esq != NULL)
		{
			gotoxy(x-dist/2,y+1);
			printf("/");
		}
		if(raiz->dir != NULL)
		{
			gotoxy(x+dist/2,y+1);
			printf("\\");
		}
		exibe(raiz->esq, x-dist, y+2, dist/2);
		exibe(raiz->dir, x+dist, y+2, dist/2);
	}
}

//pré ordem RECURSIVO


//pré ordem INTERATIVO


//in ordem RECURSIVO


//in ordem INTERATIVO


//pos ordem RECURSIVO


//pos ordem INTERATIVO
void posOrdemInt(Tree *raiz)
{
	Pilha *p1, *p2;
	init(&p1);
	init(&p2);
	
	push(&p1, raiz);
	push(&p2, raiz);
	while(!isEmpty(p1))
	{
		if(raiz != NULL)
		{
			pop(&p1, &raiz);
			while(raiz != NULL);
			{
				push(&p1, raiz);
				push(&p2, raiz);
				raiz = raiz->dir; //anda primeiro para direita para ser um pos ordem
			}
		}
		pop(&p1, &raiz);
		raiz = raiz->esq;
		if(raiz != NULL)
			push(&p1, raiz);
	}
	
	//apenas retira da pilha e exibe os valores na ordem certa
	while(!isEmpty(p2))
	{
		pop(&p2, &raiz);
		printf("\n%d", raiz->info);
	}
}

//outra maneira de fazer o pos ordem interativo
void posOrdemInt2(Tree *raiz)
{
	Pilha *p1, *p2;
	init(&p1);
	init(&p2);
	push(&p1, raiz);
	
	while(!isEmpty(p1))
	{
		pop(&p1, &raiz);
		push(&p2, raiz);
		
		if(raiz->esq != NULL)
			push(&p1, raiz->esq);
		if(raiz->dir != NULL)
			push(&p1, raiz->dir);
	}
	
	while(!isEmpty(p2))
	{
		pop(&p2, &raiz);
		printf("\n%d",raiz->info);
	}
}
