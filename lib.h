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
    int *reunioes, *rStart;
    reunioes = malloc(agenda->total*sizeof(int));
    rStart = malloc(agenda->total*sizeof(int));

    //Numero da reuniao Atual e duracao dela
    int atual = 0, atualDur = 0;

    //Variaveis pra ver se eh possivel encaixar direto
    int cabe = 0, vazio = 0, pos = -1, totalVazio = 0, newN = -1;

    //Percorro tudo
    for(int i = 0; i < 120; i++){
        if(agenda->horarios[i] != 0){//Ver se tem reuniao
            if(agenda->horarios[i] != atual){//Ver se eh outra reuniao
                rStart[agenda->horarios[i]-1] = i;
                quant++;//Aumentar a contagem de reunioes
                atualDur = 1;
                atual = agenda->horarios[i];
                agenda->horarios[i] = quant;
                vazio = 0;
            }else{
                atualDur++;
                agenda->horarios[i] = quant;

                reunioes[atual-1] = atualDur;
            }
        }else{
            totalVazio++;
            if(totalVazio >= dur){
                cabe = 1;
            }

            if(vazio == 0){
                vazio = 1;
                atualDur = 1;
            }else{
                atualDur++;

                if(atualDur >= dur && pos == -1){
                    pos = i-dur+1;
                    quant++;
                    newN = quant;
                }
            }
        }
    }  

    if(cabe == 0){ 
        int menor = dur, posMenor = -1;
        for(int i = 0; i < agenda->total; i++){
            if(reunioes[i]+totalVazio >= dur && reunioes[i] < dur){
                if(menor > reunioes[i]){
                    menor = reunioes[i]+totalVazio;
                    posMenor = i+1;
                }
                cabe = 1;
            }
        }
        
        if(cabe == 1){
            //Remover a reuniao nescessaria e reorganizar
            int flag = -1;
            for(int j = 0; j < 120; j++){
                if(j >= rStart[posMenor-1] && j < 120-menor){
                    if(agenda->horarios[j+menor] == 0){
                        agenda->horarios[j] = agenda->horarios[j+menor];
                    }else{
                        agenda->horarios[j] = agenda->horarios[j+menor]-1;
                    }
                }else if(j >= 120-menor){
                    if(flag == -1){
                        flag = j;
                    }
                    agenda->horarios[j] = agenda->total;
                }
            }
            newN = agenda->total;
            pos = flag;
            agenda->total--;
        }
    }else{
        for(int j = pos; j < pos+dur; j++){
            agenda->horarios[j] = newN;
        }
    }
    if(cabe == 0){
        printf("Reuniao nao pode ser agendada!\n");
    }else{
        printf("-------------\n\nReuniao agendada!\nNumero da reuniao: %d\nHorario de Inicio:%.2dh%.2d\n-------------\n\n", newN, calcHora(pos), calcMinuto(pos));
        agenda->total++;
        printf("Algumas reunioes podem ter sido renumeradas!\n");
    }

    return agenda;
}

a *remover(a *agenda){
    int re, flag = 0, i = 0, size = 1, start;

    system("clear");
    printf("Digite o numero da reuniao que deseja remover: ");
    scanf("%d", &re);

    while(flag != 2 && i < 120){
        if(agenda->horarios[i] == re && flag == 0){
            flag = 1;
            start = i;
        }else if(agenda->horarios[i] == re && flag == 1){
            size++;
        }else if(agenda->horarios[i] != re && flag == 1){
            flag = 2;
        }
        i++;
    };

    if(flag == 0){
        printf("Reuniao nao encontrada!\n");
        return agenda;
    }else{
        printf("Deseja adiantar as reunioes possiveis?\n1 - Sim\n2 - Nao\n>");
        int op;
        scanf("%d", &op);

        if(op == 1){//Adiantar as reunioes
            for(int j = 0; j < 120; j++){
                if(j >= start && j < 120-size){
                    if(agenda->horarios[j+size] == 0){
                        agenda->horarios[j] = agenda->horarios[j+size];
                    }else{
                        agenda->horarios[j] = agenda->horarios[j+size]-1;
                    }
                }else if(j >= 120-size){
                    agenda->horarios[j] = 0;
                }
            }
        }else{//So deletar
            for(int j = 0; j < 120; j++){
                if(j >= start && j < start+size){
                    agenda->horarios[j] = 0;
                }else if(agenda->horarios[j] != 0){
                    agenda->horarios[j]--;
                }
            }
        }
    }
    agenda->total--;
    system("clear");
    printf("Reuniao %d cancelada!\nAlgumas reunioes foram renumeradas!\n", re);
    return agenda;
}

void show(a *agenda){
    int atual = 0, dur = 1, num = 0;

    system("clear");
    printf("||Reunioes Agendadas||\n-------------\n\n");

    if(agenda->total == 0){
        system("clear");
        printf("Agenda Vazia!\n");
        return;
    }

    for(int i = 0; i <= 120; i++){
        if(agenda->horarios[i] != atual || i == 120){
            if(atual != 0){
                printf("Reuniao Numero %d:\nA Sala Ficara Ocupada das %.2dh%.2d as %.2dh%.2d\n-------------\n\n", num, calcHora(i-dur), calcMinuto(i-dur), calcHora(i), calcMinuto(i));
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
}

void save(a *agenda){
    FILE *fp = fopen("agenda.txt", "w");
        for(int i = 0; i < 120; i++){  
            system("clear");
            printf("Salvando");

            switch(i%3){
                case 0:
                    printf("...\n");
                break;

                case 1:
                    printf(".\n");
                break;

                case 2:
                    printf("..\n");
                break;
            }
        
            fprintf(fp, "%d ", agenda->horarios[i]);
        }

        fprintf(fp, "%d", agenda->total);
    fclose(fp);

    system("clear");
    printf("Agenda Salva!\n");
}