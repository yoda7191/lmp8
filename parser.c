#include <stdio.h>
#include <stdlib.h>    // exit - ale exit trzeba kiedyś usunąć i nie będzie to potrzebne
#include "alex.h"      // analizator leksykalny
#include "fun_stack.h" // stos funkcji
#include "parser.h"

#define MAXINDENTLENGTH 256 // maks długość identyfikatora

//lista wezwan funkcji
typedef struct callResult
{
  char* file;
  char* functionName;
  int line;
} callResult;
typedef struct callResultArray
{
  callResult* callResults;
  int size;
} callResultArray;


typedef struct protoResult
{
  char* file;
  char* functionName;
  int line;
} protoResult;
typedef struct protoResultArray
{
  protoResult* protoResults;
  int size;
} protoResultArray;

typedef struct defResult
{
  char* file;
  char* functionName;
  int line;
} defResult;
typedef struct defResultArray
{
  defResult* defResults;
  int size;
} defResultArray;

callResultArray callResults;
protoResultArray protoResults;
defResultArray defResults;

//sprawdzamy, czy nie przechowujemy juz tej funkcji
// int checkForFuncInStore(char* name)
// {
//   for (int i = 0; i< defResults.size; i++)
//     if (strcmp(defResults.defResults[i].functionName, name) == 0)
//       return i;
//   return -99;
// }

//dodajemy do wyniku wywolanie
void store_add_call (char* functionName, int line, char* fileName)
{
  callResults.callResults->functionName = functionName;
  callResults.callResults->file = fileName;
  callResults.callResults->line = line;
  callResults.size++;
}

//dodajemy do wyniku prototyp funkcji
void store_add_proto (char* functionName, int line, char* fileName)
{
  protoResults.protoResults->functionName = functionName;
  protoResults.protoResults->line = line;
  protoResults.protoResults->file = fileName;
  protoResults.size++;
}

//dodajemy do wyniku definicje funkcji
void store_add_def (char* functionName, int line, char* fileName)
{
  // if (checkForFuncInStore(functionName) == -99)
  //   return;
  defResults.defResults->file = fileName;
  defResults.defResults->functionName = functionName;
  defResults.defResults->line = line;
  defResults.size++;
}

void printResults()
{
  for(int i = 0; i < defResults.size; i++)
  {
    printf("Funkcja: %s \n", defResults.defResults[i].functionName);
    printf("\t Prototyp: \n");
    printf("\t\t %s linia %d\n", protoResults.protoResults[i].file, protoResults.protoResults[i].line);
    printf("\t Definicja: \n");
    printf("\t\t %s linia %d\n", defResults.defResults[i].file, defResults.defResults[i].line);
    printf("\t Uzycie\n");
    printf("\t\t %s linia %d\n", callResults.callResults[i].file, callResults.callResults[i].line);
  }
}

void analizatorSkladni (char *inpname)
{ // przetwarza plik inpname

  FILE *in = fopen(inpname, "r");

  int nbra = 0; // bilans nawiasów klamrowych {}
  int npar = 0; // bilans nawiasów zwykłych ()

  alex_init4file(in); // ustaw analizator leksykalny, aby czytał in

  lexem_t lex;

  lex = alex_nextLexem(); // pobierz następny leksem
  while (lex != EOFILE)
  {
    switch (lex)
    {
    case IDENT:
    {
      char *iname = alex_ident(); // zapamiętaj identyfikator i patrz co dalej
      lexem_t nlex = alex_nextLexem();
      if (nlex == OPEPAR) // nawias otwierający - to zapewne funkcja
      {
        npar++;
        put_on_fun_stack(npar, iname); // odłóż na stos funkcji
                                       // stos f. jest niezbędny, aby poprawnie obsłużyć sytuacje typu
                                       // f1( 5, f2( a ), f3( b ) )
      }
      else // nie nawias, czyli nie funkcja
      {
        lex = nlex;
        continue;
      }
    }
    break;

    case OPEPAR:
      npar++;
      break;

    case CLOPAR: // zamykający nawias - to może być koniec prototypu, nagłówka albo wywołania
    {
      if (top_of_funstack() == npar)
      {                                  // sprawdzamy, czy liczba nawiasów bilansuje się z wierzchołkiem stosu funkcji
                                         // jeśli tak, to właśnie wczytany nawias jest domknięciem nawiasu otwartego
                                         // za identyfikatorem znajdującym się na wierzchołku stosu
        lexem_t nlex = alex_nextLexem(); // bierzemy nast leksem

        if (nlex == OPEBRA) // nast. leksem to klamra a więc mamy do czynienia z def. funkcji
          store_add_def(get_from_fun_stack(), alex_getLN(), inpname);

        else if (nbra == 0) // nast. leksem to nie { i jesteśmy poza blokami - to musi być prototyp
          store_add_proto(get_from_fun_stack(), alex_getLN(), inpname);

        else // nast. leksem to nie { i jesteśmy wewnątrz bloku - to zapewne wywołanie
          store_add_call(get_from_fun_stack(), alex_getLN(), inpname);
      }
      npar--;
    }
    break;

    case OPEBRA:
      nbra++;
      break;

    case CLOBRA:
      nbra--;
      break;

    case ERROR:
    {
      fprintf(stderr, "\nBUUUUUUUUUUUUUUUUUUUUUU!\n"
                      "W pliku %s (linia %d) są błędy składni.\n"
                      "Kończę!\n\n",
              inpname, alex_getLN());
      exit(1); // to nie jest najlepsze, ale jest proste ;-)
    }

    break;
    default:
    break;
    }
    lex = alex_nextLexem();
  }
}
