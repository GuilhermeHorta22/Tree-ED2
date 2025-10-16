#include<stdlib.h>
#include<conio2.h>
#include<ctype.h>
#include<string.h>

struct tree
{
	int info;
	struct tree *esq, *dir;
};
typedef struct tree Tree;

//funcao que cria um novo n� para arvore
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

//quantidade de n� na arvore RECURSIVO - p�s ordem
void quantidadeNo(Tree *raiz, int *qtde)
{
	if(raiz != NULL)
	{
		quantidadeNo(raiz->esq, &*qtde);
		quantidadeNo(raiz->dir, &*qtde);
		(*qtde)++;
	}
}

//quantidade de n� na arvore INTERATIVO
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

//buscar um n� da arvore de maneira INTERATIVA


//buscar um n� na arvore de maneira RECURSIVA


//pr� ordem RECURSIVO


//pr� ordem INTERATIVO


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
