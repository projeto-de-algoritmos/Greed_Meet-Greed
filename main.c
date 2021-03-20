#include "lib.h"
int flag = -1;
a *agenda;

void pressione(){
    printf("pressione enter pra continuar...");
    getchar();
    getchar();
}


void menu(){
    system("clear");
    printf("Bem-Vindo ao Meet&Greed (Horario de Funcionamento: 08h as 18h)\n");
    printf("Digite o numero da operacao:\n");
    printf("1 - Agendar reuniao\n2 - Cancelar reuniao\n3 - Visualizar agenda\n4 - Salvar\n5 - Sair\n>");
    
    int op;
    scanf("%d", &op);

    switch(op){
        case 1:
            agenda = agendar(agenda);
            pressione();
            menu();
        break;
        case 2:
            agenda = remover(agenda);
            pressione();
            menu();
        break;
        case 3:
            show(agenda);
            pressione();
            menu();
        break;
        case 4:
            save(agenda);
            pressione();
            menu();
        break;
        default:
            exit(0);
        break;
    }
}


void start(){
    printf("Digite o numero da sua escolha:\n1 - Usar agenda existente\n2 - Criar nova agenda\n>");
    int op;
    scanf("%d", &op);
    while(op < 1 || op > 2){
        system("clear");
        printf("Digite o numero da sua escolha:\n1 - Usar agenda existente\n2 - Criar nova agenda\n>");
        scanf("%d", &op);
    };

    agenda = newAgenda(op);
    menu();
}

int main(){
    start();
    free(agenda);
}