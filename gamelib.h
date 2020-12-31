
enum Stato_giocatore{astronauta,impostore,assassinato,defenestrato};
enum Nome_giocatore{rosso,blu,giallo,verde,arancione,ciano,viola,marrone,bianco,rosa};
enum Tipo_stanza{vuota,quest_semplice,quest_compicata,botola};
enum Emergenza_chiamata{noeffettuata, effettuata};
struct Giocatore {
    struct Stanza* posizione;
    enum Stato_giocatore stato;
    enum Nome_giocatore player;
    struct Giocatore* next;
};
struct Stanza{
    struct Stanza* avanti;
    struct Stanza* destra;
    struct Stanza* sinistra;
    struct Stanza* stanza_precedente;
    struct Stanza* prox;//la uso solo con lista_stanze
    enum Tipo_stanza tipo;
    enum Emergenza_chiamata emergenza;
};
 void imposta_gioco();
 void gioca();
 void termina_gioco();
 void scritta();
