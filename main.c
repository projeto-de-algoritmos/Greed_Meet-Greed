#include "lib.h"
int flag = -1;
a *agenda;


void menu(){
    printf("Welcome to Meet&Greed (Horario de Funcionamento: 08h as 18h)\n");

    if(flag == -1){
        int op;
        printf("Digite o numero da sua escolha:\n0 -Usar a Agenda Existente\n1 -Criar nova Agenda");
        flag = op;
        agenda = newAgenda(op);
    }
}

int main(){
    menu();
}