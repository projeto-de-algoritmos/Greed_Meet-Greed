#include "lib.h"
int flag = -1;
a *agenda;


void menu(){
    printf("Digite o numero da operacao:\n");
    printf("0 - Agendar reuniao\n
            1 - Remover reuniao\n
            2 - Visualizar agenda\n
            3 - Salvar alteracoes\n");
    
    int op;
    scanf("%d", &op);

    swicth(op){
        case 0:
            agendar();
        break;
        case 1:
            remover();
        break;
        case 2:
            show();
        break;
        case 3:
            save();
        break;
    }
}


void mainMenu(){
    printf("Welcome to Meet&Greed (Horario de Funcionamento: 08h as 18h)\n");

    if(flag == -1){
        int op;
        printf("Digite o numero da operacao:\n0 -Usar a Agenda Existente\n1 -Criar nova Agenda");
        flag = op;
        agenda = newAgenda(op);
    }else{
        menu();
    }
}

int main(){
    mainMenu();
}