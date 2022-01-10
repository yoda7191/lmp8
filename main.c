#include "alex.h"
#include "parser.h"

int main(int argc, char* argv[])
{
    if (argc < 1)
    {
        printf("BLAD: Niepoprawna ilosc argumentow!\n");
        return 99;
    }
    else
    {
        for(int i = 1; i < argc; i++)
            analizatorSkladni(argv[i]);
    }
    return 0;
}