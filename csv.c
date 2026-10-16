#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"

void load_csv(const char *nazov_suboru, CSV *data){

    FILE *file = fopen(nazov_suboru,"r");

    //zistenie poctu riadkov
    int rows = 0;
    char buffer[100];

    while (fgets(buffer, 100, file) != NULL)
    {
        rows++;
    }

    data->dni = rows;

    //alokacia pamate
    data->zaznam = malloc(rows * sizeof(Riadok));

    rewind(file);

     //prechádzanie CSV súboru a ukladanie dát
    int i = 0;
    while (fgets(buffer, 100, file) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        char *sus = strtok(buffer, ","); 
        data->zaznam[i].susceptible = atoi(sus);

        char *inf = strtok(NULL, ","); 
        data->zaznam[i].infected = atoi(inf);

        char *rec = strtok(NULL, ",");
        data->zaznam[i].recovered = atoi(rec);

        i++; 
    }
    fclose(file);
    //výpočet celkovej populácie
    data->populacia = data->zaznam[0].susceptible + data->zaznam[0].infected +  data->zaznam[0].recovered;
}

void free_csv(CSV *data){
    free(data->zaznam);
}