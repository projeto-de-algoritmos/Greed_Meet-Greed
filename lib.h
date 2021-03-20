#include <stdio.h>
#include <stdlib.h>

typedef struct reunion{
    int duration;
    int start[2];
    int end[2];
}r;

typedef struct agenda{
    int horarios[120];
    int total;
}a;

a *newAgenda(int op){
    a *newA =  malloc(sizeof(a *));

    if(op == 1){
        for(int i = 0; i < 120; i++){
            newA->horarios[i] = 0;
        }
        newA->total = 0;
    }else{
        FILE *f = fopen("agenda.txt", "r");
            for(int i = 0; i < 120; i++){
                fscanf(f, "%d", &newA->horarios[i]);
            }
            fscanf(f, "%d", &newA->total);
        fclose(f);
    }

    return newA;
}

int calcHora(int tempo){
    tempo *= 5;

    return tempo/60;
}

int calcMinuto(int tempo){
    tempo *= 5;

    return 60 - (tempo%60);
}

void newReunion(int d, int s[], int e[]){
    r *newR = malloc(sizeof(r *));

    newR->duration = d;

    newR->start[0] = s[0];
    newR->start[1] = s[1];

    newR->end[0] = e[0];
    newR->end[0] = e[1];
}

void agendar(a *agenda){
    printf("//Agendar Reuniao\\\\\n");
}

void remover(a *agenda){

}

void show(a *agenda){
    int atual = 0, dur = 0, num = 0;

    for(int i = 0; i < 120; i++){
        if(agenda->horarios[i] != 0 && agenda->horarios[i] != atual){
            num++;
            atual = agenda->horarios[i];
            printf("-------------\nReuniao numero: %d\nHorario Inicial: %d:%d\nDuracao:%d-------------\n", atual, calcHora(i), calcMinuto(i), (dur*5));
            dur = 0;
        }else{
            dur++;
        }
    }

    if(num == 0){
        system("clear");
        printf("Agenda Vazia!\n");
    }
}

void save(a *agenda){
    //FILE *f = fopen("agenda.txt", "w");
        for(int i = 0; i < 120; i++){
            system("clear");
            printf("Salvando agenda");
            switch(i%3){
                case 1:
                    printf(".\n");
                break;

                case 2:
                    printf("..\n");
                break;

                case 0:
                    printf("...\n");
                break;
            }            
            //fprintf(f, "%d ", agenda->horarios[i]);
        }
    //fclose(f);
}