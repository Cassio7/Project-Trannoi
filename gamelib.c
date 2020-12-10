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

void stampa_giocatori(){
  printf("poggers\n");
  /*if (primo==NULL)//stampa
    printf("Nessun giocatore\n");
  else{
      struct Giocatore* scan=primo;
      do {
        printf("Giocatore numero :%d\n",scan->cock );
        scan= scan->next;
      } while(scan!=NULL);
  }
  */
}
void stanza_iniziale(int rando){
  stanza_inizio =(struct Stanza*) malloc(sizeof(struct Stanza));//inizializzazione stanza prinicipale
  stanza_inizio->avanti=NULL;
  stanza_inizio->sinistra=NULL;
  stanza_inizio->destra=NULL;
  stanza_inizio->stanza_precedente=NULL;
  if (rando>1&&rando<=30)
    stanza_inizio->tipo=0;
  else{
    if (rando>30&&rando<=60)
      stanza_inizio->tipo=1;
    else{
      if (rando>60&&rando<=75)
        stanza_inizio->tipo=2;
      else
        stanza_inizio->tipo=3;
    }
  }
}
void nuova_stanza(int rando){
  struct Stanza *nuova =(struct Stanza*) malloc(sizeof(struct Stanza));//inizializzazione stanza prinicipale
  nuova->avanti=NULL;
  nuova->sinistra=NULL;
  nuova->destra=NULL;
  nuova->stanza_precedente=NULL;
  if (rando>1&&rando<=30)
    nuova->tipo=0;
  else{
    if (rando>30&&rando<=60)
      nuova->tipo=1;
    else{
      if (rando>60&&rando<=75)
        nuova->tipo=2;
      else
        nuova->tipo=3;
    }
  }
}
void imposta_gioco(){
int n=0,scelta=0, rando=0;
time_t t;
srand((unsigned) time(&t));
do {
  printf("\nInserisci il numero di giocatori, il minimo è 4 il massimo è 10: ");
  scanf("%d",&n);
} while(n<4||n>10);
//printf("caso %d\n",1+rand() % 10);
//giocatore = (struct Giocatore*) calloc(n, sizeof(struct Giocatore));
rando=1+rand()%100;
stanza_iniziale(rando);
giocatore = (struct Giocatore*) malloc(sizeof(struct Giocatore));//inserimento primo giocatore
  //scanf("%d",&(giocatore->cock));

  giocatore->next=NULL;
  giocatore->posizione=stanza_inizio;
  if (primo == NULL)
    primo = giocatore;
  else{
    giocatore->next=primo;
    primo=giocatore;
  }
for(int i =0;i<n-1;i++){
  struct Giocatore* new = (struct Giocatore*) malloc(sizeof(struct Giocatore));
  //scanf("%d",&(new->cock));
  new->posizione=stanza_inizio;
  if (primo == NULL)
    primo = new;
  else{
    new->next=primo;
    primo=new;
  }
}
printf("Inserisci il numero di quest da fare per vincere la partita\n");
scanf("%hu",&quest_da_finire);

do {
  printf("Inserisci 1 per stampare tutte le informazioni relative ai giocatori\n");
  printf("Insersici 2 per iniziare la partita\n");
  scanf("%d",&scelta);
} while(scelta <1||scelta>2);
switch (scelta) {
  case 1:
         stampa_giocatori();
         break;
  case 2:
         gioca();
         break;
}
}

void gioca(){
  printf("xd\n");
}
void termina_gioco(){
free(giocatore);
}
