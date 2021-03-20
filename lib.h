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

a *newAgenda(){
    a *newA;

    for(int i = 0; i < 120; i++){
        newA.horarios[i] = 0;
    }

    return newA;
}

void newReunion(int d, int s[], int e[]){
    r *newR = malloc(sizeof(r *));

    newR.duration = d;

    newR.start[0] = s[0];
    newR.start[1] = s[1];

    newR.end[0] = e[0];
    newR.end[0] = e[1];
}