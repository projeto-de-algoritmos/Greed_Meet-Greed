#include <stdio.h>
#include <stdlib.h>

typedef struct reunion{
    int duration;
    int start[2];
    int end[2];
}r;

typedef struct agenda{
    int horarios[120];
}a;

a *newAgenda(int op){
    a *newA;

    if(op == 1){
        for(int i = 0; i < 120; i++){
            newA->horarios[i] = 0;
        }
    }else{
        FILE *f = fopen("agenda.txt", "r");
        for(int i = 0; i < 120; i++){
            fscanf(f, "%d", &newA->horarios[i]);
        }
        fclose(f);
    }

    return newA;
}

void newReunion(int d, int s[], int e[]){
    r *newR = malloc(sizeof(r *));

    newR->duration = d;

    newR->start[0] = s[0];
    newR->start[1] = s[1];

    newR->end[0] = e[0];
    newR->end[0] = e[1];
}

void agendar(){

}

void remover(){

}

void show(){

}

void save(){
    
}