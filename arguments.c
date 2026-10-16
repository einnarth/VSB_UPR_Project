#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arguments.h"

void nacitaj_argumenty(int argc, char *argv[], Argumenty *arg){
    // nastavenie prazdnych argumentov
    arg->doba_nakazenia = 0;
    arg->nakazlivost = 0;
    strcpy(arg->vstupny_subor, "");
    strcpy(arg->vystupny_subor, "");


    //cyklus ktory prechadza argumenty
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "--real_data") == 0)
        {
            if (i+1 < argc)
            {
                strcpy(arg->vstupny_subor, argv[i+1]);
                i++;
            }
        }
        if (strcmp(argv[i], "--infectious_days") == 0)
        {
            if (i+1 < argc)
            {
                arg->doba_nakazenia = atoi(argv[i+1]);
                i++;
            }
        }
        if (strcmp(argv[i], "--infections_per_day") == 0)
        {
            if (i+1 < argc)
            {
                arg->nakazlivost = atof(argv[i+1]);
                i++;
            }
        }
        if (strcmp(argv[i], "--output") == 0)
        {
            if (i+1 < argc)
            {
                strcpy(arg->vystupny_subor, argv[i+1]);
                i++;
            }
        }
        
    }

    //kontrola parametrov
    if  ( arg->nakazlivost == 0 || arg->doba_nakazenia == 0 || strlen(arg->vystupny_subor) == 0 || strlen(arg->vstupny_subor) == 0  )
    {
        exit(1);
    }
    
}