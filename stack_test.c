#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fun_stack.h"


int main()
{
	printf("TEST 1 - poprawne dane: ");

        put_on_fun_stack(2, "funkcja <usun>");
        put_on_fun_stack(3, "funkcja <przesun>");
        put_on_fun_stack(4, "funkcja <wyjmij>");
	
	if( top_of_funstack() != 4 || strcmp(get_from_fun_stack(), "funkcja <wyjmij>") != 0) 
		printf("WYSTĄPIŁ BŁĄD\n");
	else if( top_of_funstack() != 3 || strcmp(get_from_fun_stack(), "funkcja <przesun>")!= 0)
		printf("WYSTĄPIŁ BŁĄD\n");
	else if( top_of_funstack() != 2 || strcmp(get_from_fun_stack(), "funkcja <usun>") != 0)
		printf("WYSTĄPIŁ BŁĄD\n");
	else 
		printf("DZIAŁANIE POPRAWNE\n");

	printf("TEST 2 - pusty stos: ");

	if( strcmp(get_from_fun_stack(), "Stos jest pusty") == 0 )
		printf("DZIAŁANIE POPRAWNE\n");
	else
		printf("WYSTĄPIŁ BŁĄD\n");


        printf("TEST 3 - wiele elementów: ");

        for( int i=1; i < 200; i++)
               put_on_fun_stack(i, "fun");

        if( top_of_funstack() == 199 )
                printf("DZIAŁANIE POPRAWNE\n");
        else
                printf("WYSTĄPIŁ BŁĄD\n");

        return 0;
}

