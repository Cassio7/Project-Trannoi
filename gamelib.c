#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "gamelib.h"

struct Giocatore* giocatore=NULL;//creato dinamicamente
struct Giocatore* primo=NULL;
unsigned short quest_da_finire;
struct Stanza* stanza_inizio;
struct Stanza* lista_stanze;

void imposta_gioco(){
int n=0;
time_t t;
srand((unsigned) time(&t));
do {
  printf("\nInserisci il numero di giocatori, il minimo è 4 il massimo è 10: ");
  scanf("%d",&n);
} while(n<4||n>10);
//printf("caso %d\n",1+rand() % 10);
//giocatore = (struct Giocatore*) calloc(n, sizeof(struct Giocatore));
giocatore = (struct Giocatore*) malloc(sizeof(struct Giocatore));//inserimento primo giocatore
  scanf("%d",&(giocatore->cock));
  giocatore->next=NULL;
  if (primo == NULL)
    primo = giocatore;
  else{
    giocatore->next=primo;
    primo=giocatore;
  }
for(int i =0;i<n-1;i++){
struct Giocatore* new = (struct Giocatore*) malloc(sizeof(struct Giocatore));
scanf("%d",&(new->cock));
if (primo == NULL)
  primo = new;
else{
  new->next=primo;
  primo=new;
}
}
if (primo==NULL)//stampa
  printf("Nessun nodo\n");
else{
  struct Giocatore* scan=primo;
  do {
    printf("Giocatore numero :%d\n",scan->cock );
    scan= scan->next;
  } while(scan!=NULL);
}

}
void gioca(){

}
void termina_gioco(){
free(giocatore);
}
