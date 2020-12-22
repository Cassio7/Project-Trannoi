# Progetto-finale-2020-Trannoi
Template progetto finale per l'esame di Programmazione Procedurale con Laboratorio a.a. 2020-2021.

Inserire

Nome:Alessio

Cognome:Cassieri

Matricola:324396


ed eventuali note sulla realizzazione del progetto, come nuove funzionalità aggiunte o modificate rispetto al testo del progetto assegnato.

-Ho cambiato la funzione usa_botola() in modo tale che un impostore può decide dove spostarsi di botola, solo se sono presenti 1 o più botole in più rispetto alla sua in base a dove si trova. Se non ci sono altre stanze di tipo botola oltre alla sua viene spostato random (questo è uguale alla consegna) e se il numero di stanze è uguale ad 1, cioè esiste solo la stanza iniziale, un impostore non si può muovere in nessun'altra stanza dato che non esistono.

-Nella funzione chiamata_emergenza() quando la probabilità di "defenestrazione" è uguale per gli impostori e gli astronauti (nella stessa stanza), estraggo casualmente 0 o 1 (0=astronauta, 1=impostore), ed in base a cosa esce defenestro automaticamente un impostore o un astronauta. Questo è fatto per evitare che quando la probabilità è uguale nessuna delle due categorie di giocatori ci rimetta. 

-Aggiunta la possibilità di tornare indietro di stanza ovviamente se esiste una stanza precedente non NULL, è NULL sono nella stanza iniziale.

-Aggiunto un minigame dentro quest_semplice, dove si deve inserire il risultato di una somma. Inserendo 0 si può lasciare il tentativo e non completare la quest. Un altro giocatore può completare la quest in quella stanza.

-Aggiunto un minigame dentro quest_comlicata, dove si deve indovinare la sequenza di 5 numeri random da 1 a 5. Inserendo 0 si può lasciare il tentativo e non completare la quest. Un altro giocatore può completare la quest in quella stanza.
