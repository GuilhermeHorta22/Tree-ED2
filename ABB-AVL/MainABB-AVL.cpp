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


//quantidade de nó na arvore


//localiza nó na arvore


//inserir um valor na arvore ABB de maneira INTERATIVA


//inserir um valor na arvore ABB de maneira RECURSIVA


//buscar um nó da arvore de maneira INTERATIVA


//buscar um nó na arvore de maneira RECURSIVA


//pré ordem RECURSIVO


//pré ordem INTERATIVO


//in ordem RECURSIVO


//in ordem INTERATIVO


//pos ordem RECURSIVO


//pos ordem INTERATIVO
