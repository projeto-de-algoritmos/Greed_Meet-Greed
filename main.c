#include "lib.h"
int flag = -1;
a *agenda;

void pressione(){
    printf("pressione qualquer tecla pra continuar...\n");
    getchar();
    getchar();
}


void menu(){
    system("clear");
    printf("Digite o numero da operacao:\n");
    printf("0 - Agendar reuniao\n1 - Remover reuniao\n2 - Visualizar agenda\n3 - Salvar alteracoes\n4 - Sair\n");
    
    int op;
    scanf("%d", &op);

    switch(op){
        case 0:
            agenda = agendar(agenda);
            pressione();
            menu();
        break;
        case 1:
            agenda = remover(agenda);
            pressione();
            menu();
        break;
        case 2:
            show(agenda);
            pressione();
            menu();
        break;
        case 3:
            save(agenda);
            pressione();
            menu();
        break;
        case 4:
            exit(0);
        break;
    }
}


void mainMenu(){
    printf("Welcome to Meet&Greed (Horario de Funcionamento: 08h as 18h)\n");

    if(flag == -1){
        int op;
        printf("Digite o numero da operacao:\n0 -Usar a Agenda Existente\n1 -Criar nova Agenda\n:");
        scanf("%d", &op);
        flag = op;
        agenda = newAgenda(op);
        menu();
    }else{
        menu();
    }
}

int main(){
    mainMenu();
}