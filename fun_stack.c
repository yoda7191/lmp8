#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "fun_stack.h"
#include "global.h"

//struct SNode* top;
//top = NULL;

// funkcje niezbędne do obsługi stosu
struct SNode* newNode(int par_level, char *funame)
{
	struct SNode* sNode = malloc(sizeof(struct SNode));
	sNode->par_level = par_level;
	sNode->funame = malloc(strlen(funame) * (sizeof(*funame)+1));
	sNode->funame = strdup(funame);
	sNode->next = NULL;
	return sNode;
}


int isEmpty()
{
	return !top;	
}
	

// zwraca licznik nawiasów z funkcji na wierzchu stosu
// nie przyjmuje żadnych argumentów
int top_of_funstack()
{
	if( isEmpty() ) {
		fprintf(stderr, "Stos jest pusty");
		return 1;
	} 
	else
		return top->par_level; 
}		

// dodaje funkcję na stos - licznik nawiasów i jej nazwę
void put_on_fun_stack( int par_level, char *funame )
{
	struct SNode* sNode = newNode(par_level, funame);
    	sNode->next = top;
    	top = sNode;
}

// zwraca nazwę funkcji z wierzchołka i usuwa tę funkcję 
// nie przyjmuje argumentów 
char *get_from_fun_stack()
{
	if( isEmpty() ) {
		return "Stos jest pusty";
	}
	else {
		struct SNode* temp = top;
		top = top->next;
		char* deleted = temp->funame;
		free(temp);
		return deleted;
	}
}
