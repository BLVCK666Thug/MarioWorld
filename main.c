#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"


int main(void)
{
    int done=0;

    initialiser();

    while(!done)
    {
        done=deplacer();

        afficher();
    }

    freememory();


    return EXIT_SUCCESS;
}
