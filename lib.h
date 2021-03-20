#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct agenda{
    int horarios[120];
    int total;
}a;

a *newAgenda(int op){
    a *newA =  malloc(sizeof(a));

    if(op == 1){
        FILE *fp = fopen("agenda.txt", "r");
        for(int i = 0; i < 120; i++){  
            fscanf(fp, "%d", &newA->horarios[i]);
        }

        fscanf(fp, "%d", &newA->total);
        fclose(fp);
    }else{
        for(int i = 0; i < 120; i++){
            newA->horarios[i] = 0;
        }
        newA->total = 0;
    }

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
    int dur, quant = 0;
    system("clear");
    printf("//Agendar Reuniao\\\\\n");
    printf("Duracao da reuniao(em minutos): ");
    scanf("%d", &dur);

    //Transformar valor da duracao
    if(dur%5 != 0){
        dur = (dur/5)+1;
    }else{
        dur = dur/5;
    }

    //Vetor para o tamanho de cada reuniao
    int *reunioes;
    reunioes = malloc(agenda->total*sizeof(int));

    //Numero da reuniao Atual e duracao dela
    int atual = 0, atualDur = 0;

    //Variaveis pra ver se eh possivel encaixar direto
    int cabe = -1, vazio = 0, pos;

    //Percorro tudo
    for(int i = 0; i < 120; i++){
        if(agenda->horarios[i] != 0){//Ver se tem reuniao
            if(agenda->horarios[i] != atual){//Ver se eh outra reuniao
                quant++;
                if(atual > 0){
                    reunioes[atual-1] = atualDur;
                }
                atualDur = 1;
                atual = agenda->horarios[i];
                vazio = 0;
            }
        }else{
            if(vazio == 0){
                vazio = 1;
                atualDur = 1;
            }else if(cabe == -1){
                atualDur++;
                if(atualDur >= dur){
                    cabe = i+1;
                    pos = quant++;
                }
            }
        }
    }  

    if(cabe == -1){

    }else{
        for(int j = cabe-dur; j <= cabe; j++){
            agenda->horarios[j] = quant;
        }
    }

    if(cabe == -1){
        printf("Reuniao nao pode ser agendada!\n");
    }else{
        printf("Reuniao agendada!\nNumero da reuniao: %d\nHorario de Inicio:%.2dh%.2d\n", quant, calcHora(cabe-dur), calcMinuto(cabe-dur));
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
    printf("||Reunioes Agendadas||\n");

    for(int i = 0; i < 120; i++){
        if(agenda->horarios[i] != atual){
            if(atual != 0){
                printf("Reuniao Numero %d:\nA Sala Ficara Ocupada das %.2dh%.2d as %.2dh%.2d\n", num, calcHora(i-dur), calcMinuto(i-dur), calcHora(i-1), calcMinuto(i-1));
            }

            if(agenda->horarios[i] != 0){
                num++;
            }
            dur = 1;
            atual = agenda->horarios[i];
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
    FILE *fp = fopen("agenda.txt", "w");
        for(int i = 0; i < 120; i++){  
            fprintf(fp, "%d ", agenda->horarios[i]);
        }

        fprintf(fp, "%d", agenda->total);
    fclose(fp);
}