#include <stdio.h>
#include <stdlib.h>
#include "gamelib.h"
void menu(){
  int scelta=0, flag=0,flag1=0,flag2=0;
  do{
    do {
      scelta=0;
      if (flag1)//entra se flag1 è diverso da 0
        printf("\n!Errore nell'inserimento!\n" );
      printf("\nInserisci un numero da 1 a 3 per decidere una di queste opzioni:\n");
      printf("\n\t1= Imposta il gioco\n\t2= Gioca\n\t3= Termina il gioco\n");
      if (!flag2){//entra quando flag2 è 0
        do {
          printf("\vPer prima cosa è necessario impostare il gioco, inserisci 1:\nScelta: ");
          scanf("%d",&scelta);
          while(getchar()!= '\n');//pulisco il buffer
        } while(scelta!=1&&scelta!=3);//faccio fare solo l'inserimento o terminare il gioco
        flag2++;
        break;
      }
      printf("Scelta: " );
      scanf("%d",&scelta);
      while(getchar()!= '\n');//pulisco il buffer
      flag1++;
    }while(scelta<1||scelta>3);
    flag1=0;
      switch(scelta){
        case 1://apertura case 1
               imposta_gioco();
               break;//indica la fine del case
        case 2://apertura case 2
               gioca();
               system("clear");
               scritta();//rimetto la scritta
               flag2=0;//metto flag2 a 0 per ricominciare un altro game e fargli impostare il gioco per prima cosa
               //flag++;
               break;//indica la fine del case
        case 3://apertura case 3
               termina_gioco();
               printf("\vGG WP ALL\n");
               flag++;
               break;//indica la fine del case
             }
     }while(!flag);//finisce quando flag è diverso da 0
}

int main() {
  system("clear");
  scritta();
  menu();
  return 0;
}
