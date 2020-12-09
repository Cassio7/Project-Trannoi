#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum Stato_giocatore{astronauta,impostore,assassinato,defenestrato};
enum Nome_giocatore{rosso,blu,giallo,verde,arancione,nero,viola,marrone,bianco,rosa};
enum Tipo_stanza{vuota,quest_semplice,quest_compicata,botola};
struct Giocatore {
    struct Stanza* posizione;
    enum Stato_giocatore stato;
    enum Nome_giocatore player;
    int cock;
    struct Giocatore* next;
};
struct Stanza{
    struct Stanza* avanti;
    struct Stanza* destra;
    struct Stanza* sinistra;
    struct Stanza* stanza_precedente;
    enum Tipo_stanza tipo;
    bool emergenza_chiamata;
};
extern void imposta_gioco();
extern void gioca();
extern void termina_gioco();
