#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct agenda{
    int horarios[120];
    int total;
}a;

a *newAgenda(){
    a *newA =  malloc(sizeof(a *));

    for(int i = 0; i < 120; i++){
        newA->horarios[i] = 0;
        printf("%d %d\n", i, newA->horarios[i]);
    }
    newA->total = 0;

    return newA;
}

int calcHora(int tempo){
    tempo *= 5;

    return 8+(tempo/60);
}

int calcMinuto(int tempo){
    tempo *= 5;

    return tempo%60;
}

a *agendar(a *agenda){
    int dur, quant = 0, atual = 0;
    system("clear");
    printf("//Agendar Reuniao\\\\\n");
    printf("Duracao da reuniao(em minutos): ");
    scanf("%d", &dur);

    if(dur%5 != 0){
        dur = (dur/5)+1;
        printf("%d\n", dur);
    }else{
        dur = dur/5;
    }

    for(int i = 0; i < 120; i++){
        if(agenda->horarios[i] == 0){
            int flag = 0;

            for(int j = i; j < i+dur; j++){
                if(agenda->horarios[j] != 0 && i+dur < 120){
                    flag = 1;
                }
            }

            if(flag == 0){
                printf("Reuniao Marcada!\n");
                quant++;
                for(int j = i; j < i+dur; j++){
                    agenda->horarios[j] = quant;
                }

                agenda->total++;
                break;
            }
        }else if(agenda->horarios[i] != atual){
            quant++;
            atual = agenda->horarios[i];
            agenda->horarios[i] = quant;
        }else{
            agenda->horarios[i] = quant;
        }
    }

    return agenda;
}

a *remover(a *agenda){
    system("clear");
    return agenda;
}

void show(a *agenda){
    int atual = 0, dur = 0, num = 0;

    system("clear");
    printf("//Reunioes Agendadas\\\\\n");

    for(int i = 0; i < 120; i++){
        if(atual != 0){
            if(agenda->horarios[i] != atual){
                num++;
                atual = agenda->horarios[i];
                printf("-------------\nReuniao numero: %d\nA Sala estara ocupada das %.2dh%.2d as %.2dh%.2d\n-------------\n", num, calcHora(i-dur), calcMinuto(i-dur), calcHora(i), calcMinuto(i));
                dur = 0;
            }else{
                dur++;
            }
        }else{
            if(agenda->horarios[i] != 0){
                dur++;
                atual = agenda->horarios[i];
            }
        }
    }

    if(num == 0){
        system("clear");
        printf("Agenda Vazia!\n");
    }
}