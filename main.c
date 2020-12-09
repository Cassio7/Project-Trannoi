#include <stdio.h>
#include <stdlib.h>
#include "gamelib.h"

int main() {
  int scelta=0, flag=0,flag1=0;
  printf("Benvenuti in Trannoi!\nPer prima cosa è necessario impostare il gioco:\n");
  imposta_gioco();
//  do{
    do {
      if (flag1)
      printf("\n!!Errore nell'inserimento della scelta!!\n" );
      printf("\nInserisci un numero da 1 a 3 per decidere una di queste opzioni:\n");
      printf("\n1= Imposta il gioco\n2= Gioca\n3= Termina il gioco\nScelta: ");
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
     //}while(!flag);
  return 0;
}
