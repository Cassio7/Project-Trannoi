#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gamelib.h"

struct Giocatore* giocatore=NULL;//creato dinamicamente
struct Giocatore* primo=NULL;
unsigned short quest_da_finire;
struct Stanza* stanza_inizio;
struct Stanza* lista_stanze;

char *colore(struct Giocatore* scan){//per far tornare il colore in base alla posizione sull'enum Nome_giocatore
  static char color[22];
  switch (scan->player) {
    case 0:
           strcpy(color, "rosso");
           break;
    case 1:
           strcpy(color, "blu");
           break;
    case 2:
         strcpy(color, "giallo");
         break;
    case 3:
         strcpy(color, "verde");
         break;
    case 4:
         strcpy(color, "arancione");
         break;
    case 5:
         strcpy(color, "nero");
         break;
    case 6:
         strcpy(color, "viola");
         break;
    case 7:
         strcpy(color, "marrone");
         break;
    case 8:
         strcpy(color, "bianco");
         break;
    case 9:
         strcpy(color, "rosa");
         break;
  }
  return color;
}
char *job(struct Giocatore* scan){
  static char jobb[22];
  switch (scan->stato) {
    case 0:
           strcpy(jobb, "astronauta");
           break;
    case 1:
           strcpy(jobb, "impostore");
           break;
    case 2:
           strcpy(jobb, "assassinato");
           break;
    case 3:
           strcpy(jobb, "defenestrato");
           break;
  }
  return jobb;
}
char *tipo(struct Giocatore* scan){
  static char tipoo[22];
  switch (scan->posizione->tipo) {
    case 0:
           strcpy(tipoo, "vuota");
           break;
    case 1:
           strcpy(tipoo, "quest semplice");
           break;
    case 2:
           strcpy(tipoo, "quest complicata");
           break;
    case 3:
           strcpy(tipoo, "botola");
           break;
  }
  return tipoo;
}
void stampa_giocatori(){
  int flag=1;//per il numero giocatore
  if (primo==NULL)//stampa
    printf("Nessun giocatore\n");
  else{
      struct Giocatore* scan=primo;
      do {
        printf("Giocatore numero %d è di colore %s ed è un %s\n",flag, colore(scan), job(scan));
        scan= scan->next;
        flag++;
      } while(scan!=NULL);
  }

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

static void avanza(struct Giocatore* scan){
  printf("joy\n");
}
static void esegui_quest(struct Giocatore* scan){
  printf("joy\n");
}
static void chiamata_emergenza(struct Giocatore* scan){
  printf("joy\n");
}
static void uccidi_astronauta(struct Giocatore* scan){
  printf("joy\n");
}
static void usa_botola(struct Giocatore* scan){
  printf("joy\n");
}
static void sabotaggio(struct Giocatore* scan){
  printf("joy\n");
}

void imposta_gioco(){//funzione principale ove inizializzo il gioco con creazione della stanza_inizio e giocatori
termina_gioco();
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
/*faccio il random delle posizioni dell'array per evitare che gli impostori siano sempre
  quelli all'inizio, dato che appena trova n impostori tutti gli altri vengono impostati a 0
  facendp lo shuffle sotto ho più probabilità che venga inserto 1 tra gli ultimi posti
*/
for (int i = 0; i < n; i++) {
  int j = rand()%(i+1);
  int temp= rondo[i];
  rondo[i]=rondo[j];
  rondo[j]=temp;
}
/*for (int i = 0; i < n; i++) {
  printf("secondo Controllo se astronauta o impostore :%d\n",rondo[i] );
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
    new->stato=rondo[i+1];//metto dentro stato la posizione di i+1 dato che i=0 è già inserito
    new->player=rondo1[i+1];//metto dentro player(colore) la posizione di i+1 dato che i=0 è già inserito
  new->posizione=stanza_inizio;//puntatore alla stanza_inizio uguale per tutti i giocatori
  if (primo == NULL)
    primo = new;
  else{
    new->next=primo;
    primo=new;
  }
}
printf("Inserisci il numero di quest da fare per vincere la partita\n");
scanf("%hu",&quest_da_finire);//h sta per half (metà di una int e short) e u per unsigned
scelta=0;
do {
  printf("Inserisci 1 per stampare tutte le informazioni relative ai giocatori\n");
  printf("Insersici 2 per iniziare la partita\nInserisci 3 per riimpostare il gioco\n");
  scanf("%d",&scelta);
} while(scelta <1||scelta>3);
switch (scelta) {
  case 1:
         stampa_giocatori();
         break;
  case 2:
         gioca();
         break;
  case 3:
         termina_gioco();
         imposta_gioco();
         break;
}
}

void gioca(){//funzione principale per eseguire i comandi di gioco
  int scelta=0,flag=1,flag1=1;//scelta per menu,flag per il numero del giocatore,flag1 per i giocatori dentro la stanz
  if (primo==NULL)
    printf("Nessun giocatore inserito ao\n");
  else{
      struct Giocatore* scan=primo;//per ciclare tutti i player e fargli scegliere cosa fare nel loro turno
      do {
        printf("\nTurno del giocatore numero %d, di colore %s ed è un %s\n",flag, colore(scan), job(scan));
        printf("La tua stanza è di tipo: %s e è/sono presente/i :\n\n",tipo(scan));
        struct Giocatore* temp=primo;//utilizzata per stampare i giocatori presenti nella stanza
        flag1=1;
        do {
          if (scan->posizione==temp->posizione) {//contrll tra il gioca di questo turno e i presenti nella stessa stanz
            if (flag!=flag1){//controllo per non stampare se stesso tra i presenti in stanza ma solo gli altri giocatori
              printf("Il Giocatore di colore %s \n",colore(temp));
              scelta++;
            }
          }
          temp=temp->next;//vado al next giocatore
          flag1++;
        } while(temp!=NULL);
        if (!scelta)//entra solo se scelta è 0
            printf("Non ci sono giocatori nella tua stanza\n");
        scelta=0;
        if (!scan->stato) {//entra quando è 0
          do {//menu per gl'astronauti
            printf("\nInserisci 1 per spostarti di stanza\n");
            printf("Insersici 2 per eseguire una quest\nInserisci 3 per la chiamata di emergenza\n");
            printf("Scelta: ");
            scanf("%d",&scelta);
          } while(scelta <1||scelta>3);
          switch (scelta) {
            case 1:
                   avanza(scan);//passo il puntatore al giocatore
                   break;
            case 2:
                   esegui_quest(scan);//passo il puntatore al giocatore
                   break;
            case 3:
                   chiamata_emergenza(scan);//passo il puntatore al giocatore
                   break;
          }
        }
        else{
          if (scan->stato==1) {
            do {//menu per gl'impostori
              printf("\nInserisci 1 per spostarti di stanza\nInserisci 2 per la chiamata di emergenza\n");
              printf("Inserisci 3 per uccidere\nInserisci 4 per usare la botola\nInserisci 5 per sabotare\n");
              printf("Scelta: ");
              scanf("%d",&scelta);
            } while(scelta <1||scelta>5);
            switch (scelta) {
              case 1:
                     avanza(scan);
                     break;
              case 2:
                     chiamata_emergenza(scan);//passo il puntatore al giocatore
                     break;
              case 3:
                     uccidi_astronauta(scan);//passo il puntatore al giocatore
                     break;
              case 4:
                     usa_botola(scan);//passo il puntatore al giocatore
                     break;
              case 5:
                     sabotaggio(scan);//passo il puntatore al giocatore
                     break;
            }
          }
        }
        scan= scan->next;
        flag++;
      } while(scan!=NULL);
  }
}

void termina_gioco(){
  if (primo!=NULL){
    free(stanza_inizio);
    do {
      struct Giocatore* temp=primo->next;
      free(primo);
      primo=temp;
    } while(primo!=NULL);
  }
}
