#include "lib.h"
int flag = -1;
a *agenda;

void pressione(){
    printf("pressione enter tecla pra continuar...\n");
    getchar();
    getchar();
}


void menu(){
    system("clear");
    printf("Bem-Vindo ao Meet&Greed (Horario de Funcionamento: 08h as 18h)\n");
    printf("Digite o numero da operacao:\n");
    printf("0 - Agendar reuniao\n1 - Cancelar reuniao\n2 - Visualizar agenda\n3 - Sair\n");
    
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
            exit(0);
        break;
    }
}


void start(){
    agenda = newAgenda();
    menu();
}

int main(){
    start();
    free(agenda);
}