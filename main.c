#include <stdio.h>
#include <stdlib.h>
#include "arguments.h"
#include "csv.h"
#include "sir.h"
#include "svg.h" 

int main(int argc, char *argv[]) {
    
    //Argumenty
    Argumenty arg;
    nacitaj_argumenty(argc, argv, &arg);

    printf("Parametre:\n");
    printf(" - Infekcne dni: %d\n", arg.doba_nakazenia);
    printf(" - Nakazlivost: %.2f\n", arg.nakazlivost);
    printf(" - Subor: %s\n", arg.vstupny_subor);
    printf(" - Vystup: %s\n\n", arg.vystupny_subor); 

    //CSV
    CSV data;
    load_csv(arg.vstupny_subor, &data);

    printf("Nacitane data:\n");
    printf(" - Pocet dni: %d\n", data.dni);
    printf(" - Celkova populacia: %d\n\n", data.populacia);

    //SIR
    // Vypocet parametrov b a y podla zadania
    double b = arg.nakazlivost;
    double y = 1.0 / arg.doba_nakazenia; 
    int populacia = data.populacia;

    //Alokujeme pole kde budeme ukladať dáta predpovede
    SIR *model = malloc(data.dni * sizeof(SIR));


    //Nastavenie prvého dňa podľa dát z CSV
    SIR model_stav;
    model_stav.susceptible = (double)data.zaznam[0].susceptible / populacia;
    model_stav.infected = (double)data.zaznam[0].infected / populacia;
    model_stav.recovered = (double)data.zaznam[0].recovered / populacia;

    //Simulácia modelu
    for (int i = 0; i < data.dni; i++) {
        
        //Ulozime si aktualny stav
        model[i] = model_stav;

        //Vypocitame stav pre dalsi den
        model_stav = sir_novy(model_stav, b, y);
    }

    //Vykreslenie grafu
    uloz_graf(arg.vystupny_subor, &data, model, data.dni, data.populacia);


    free(model);
    free_csv(&data);
    return 0;
}