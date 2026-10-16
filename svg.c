#include <stdio.h>
#include <stdlib.h>
#include "svg.h"


void uloz_graf(const char *vystupny_subor, CSV *realita, SIR *model, int dni, int populacia) {
    FILE *f = fopen(vystupny_subor, "w");

    // Veľkosť grafu
    int sirka = 1100;
    int vyska = 600;
    int okraj = 60;

    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%d\" height=\"%d\" style=\"background-color:white\">\n", sirka, vyska);
    fprintf(f, "<text x=\"%d\" y=\"30\" font-size=\"20\" font-family=\"Arial\" text-anchor=\"middle\">SIR Model X Realita</text>\n", sirka/2);

    // Osa X a Y
    fprintf(f, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" stroke-width=\"2\" />\n", okraj, vyska - okraj, sirka - okraj, vyska - okraj);
    fprintf(f, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" stroke-width=\"2\" />\n", okraj, vyska - okraj, okraj, okraj);

    // Popis
    fprintf(f, "<text x=\"%d\" y=\"%d\" font-size=\"14\" font-family=\"Arial\" text-anchor=\"middle\">Pocet dni</text>\n", sirka/2, vyska - 10);
    fprintf(f, "<text x=\"20\" y=\"%d\" font-size=\"14\" font-family=\"Arial\" text-anchor=\"middle\" transform=\"rotate(-90 20,%d)\">Populacia</text>\n", vyska/2, vyska/2);


    double krok_x = (double)(sirka - 2 * okraj) / (dni - 1);    // Medzera medzi dňami pre X súradnice
    int graf_vyska = vyska - 2 * okraj; // Reálna výska časti, kde sa zobrazuje graf

    // Zistovanie maxima pre I a R
    int max_i_real = 0;
    int den_max_i_real = 0;

    int max_i_model = 0;
    int den_max_i_model = 0;

    int max_r_real = 0;
    int den_max_r_real = 0;

    int max_r_model = 0;
    int den_max_r_model = 0;

    for (int i = 0; i < dni; i++) {

        if (realita->zaznam[i].infected > max_i_real) {
            max_i_real = realita->zaznam[i].infected;
            den_max_i_real = i;
        }

        int model_infected = (int)(model[i].infected * populacia); // pri modeli musíme previezť na konkrétnu hodnotu z pomeru

        if (model_infected > max_i_model) {
            max_i_model = model_infected;
            den_max_i_model = i;
        }

        if (realita->zaznam[i].recovered > max_r_real) {
            max_r_real = realita->zaznam[i].recovered;
            den_max_r_real = i;
        }

        int model_recovered = (int)(model[i].recovered * populacia); // pri modeli musíme previezť na konkrétnu hodnotu z pomeru

        if (model_recovered > max_r_model) {
            max_r_model = model_recovered;
            den_max_r_model = i;
        }
    }

    // Kreslenie hodnôt
    for (int i = 0; i < dni - 1; i++) {
        int x1 = okraj + (int)(i * krok_x);
        int x2 = okraj + (int)((i + 1) * krok_x);

        // Reálna dáta - prevádzame ich na pomer
        int y1_s = vyska - okraj - (int)((realita->zaznam[i].susceptible / (double)populacia) * graf_vyska);
        int y2_s = vyska - okraj - (int)((realita->zaznam[i+1].susceptible / (double)populacia) * graf_vyska);
        fprintf(f, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"blue\" stroke-width=\"2\" opacity=\"0.5\" />\n", x1, y1_s, x2, y2_s);

        int y1_i = vyska - okraj - (int)((realita->zaznam[i].infected / (double)populacia) * graf_vyska);
        int y2_i = vyska - okraj - (int)((realita->zaznam[i+1].infected / (double)populacia) * graf_vyska);
        fprintf(f, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"red\" stroke-width=\"2\" opacity=\"0.5\" />\n", x1, y1_i, x2, y2_i);

        int y1_r = vyska - okraj - (int)((realita->zaznam[i].recovered / (double)populacia) * graf_vyska);
        int y2_r = vyska - okraj - (int)((realita->zaznam[i+1].recovered / (double)populacia) * graf_vyska);
        fprintf(f, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"green\" stroke-width=\"2\" opacity=\"0.5\" />\n", x1, y1_r, x2, y2_r);

        // Dáta z modelu
        int my1_s = vyska - okraj - (int)(model[i].susceptible * graf_vyska);
        int my2_s = vyska - okraj - (int)(model[i+1].susceptible * graf_vyska);
        fprintf(f, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"blue\" stroke-width=\"2\" stroke-dasharray=\"5,5\" />\n", x1, my1_s, x2, my2_s);

        int my1_i = vyska - okraj - (int)(model[i].infected * graf_vyska);
        int my2_i = vyska - okraj - (int)(model[i+1].infected * graf_vyska);
        fprintf(f, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"red\" stroke-width=\"2\" stroke-dasharray=\"5,5\" />\n", x1, my1_i, x2, my2_i);

        int my1_r = vyska - okraj - (int)(model[i].recovered * graf_vyska);
        int my2_r = vyska - okraj - (int)(model[i+1].recovered * graf_vyska);
        fprintf(f, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"green\" stroke-width=\"2\" stroke-dasharray=\"5,5\" />\n", x1, my1_r, x2, my2_r);
    }

    // Zobrazovanie maxím v grafe
    // Infected - Realita
    int x_real_i = okraj + (int)(den_max_i_real * krok_x);
    int y_real_i = vyska - okraj - (int)((max_i_real / (double)populacia) * graf_vyska);
    fprintf(f, "<circle cx=\"%d\" cy=\"%d\" r=\"5\" fill=\"red\" />\n", x_real_i, y_real_i);
    fprintf(f, "<text x=\"%d\" y=\"%d\" font-size=\"12\" fill=\"red\">Max I=%d</text>\n", x_real_i , y_real_i - 10, max_i_real);
    //Infected - Model
    int x_model_i = okraj + (int)(den_max_i_model * krok_x);
    int y_model_i = vyska - okraj - (int)((max_i_model / (double)populacia) * graf_vyska);
    fprintf(f, "<circle cx=\"%d\" cy=\"%d\" r=\"5\" fill=\"darkred\" />\n", x_model_i, y_model_i);
    fprintf(f, "<text x=\"%d\" y=\"%d\" font-size=\"12\" fill=\"darkred\">Max I=%d</text>\n", x_model_i , y_model_i - 10, max_i_model);
    //Recovered - Realita
    int x_real_r = okraj + (int)(den_max_r_real * krok_x);
    int y_real_r = vyska - okraj - (int)((max_r_real / (double)populacia) * graf_vyska);
    fprintf(f, "<circle cx=\"%d\" cy=\"%d\" r=\"5\" fill=\"green\" />\n", x_real_r, y_real_r);
    fprintf(f, "<text x=\"%d\" y=\"%d\" font-size=\"12\" fill=\"green\">Max R=%d</text>\n", x_real_r , y_real_r - 10, max_r_real);
    //Recovered - Model
    int x_model_r = okraj + (int)(den_max_r_model * krok_x);
    int y_model_r = vyska - okraj - (int)((max_r_model / (double)populacia) * graf_vyska);
    fprintf(f, "<circle cx=\"%d\" cy=\"%d\" r=\"5\" fill=\"darkgreen\" />\n", x_model_r, y_model_r);
    fprintf(f, "<text x=\"%d\" y=\"%d\" font-size=\"12\" fill=\"darkgreen\">Max R=%d</text>\n", x_model_r , y_model_r - 10, max_r_model);


    // Legenda
    int lx = sirka - 220;
    int ly = 80;
    fprintf(f, "<rect x=\"%d\" y=\"%d\" width=\"200\" height=\"140\" fill=\"white\" stroke=\"black\" />\n", lx - 10, ly - 20);
    fprintf(f, "<text x=\"%d\" y=\"%d\" font-weight=\"bold\">Realita (Plna)</text>\n", lx, ly);
    fprintf(f, "<text x=\"%d\" y=\"%d\" fill=\"blue\">- S (Zdravi)</text>\n", lx, ly + 20);
    fprintf(f, "<text x=\"%d\" y=\"%d\" fill=\"red\">- I (Nakazeni)</text>\n", lx, ly + 40);
    fprintf(f, "<text x=\"%d\" y=\"%d\" fill=\"green\">- R (Vylieceni)</text>\n", lx, ly + 60);
    fprintf(f, "<text x=\"%d\" y=\"%d\" font-weight=\"bold\">Model (Ciarkovana)</text>\n", lx, ly + 90);
    fprintf(f, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" stroke-dasharray=\"5,5\" />\n", lx, ly + 100, lx+50, ly+100);
    fprintf(f, "</svg>\n");
    fclose(f);
}