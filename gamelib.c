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
void stanza_iniziale(int rando){//inizializzazione della stanza iniziale
  stanza_inizio =(struct Stanza*) malloc(sizeof(struct Stanza));//inizializzazione stanza prinicipale
  stanza_inizio->avanti=NULL;
  stanza_inizio->sinistra=NULL;
  stanza_inizio->destra=NULL;
  stanza_inizio->stanza_precedente=NULL;
  if (rando>=1&&rando<=30)//da 1 a 30 stanza tipo vuoto
    stanza_inizio->tipo=0;
  else{
    if (rando>30&&rando<=60)//da 30 a 60 stanza tipo quest_semplice
      stanza_inizio->tipo=1;
    else{
      if (rando>60&&rando<=75)//da 60 a 75 stanza tipo quest_compicata
        stanza_inizio->tipo=2;
      else
        stanza_inizio->tipo=3;//da 75 in poi stanza tipo botola
    }
  }
}
void nuova_stanza(int rando){//inizializzazione di una nuova stanza
  struct Stanza *nuova =(struct Stanza*) malloc(sizeof(struct Stanza));//inizializzazione stanza prinicipale
  nuova->avanti=NULL;
  nuova->sinistra=NULL;
  nuova->destra=NULL;
  nuova->stanza_precedente=NULL;
  if (rando>=1&&rando<=30)//da 1 a 30 stanza tipo vuoto
    nuova->tipo=0;
  else{
    if (rando>30&&rando<=60)//da 30 a 60 stanza tipo quest_semplice
      nuova->tipo=1;
    else{
      if (rando>60&&rando<=75)//da 60 a 75 stanza tipo quest_compicata
        nuova->tipo=2;
      else
        nuova->tipo=3;//da 75 in poi stanza tipo botola
    }
  }
}

void imposta_gioco(){//funzione principale ove inizializzo il gioco con creazione della stanza_inizio e giocatori
int n=0,scelta=0,rando=0;//n=numero di persone, scelta la uso come flag e per la scelta dell'utente, rando=random
time_t t;//per il random
srand((unsigned) time(&t));//per il random
do {
  printf("\nInserisci il numero di giocatori, il minimo è 4 il massimo è 10: ");
  scanf("%d",&n);
} while(n<4||n>10);//numero tra 4 e 10
int rondo[n], rondo1[n]; //array per inserimento e controllo di numeri per metterli dentro delle enum
rando=1+rand()%101;//da 1 a 100
stanza_iniziale(rando);//chiamo una funzione e passo un numero random
if (n>=4&&n<=6) { // 1 impostore
  for (int i = 0; i < n; i++) {
    rondo[i]=rand()%2;
    if (rondo[i]==1) {
      if (scelta>=1)//se abbiamo già 1 impostore tutti i next diventano astronauti
        rondo[i]=0;
      scelta++;
    }
  }
}
else{
  if (n>=7&&n<=9) { // 2 impostori
    for (int i = 0; i < n; i++) {
      rondo[i]=rand()%2;
      if (rondo[i]==1) {
        if (scelta>=2) //se abbiamo già 2 impostori tutti i next diventano astronauti
          rondo[i]=0;
        scelta++;
      }
    }
  }
  else{ //3 impostori
    for (int i = 0; i < n; i++) {
      rondo[i]=rand()%2;
      if (rondo[i]==1) {
        if (scelta>=3) //se abbiamo già 3 impostori tutti i next diventano astronauti
          rondo[i]=0;
        scelta++;
      }
    }
  }
}
/*for (int i = 0; i < n; i++) {
  printf("Controllo se astronauta o impostore :%d\n",rondo[i] );
}*/
  for (int i = 0; i < n; i++) { // numeri random senza ripetizione per stabilire il Nome_giocatore
    rondo1[i]= rand()%10;
    for (int c = 0; c < i; c++) {
      if (rondo1[c]==rondo1[i]) {
        i--;
        break;
      }
    }
  }
  /*for (int i = 0; i < n; i++) {
    printf("Colore in base al numero: %d\n",rondo1[i] );
  }*/
  giocatore = (struct Giocatore*) malloc(sizeof(struct Giocatore));//creazione in mem dinamica primo giocatore
  giocatore->stato=rondo[0];//metto il primo stato dentro il primo giocatore
  giocatore->player=rondo1[0];//metto il primo player (colore) dentro il primo giocatore
  giocatore->next=NULL;
  giocatore->posizione=stanza_inizio;//puntatore alla stanza_inizio uguale per tutti i giocatori
  if (primo == NULL)//in questo caso primo e NULL quindi entra e ci mette il primo giocatore
    primo = giocatore;
  else{
    giocatore->next=primo;
    primo=giocatore;
  }
for(int i =0;i<n-1;i++){//n-1 perchè giocatore l'ho già inserito
  struct Giocatore* new = (struct Giocatore*) malloc(sizeof(struct Giocatore));//creazione in mem dinamica dei giocat
  for (int c = 1; c < n; c++) {//inserimeto dei giocatori in base ad n; parte da 1 perchè 0 (primo)già inserito
    new->stato=rondo[i];//metto lo stato a posizione n nel new giocatore
    new->player=rondo1[i];//metto dentro player (colore) a posizione n nel new giocatore
  }
  new->posizione=stanza_inizio;//puntatore alla stanza_inizio uguale per tutti i giocatori
  if (primo == NULL)
    primo = new;
  else{
    new->next=primo;
    primo=new;
  }
}
printf("Inserisci il numero di quest da fare per vincere la partita\n");
scanf("%hu",&quest_da_finire);
scelta=0;
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
