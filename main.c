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
        analizatorSkladni(argv[1]);
    }
    return 0;
}