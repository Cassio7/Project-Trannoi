#include <stdio.h>
#include <stdlib.h>
#include "gamelib.h"
void menu(){
  int scelta=0, flag=0,flag1=0,flag2=0;
  printf("Benvenuti in Trannoi!\n");
  do{
    do {
      if (flag1)//entra se flag1 è diverso da 0
        printf("\n!!Errore nell'inserimento della scelta!!\n" );
      printf("\nInserisci un numero da 1 a 3 per decidere una di queste opzioni:\n");
      printf("\n1= Imposta il gioco\n2= Gioca\n3= Termina il gioco\n");
      if (!flag2){
        do {
          printf("Per prima cosa è necessario impostare il gioco, inserisci 1:\n");
          printf("Scelta: " );
          scanf("%d",&scelta);
        } while(scelta!=1);
        flag2++;
        break;
      }
      printf("Scelta: " );
      scanf("%d",&scelta);
      flag1++;
    }while(scelta<1||scelta>3);
    flag1=0;
      switch(scelta){
        case 1://apertura case 1
               imposta_gioco();
               break;//indica la fine del case
        case 2://apertura case 2
               gioca();
               break;//indica la fine del case
        case 3://apertura case 3
               termina_gioco();
               printf("GG WP ALL\n");
               flag++;
               break;//indica la fine del case
             }
     }while(!flag);
}

int main() {
  menu();
  return 0;
}
