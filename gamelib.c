#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "gamelib.h"

struct Giocatore* primo=NULL;
unsigned short quest_da_finire;
int n;//numero dei giocatori
struct Stanza* stanza_inizio;
struct Stanza* lista_stanze;

static char *colore(struct Giocatore* scan){//per far tornare il colore in base alla posizione sull'enum Nome_giocatore
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

static char *job(struct Giocatore* scan){//per far tornare lo stato in base alla posizione sull'enum Stato_giocatore
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

static char *tipo(struct Giocatore* scan){//per far tornare il tipo stanza in base alla posizione del giocatore
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

static void stampa_giocatori(){//stampa tutti i giocatori
  int flag=1;//per il numero giocatore
  if (primo==NULL)//stampa
    printf("Nessun giocatore\n");
  else{
      struct Giocatore* scan=primo;
      printf("\nLa stanza iniziale è di tipo : %s\n",tipo(scan));
      do {
        printf("Giocatore numero %d è di colore %s ed è un %s\n",flag, colore(scan), job(scan));
        scan= scan->next;
        flag++;
      } while(scan!=NULL);
  }
}

static void stanza_iniziale(int rando){//inizializzazione della stanza iniziale
  stanza_inizio =(struct Stanza*) malloc(sizeof(struct Stanza));//inizializzazione stanza prinicipale
  stanza_inizio->avanti=NULL;
  stanza_inizio->sinistra=NULL;
  stanza_inizio->destra=NULL;
  stanza_inizio->prox=NULL;
  stanza_inizio->emergenza=0;//metto la chiamata a non effettuata
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
  lista_stanze=stanza_inizio;
}

static void nuova_stanza(struct Giocatore* scan,int scelta){//inizializzazione di una nuova stanza
  printf("\nNuova stanza creata\n");
  int rando=1+rand()%100;//da 1 a 100
  struct Stanza *nuova =(struct Stanza*) malloc(sizeof(struct Stanza));//inizializzazione stanza prinicipale
  nuova->avanti=NULL;
  nuova->sinistra=NULL;
  nuova->destra=NULL;
  nuova->prox=NULL;
  nuova->emergenza=0;//metto la chiamata a non effettuata
  nuova->stanza_precedente=scan->posizione;
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
  if (scelta==1) {//è stato scelto avanti
    do{
    if (lista_stanze->prox==NULL){//va all'ultima posizione dove posso mettere la nuova stanza per farle in fila
      lista_stanze->prox=nuova;//metto la nuova stanza in fila
      scan->posizione->avanti=nuova;//metto dentro la posizione attuale la nuova stanza creata per il percorso
      scan->posizione=nuova;//aggiorno la posizione
      lista_stanze=NULL;//esco dal ciclo
    }
    else{
      lista_stanze=lista_stanze->prox;//vado alla prossima stanza finche la prox non è NULL
    }
  }while (lista_stanze!=NULL);
  }
  else{
    if (scelta==2) {//è stato scelto destra
      do{
      if (lista_stanze->prox==NULL){
        lista_stanze->prox=nuova;
        scan->posizione->destra=nuova;
        scan->posizione=nuova;
        lista_stanze=NULL;
      }
      else{
        lista_stanze=lista_stanze->prox;
      }
    }while (lista_stanze!=NULL);
    }
    else{
      if (scelta==3) {//è stato scelto sinistra
        do{
        if (lista_stanze->prox==NULL){
          lista_stanze->prox=nuova;
          scan->posizione->sinistra=nuova;
          scan->posizione=nuova;
          lista_stanze=NULL;
        }
        else{
          lista_stanze=lista_stanze->prox;
        }
      }while (lista_stanze!=NULL);
      }
    }
  }
}

static void avanza(struct Giocatore* scan){//funzione che permette il movimento al giocatore
  int scelta=0;
  do {//menu per scegliere se andare avanti, destra, sinistra o rimanere fermo
    printf("\v\tInserisci 1 per spostarti nella stanza avanti\n\tInserisci 2 per spostarti nella stanza a destra\n");
    printf("\tInserisci 3 per spostarti nella stanza a sinistra\n\tInserisci 4 per rimanere in questa stanza\n");
    printf("\tInserisci 5 per tornare indietro\n\tScelta: ");
    scanf("%d",&scelta);
  } while(scelta <1||scelta>5);
  switch (scelta) {
    case 1://permette di muoversi in avanti
             if (scan->posizione->avanti==NULL)//vede se esiste la stanza avanti, se è null non esiste
               nuova_stanza(scan,scelta);//crea la nuova stanza e passo il giocatore e la scelta
             else//se la stanza avanti esiste, è presente in memoria basta inserirla in scan->posizione
               scan->posizione=scan->posizione->avanti;//inserisce la stanza
           break;
    case 2://permette di muoversi a destra
             if (scan->posizione->destra==NULL)
               nuova_stanza(scan,scelta);
             else
               scan->posizione=scan->posizione->destra;
           break;
    case 3://permette di muoversi a sinistra
             if (scan->posizione->sinistra==NULL)
               nuova_stanza(scan,scelta);
             else
               scan->posizione=scan->posizione->sinistra;
           break;
    case 4:
           printf("\vRimani fermo\n");
           break;
    case 5://per tornare alla stanza precedente, se è NULL significa che siamo nella stanza iniziale
            if (scan->posizione->stanza_precedente==NULL)
              printf("\vNon esiste una stanza precedente a quella iniziale\n");
            else
              scan->posizione=scan->posizione->stanza_precedente;
}
lista_stanze=stanza_inizio;
}

static void esegui_quest(struct Giocatore* scan){
  if (scan->posizione->tipo==1){//controllo se è quest_semplice
    int complete=0;
    printf("\vIndovina la sequenza di 5 numeri per eseguire la quest semplice\n");
    time_t t;//per il random
    srand((unsigned) time(&t));//per il random
    int seq[5];
    for (int i = 0; i < 5; i++) { // numeri random senza ripetizione per stabilire il mini-game
      seq[i]= 1+rand()%5;
      for (int c = 0; c < i; c++) {
        if (seq[c]==seq[i]) {
          i--;
          c=i;
        }
      }
    }
    /*for (int i=0;i<5;i++) {//vedere la sequenza
      printf("%d ",seq[i]);
    }*/
    int sceltaa=0;
    while(complete!=5){//esce quando è 5
     printf("\nHai la possibilità di uscire dal tentativo inserendo 0, però causa il non completamento della quest\n");
      for (int i=0;i<5;i++) {
        printf("\tInserisci il %d° numero\n\tScelta: ",i+1);
        scanf("%d",&sceltaa);
        if (sceltaa==0){
          complete=5;
          i=5;
        }
        else{
          if (sceltaa==seq[i]){//controllo se il numero inserito è uguale a quello della sequenza
            printf("\v\tNumero indovinato!\n\t");
            complete++;//aumento perchè numero indovinato
            for (int c=0;c<=i;c++) {//stampo i numeri indovinati fino ad ora
              printf("%d-",seq[c]);
            }
          printf("\n");
          }
          else{//se numero inserito errato torno indietro al ciclo precedente
            printf("\v\tNumero errato, riprova\n");
            i--;
          }
        }
      }
    }
    if (sceltaa==0)
      printf("\nNon hai completato la quest semplice!\n");
    else{
      quest_da_finire--;//scalo di 1
      scan->posizione->tipo=0;//la metto a vuota
      printf("\nÈ stata eseguita una quest_semplice\n");
    }
  }
  else{
    if (scan->posizione->tipo==2){//controllo se è quest_compicata
      quest_da_finire-=2;//scalo di 2
      scan->posizione->tipo=0;//la metto a vuota
      printf("\nÈ stata eseguita una quest_compicata\n");
    }
    else
      printf("\nLa stanza in cui ti trovi è di tipo: %s e non esiste una quest\n",tipo(scan));
  }
}

static void chiamata_emergenza(struct Giocatore* scan){
  struct Giocatore* temp=primo;//per scorrere i giocatori
  struct Giocatore* morto[n];//per salvare le posizione dei morti
  struct Giocatore* astro[n];//per salvare la posizione deigli astronauti
  struct Giocatore* impo[n];//per salvare la posizione degli impostori
  int flag=0,flag1=0,flag2=0;//flag=numero morti,flag1=numero astronauti,flag2=numero impostori;nella stessa stanza
  if(scan->posizione->emergenza==0){//controllo se è già stata effettuata una chiamata emergenza in questa stanza
    printf("Turno del giocatore %s\n",colore(scan));
  do {
    if (scan->posizione==temp->posizione){//controllo se sono nella stessa staza
      if (temp->stato==2){//controllo per i morti
        morto[flag]=temp;//salvo i morti nella stessa stanza
        flag++;
      }
      if (temp->stato==0){//controllo per gli astronauti
        astro[flag1]=temp;//salvo gli astronauti in questa stanza
        flag1++;
      }
      if (temp->stato==1){//controllo per gli impostori
        impo[flag2]=temp;//salvo gli impostori in questa stanza
        flag2++;
      }
    }
    temp=temp->next;
  }while(temp!=NULL);
  temp=primo;
  if (flag!=0) {
    printf("In questa stanza è/sono presente/i %d cadavere/i\n\n",flag);
    for (int i=0;i<flag; i++) {
      printf("L'astronauta di colore %s\n",colore(morto[i]));
    }
    int prob=0,prob1=0;//prob=probabilità per gli astronauti, prob1=probabilità per gli impostori
    if (flag1!=0){//se ci sta almeno 1 astronauta
      prob+=30;//aumento la prob del 30% dato che almeno 1 ci sta
      for(int i=0;i<flag2;i++) {//ciclo per aggiungere il 20% per ogni impostore nella stanza
        prob+=20;
      }
      for(int i=0;i<flag1-1;i++) {//ciclo per togliere il 30% per ogni astronauta nella stanza lui escluso
        prob-=30;
      }
    }
    printf("probabilità per gli astronauti %d\n",prob);
    if (flag2!=0){//se ci sta almeno 1 impostore
      prob1+=30;//aumento la prob del 30% dato che almeno 1 ci sta
      for(int i=0;i<flag1;i++) {////ciclo per aggiungere il 20% per ogni astronauta nella stanza
        prob1+=20;
      }
      for(int i=0;i<flag2-1;i++) {//ciclo per togliere il 30% per ogni impostore nella stanza lui escluso
        prob1-=30;
      }
    }
    printf("probabilità per gli impostori %d\n",prob1);
    time_t t;//per il random
    srand((unsigned) time(&t));//per il random
    int a=0;
    if (prob>prob1) {//se la prob degli astronauti è maggiore di quella degli impostori esce un astronauta a caso
      a=rand()%flag1;//numero random tra 0 e il numero degli astronauti nella stanza
      for (int i=0;i<flag1;i++) {
        if (a==i) {
          astro[i]->stato=3;
          printf("\nÈ stato defenestrato randomicamente l'astronauta di colore %s\n",colore(astro[i]));
          i=flag1;
        }
      }
    }
    else{
      if (prob1>prob){//se la prob degli impostori è maggiore di quella degli astronauti esce un impostore a caso
        a=rand()%flag2;//numero random tra 0 e il numero degli imposori nella stanza
        for (int i=0;i<flag2;i++) {
          if (a==i) {
            impo[i]->stato=3;
            printf("\nÈ stato defenestrato randomicamente l'impostore di colore %s\n",colore(impo[i]));
            i=flag2;
          }
        }
      }
      else{//se la probabilità è uguale esce un astronauta o un impostore a caso
        printf("Il numero degli impostori e astronauti nella stanza è uguale, quindi ne esce uno a caso tra i due\n");
        a=rand()%2;
        if (a==0) {//se è 0 esce un astronauta
          a=rand()%flag1;//numero random tra 0 e il numero degli astronauti nella stanza
          for (int i=0;i<flag1;i++) {
            if (a==i) {
              astro[i]->stato=3;
              printf("\nÈ stato defenestrato randomicamente l'astronauta di colore %s\n",colore(astro[i]));
              i=flag1;
            }
          }
        }
        else{//esce un impostore
          a=rand()%flag2;//numero random tra 0 e il numero degli imposori nella stanza
          for (int i=0;i<flag2;i++) {
            if (a==i) {
              impo[i]->stato=3;
              printf("\nÈ stato defenestrato randomicamente l'impostore di colore %s\n",colore(impo[i]));
              i=flag2;
            }
          }
        }
      }
    }
    scan->posizione->emergenza=1;
  }
  else
    printf("\nIn questa stanza non è presente nessun cadavere\n");
  }
  else
    printf("\nGià è stata chiamata l'emergenza per questa stanza!\n");
}

static void uccidi_astronauta(struct Giocatore* scan){
  int sceltaa=0,flag=1;
  struct Giocatore* temp=primo;
  struct Giocatore* astro[n];
  printf("\nHai selezionatio uccidi astronauta. Nella stessa tua stanza è/sono presente/i\n\n");
  do {
    if (scan->posizione==temp->posizione&&temp->stato==0) {
      printf("Astronauta numero %d ed è di colore %s\n",flag,colore(temp));
      astro[flag]=temp;
      flag++;
    }
    temp=temp->next;
  } while(temp!=NULL);
  temp=primo;
  if (flag==1)
    printf("\nNon ci sono astronauti da uccidere in questa stanza\n");
  else{
    do{
    printf("\nInserisci il numero dell'astronauta per ucciderlo\nScelta: ");
    scanf("%d",&sceltaa);
  }while(sceltaa<1||sceltaa>=flag);
    for (int i=0; i<flag; i++) {
      if (sceltaa==i) {
        printf("\nHai ucciso l'astronauta %s\n",colore(astro[i]));
        astro[i]->stato=2;
        i=flag;
      }
    }
    int prob=0;
    //prob del 50% per ogni altro astronauta nella stessa stanza, faccio flag-1 perchè è il totale - quello morto
    for (int i=1; i<flag-1; i++) {
      prob+=50;//aumento del 50% la probabilità
    }
    if (scan->posizione->stanza_precedente!=NULL) {//controlo se esiste una stanza precedente
      do{
        //controllo se esistono persone nella stanza precedente e se sono astronauti
        if(temp->posizione==scan->posizione->stanza_precedente&&temp->stato==0)
          prob+=20;//aumento del 20% la probabilità
        temp=temp->next;//passo al prox giocatore
      }while(temp!=NULL);
    }
    time_t t;//per il random
    srand((unsigned) time(&t));//per il random
    int a=rand()%101;//numero random da 0 a 100
    if (a<=prob) {//se il numero random è inferiore della probabilità l'impostore viene defenestrato
      printf("\nSei stato defenestrato!!\n");
      scan->stato=3;//metto lo stato a defenestrato
    }
  }
}

static void usa_botola(struct Giocatore* scan){//l'impostore può scegliere la botola dove andare
  int sceltaa=0,numsta=0;//usata come flag e per la scelta del player,numsta=numero stanze in totale fino ad ora
  do {
    numsta++;//conto il numero delle stanze
    lista_stanze=lista_stanze->prox;
  } while(lista_stanze!=NULL);
  lista_stanze=stanza_inizio;
  if (scan->posizione->tipo==3){//controllo se è presente una botola
    struct Stanza* botole[numsta];//usata per salvarmi la posizione delle botole
    int num=0;//serve per il numero di botole (e per il numero totale di stanze nella else)
    do {
      //se la prima stanza è di tipo botola e non è la stanza del giocatore
      if (lista_stanze->tipo==3&&lista_stanze!=scan->posizione){
        botole[num]=lista_stanze;//metto la stanza che trovo in botole
        num++;//aumento il numero di stnze
      }
      lista_stanze=lista_stanze->prox;//vado alla prossima stanza
    } while(lista_stanze!=NULL);
    lista_stanze=stanza_inizio;//rimetto la lista all'inizio
    if (num!=0) {//se le stanze sono 1 o più
      printf("\nSono disponibili %d botole dove andare\n",num);
      for (int i=0; i<num; i++) {//serve per stampare i giocatori presenti in una stanza con botola
        sceltaa=0;
        struct Giocatore* temp=primo;
        printf("\nNella stanza numero %d e è/sono presente/i\n",i);
        do {
          if (botole[i]==temp->posizione) {//controllo se in quella stanza è presente un giocatore
            printf("Il giocatore di colore : %s\n",colore(temp));
            sceltaa++;//serve per stampare nessun giocatore in stanza
          }
          temp=temp->next;//vado al prox giocatore
        }while(temp!=NULL);
        if (sceltaa==0)
          printf("Non ci sono giocatori in questa stanza\n");
      }
      sceltaa=0;
      do{
        printf("Inserisci il numero della stanza dove vuoi andare\nScelta: ");
        scanf("%d",&sceltaa);
/*la scelta deve essere tra la botola a posizione 0 ed a num non compreso. es: se esiste una sola stanza botola dove
dove andare la scelta sarà solo 0 ma il num sarà 1 e la stanza 1 non esiste*/
      }while(sceltaa<0||sceltaa>=num);
      for (int i=0; i<num; i++) {//for per controllare la scelta con la stanza corrispondente
        if (sceltaa==i) {//la scelta è uguale alla stanza
          printf("Hai scelto la stanza %d ed ora ti sposterai in quella stanza\n",i);
          scan->posizione=botole[i];//scambio posizione
          i=num;//esco dal ciclo
        }
      }
    }
    else{//se non esiste una stanza botola oltre alla sua viene mandato random su un'altra stanza
      printf("\nNon esistono altre stanze di tipo botola tranne la tua, verrai spostato casualmente in una stanza\n");
      do {
        num++;
        lista_stanze=lista_stanze->prox;
      } while(lista_stanze!=NULL);
      lista_stanze=stanza_inizio;
      if (num==1) {//ho fatto il ciclo sopra ma se viene 1 significa che esiste solo la stanza iniziale
        printf("Esiste solo la stanza iniziale, non puoi spostarti in nessun'altra stanza\n");
      }
      else{
        time_t t;//per il random
        srand((unsigned) time(&t));//per il random
        int a=rand()%num,b=0;
        do {
          if (a==b){
            if (lista_stanze->tipo!=3) {
              scan->posizione=lista_stanze;
              lista_stanze=NULL;
              printf("La tua stanza è stata cambiata casualmente\n");
            }
            else
              a=rand()%num;
          }
          else{
            lista_stanze=lista_stanze->prox;
            b++;
          }
        } while(lista_stanze!=NULL);
        lista_stanze=stanza_inizio;
      }
    }
  }
  else
    printf("\nNon è presente una botola in questa stanza perchè di tipo : %s\n",tipo(scan));
}

static void sabotaggio(struct Giocatore* scan){
  if (scan->posizione->tipo==1||scan->posizione->tipo==2){//controllo se è quest_semplice o quest_compicata
    scan->posizione->tipo=0;//la metto a vuota
    printf("\nLa stanza è stata sabotata!\n");
  }
  else
    printf("\nLa stanza in cui ti trovi è di tipo: %s e non può essere sabotata\n",tipo(scan));
  }

void imposta_gioco(){//funzione principale ove inizializzo il gioco con creazione della stanza_inizio e giocatori
termina_gioco();
int scelta=0,rando=0;//n=numero di persone, scelta la uso come flag e per la scelta dell'utente, rando=random
n=0;
time_t t;//per il random
srand((unsigned) time(&t));//per il random
do {
  printf("\nInserisci il numero di giocatori, il minimo è 4 il massimo è 10\nScelta: ");
  scanf("%d",&n);
} while(n<4||n>10);//numero tra 4 e 10
int rondo[n], rondo1[n]; //array per inserimento e controllo di numeri per metterli dentro delle enum
rando=1+rand()%101;//da 1 a 100
stanza_iniziale(rando);//chiamo una funzione e passo un numero random
if (n>=4&&n<=6) { // massimo 1 impostore
  for (int i = 0; i < n; i++) {
    rondo[i]=rand()%2;
    if (rondo[i]==1) {
      if (scelta>=1)//se abbiamo già 1 impostore tutti i next diventano astronauti
        rondo[i]=0;
      scelta++;
    }
  }
  if (scelta==0) {//minimo 1 impostore
    int i=rand()%n;
    rondo[i]=1;
  }
}
else{
  if (n>=7&&n<=9) { // massimo 2 impostori
    for (int i = 0; i < n; i++) {
      rondo[i]=rand()%2;
      if (rondo[i]==1) {
        if (scelta>=2) //se abbiamo già 2 impostori tutti i next diventano astronauti
          rondo[i]=0;
        scelta++;
      }
    }
    if (scelta==0) {//minimo 1 impostore
      int i=rand()%n;
      rondo[i]=1;
    }
  }
  else{ //massimo 3 impostori
    for (int i = 0; i < n; i++) {
      rondo[i]=rand()%2;
      if (rondo[i]==1) {
        if (scelta>=3) //se abbiamo già 3 impostori tutti i next diventano astronauti
          rondo[i]=0;
        scelta++;
      }
    }
    if (scelta==0) {//minimo 1 impostore
      int i=rand()%n;
      rondo[i]=1;
    }
  }
}
/*faccio il random delle posizioni dell'array per evitare che gli impostori siano sempre
  quelli all'inizio, dato che appena trova n impostori tutti gli altri vengono impostati a 0
  facendo lo shuffle sotto ho più probabilità che venga inserto 1 tra gli ultimi posti
*/
for (int i = 0; i < n; i++) {
  int j = rand()%(i+1);
  int temp= rondo[i];
  rondo[i]=rondo[j];
  rondo[j]=temp;
}
  for (int i = 0; i < n; i++) { // numeri random senza ripetizione per stabilire il Nome_giocatore
    rondo1[i]= rand()%10;
    for (int c = 0; c < i; c++) {
      if (rondo1[c]==rondo1[i]) {
        i--;
        break;
      }
    }
  }
  struct Giocatore* giocatore=NULL;
  giocatore = (struct Giocatore*) malloc(sizeof(struct Giocatore));//creazione in mem dinamica primo giocatore
  giocatore->stato=rondo[0];//metto il primo stato dentro il primo giocatore
  giocatore->player=rondo1[0];//metto il primo player (colore) dentro il primo giocatore
  giocatore->next=NULL;
  giocatore->posizione=stanza_inizio;//puntatore alla stanza_inizio uguale per tutti i giocatori
  if (primo == NULL)//in questo caso primo è NULL quindi entra e ci mette il primo giocatore
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
printf("\nInserisci il numero di quest da fare per vincere la partita\nScelta: ");
scanf("%hu",&quest_da_finire);//h sta per half (metà di una int e short) e u per unsigned
scelta=0;
do {
  printf("\v\tInserisci 1 per stampare tutte le informazioni relative ai giocatori\n");
  printf("\tInsersici 2 per iniziare la partita\n\tInserisci 3 per riimpostare il gioco\n\tScelta: ");
  scanf("%d",&scelta);
} while(scelta <1||scelta>3);
switch (scelta) {
  case 1:
         stampa_giocatori();
         break;
  case 2:
         break;
  case 3:
         termina_gioco();
         imposta_gioco();
         break;
}
}

void gioca(){//funzione principale per eseguire i comandi di gioco
  int scelta=0,flag=1,flag1=1;//scelta per menu,flag per il numero del giocatore,flag1 per i giocatori dentro la stanz
do{//faccio un cilo infinito perchè i round lo sono, ma quando finiscono le quest/gli impostori uccidono tutti finisce
  if (primo==NULL)
    printf("Nessun giocatore inserito ao\n");
  else{
    struct Giocatore* scan=primo;//per ciclare tutti i player e fargli scegliere cosa fare nel loro turno
      do {
        lista_stanze=stanza_inizio;//resetto la lista stanze all'inizio
        struct Giocatore* temp;//utilizzata per controlli su giocatori presenti nella stanza
        if (scan->stato!=2&&scan->stato!=3){
        printf("\nTurno del giocatore di colore %s ed è un %s\n",colore(scan), job(scan));
        printf("La tua stanza è di tipo: %s e è/sono presente/i :\n\n",tipo(scan));
        temp=primo;//la metto al primo giocatore
        flag1=1;
        scelta=0;
        do {
          //controllo per stampare i giocatori presenti nella stessa stanza, solo quelli non uccisi e non defenestrati
          if (scan->posizione==temp->posizione&&temp->stato!=3) {
            if (flag!=flag1){//controllo per non stampare se stesso tra i presenti in stanza ma solo gli altri giocatori
              if (temp->stato==2) {
                printf("Il Giocatore di colore %s (%s)\n",colore(temp),job(temp));
                scelta++;
              }
              else{
                printf("Il Giocatore di colore %s \n",colore(temp));
                scelta++;
              }
            }
          }
          temp=temp->next;//vado al next giocatore
          flag1++;
        } while(temp!=NULL);
        temp=primo;//lo rimetto al giocatore iniziale
        if (scelta==0)//entra solo se scelta è 0
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
        }
        scan= scan->next;
        flag++;
        /*faccio finire il gioco se sono finite le quest: controllo se sono 0 oppure controllo se sono
        1-2 cioè il max degli unsigned short. Possibile che mi rimanga 1 quest_da_finire ma la finisco
        in una stanza doppia.
        */
        if (quest_da_finire==0||quest_da_finire==USHRT_MAX) {
          printf("\nGli astronauti hanno vinto completando le quest!\n");
          scan=NULL;//metto NULL per uscire dallo while
          lista_stanze=NULL;//metto NULL per uscire dallo while
        }
        int numimpo=0,numastro=0;//numimpostori
        temp=primo;
        do{//controllo per vedere se ci sono impostori in partita, se non ce ne stanno = defenestrati
          if (temp->stato==1)
            numimpo++;
          if (temp->stato==0)
            numastro++;
          temp=temp->next;
        } while(temp!=NULL);
        if (numimpo==0) {
          printf("\nGli astronauti hanno vinto defenestrando tutti gli impostori in partita\n");
          scan=NULL;
          lista_stanze=NULL;
        }
        if (numastro==0) {
          printf("\nGli impostori hanno vinto uccidento tutti gli astronauti in partita\n");
          scan=NULL;
          lista_stanze=NULL;
        }
      } while(scan!=NULL);
  }
  flag=1;
  flag1=1;
}while(lista_stanze!=NULL);
termina_gioco();
}

void termina_gioco(){
  if (primo!=NULL){
    struct Giocatore* temp;
    do {
      temp=primo->next;
      free(primo);
      primo=temp;
    } while(primo!=NULL);
    do {
      lista_stanze=stanza_inizio->prox;
      free(stanza_inizio);
      stanza_inizio=lista_stanze;
    } while(stanza_inizio!=NULL);
  }
}
