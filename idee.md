# Generali

Il bianco muove sempre per primo.

Nella matrice (e di conseguenza nella stampa) il bianco parte dal basso.

Al giocatore umano è assegnato il colore bianco o nero a caso.

Nel log le lettere maiuscole sono utilizzate per i pezzi neri e quelle minuscole per i pezzi bianchi.

Con il comando "XX XX" il giocatore chiede di stampare la scacchiera.

Partite di due tipi:
- giocatore vs computer
- computer vs computer

# Regole

## Mosse

### Re
Si muove di una casella sola in tutte e 8 le direzioni. 

### Donna
Si muove in qualsiasi direzione di quante case vuole, finchè non incontra un altro pezzo.

### Torre
Si muove lungo le colonne e le righe di quante case vuole.

### Alfiere
Si muove in diagonale di quante case vuole.

### Cavallo
Si muove a L. È l'unico pezzo che può scavalcare gli altri.

### Pedone
Si muove in avanti di una casa. Alla prima mossa si può muovere due case. Mangia in diagonale. 

## Mosse speciali

### Promozione
Quando il pedone raggiunge l'altra parte della scacchiera può trasformarsi in un altro pezzo tra Donna, Torre, Alfiere e Cavallo (solitamente Donna).

### En passant
Se un pedone alla sua prima mossa muove di due case fermandosi accanto ad un pedone avversario, quest'ultimo può muoversi in diagonale mangiandolo.

### Arrocco
Si muove il Re di due caselle a lato e la torre lo salta, rispettando quattro condizioni:

1. deve essere la prima mossa del Re
2. deve essere la prima mossa della Torre
3. non ci deve essere alcun pezzo tra il Re e la Torre
4. il Re non può essere sotto scacco e non può attraversare una casa in cui si troverebbe sotto scacco 

# Scacco - Scaccomatto - Patta

## Scacco - Scaccomatto
Lo scacco si ha quando il Re è attaccato da un pezzo avversario. Il Re è obbligato ad eliminare la minaccia in tre modi:

1. muovendosi e togliendosi dallo scacco
2. bloccando lo scacco con un proprio pezzo
3. catturando il pezzo avversario

Se il Re non può eliminare la minaccia è scacco matto e finisce la partita.

## Patta
Sono 5 i casi in cui una partita di scacchi può finire in parità:

1. **stallo**: il giocatore che deve muovere non può effettuare alcuna mossa legale e non ha il re sotto scacco
2. accordo tra giocatori
3. non ci sono abbastanza pezzi sulla scacchiera per poter forzare lo scacco matto (es. un Re ed un Alfiere contro un Re)
4. un giocatore può dichiarare patta nel momento in cui la stessa posizione si ripresenta per la terza volta nel corso della partita (non necessariamente per 3 volte consecutive)
5. sono state giocate 50 mosse senza che uno dei due giocatori abbia spostato un pedone o catturato un pezzo. 

# Classi

## `Piece` (classe astratta)
contiene la funzione astratta:

`virtual bool isValidMove(Cell& start_cell, Cell& end_cell, Chessboard& board) = 0;`

`virtual char print_piece() = 0;`

- un metodo che restituisce tutte le celle in cui può andare un pezzo

Classi derivate di Piece:
 
    - King
    - Queen
    - Bishop
    - Knight
    - Rook
    - Pawn

## `Cell`

## `Chessboard`
Conterrà una matrice 8x8 di puntatori a `Piece`.

Contiene i controlli:
- scacco
- scacco matto
- patta

Contiene i seguenti metodi:
- `void move (Cell& start_cell, Cell& end_cell);`
- `void print_board() const;`

## `Game` (classe astratta)
Partite di due tipi:
1. giocatore vs computer
2. computer vs computer

Tale classe:
- dovrà decidere i colori di ogni giocatore.

Contiene i seguenti metodi:
- `move (Cell& start_cell, Cell& end_cell);` controlla che ci sia un pezzo e che questo pezzo sia del giocatore giusto.


Per ogni tipo di partita c'è una classe:

### 1. `PvsC`

### 2. `CvsC`

## `Computer`
Genera delle mosse già corrette.

Genera mosse random tali che:
- sulla cella iniziale c'è un pezzo del colore di tale computer
- la cella finale è raggiungibile con una mossa dal pezzo presente nella cella iniziale

Le celle saranno generate nel seguente modo:
- **cella iniziale**: in modo random tra le celle in cui è presente un pezzo del colore del computer
- **cella finale**: in modo random tra le celle in cui può arrivare il pezzo presente nella cella iniziale

## `Human`
L'umano da la mossa da tastiera, nel formato \<casella iniziale\> \<casella finale\>, ad esempio: `B1 C3`.

Bisogna contrallare che tale mossa sia corretta.

# Domande
- nelle classi dei vari pezzi (es. `King`) al posto del metodo `print_piece()`, è meglio definire l'operatore `<<`?
- questione `move`

# TO - DO
- controllare reference sui costruttori
- questione Colour (enum?) - DONE
- controlla directory progetto c++
- finire metodo `print_table` passare `ostream` e inserire indici - DONE
- leggere docs cmake
- introdurre COSTANTI?


## Alla fine
- controllare che ci sia `const` dove deve andare 
- controllare che i parametri siano passati per reference (dove deve andare)

# `isValidMove()` vs `getValidMoves()`

## `isValidMove()`
### mossa singola 
migliore 

### scacco
per ogni pezzo avversario controllo se può attaccare il Re.

Chiamo ogni volta il metodo `isValidMove()` con `start_cell` quella di un pezzo avversario e `end_cell` quella del Re.

**complessità**: `O(numero pezzi avversari)`

Viene chiamata ad ogni mossa, se la mossa mette sotto scacco il proprio Re la mossa è illegale.

### scacco matto
simulo ogni mossa che un pezzo può fare e controllo se c'è ancora lo scacco.
Se si, è scacco matto, se c'è una sola mossa che elimina lo scacco allora non è matto.

Per ogni pezzo, chiamo `isValidMove()` con `start_cell` quella del pezzo e `end_cell` ogni cella della scacchiera. Se la mossa è valida, la faccio e controllo se il re è ancora sotto scacco.

**complessità**: `O(numero pezzi avversari * 8 * 8 * numero pezzi avversari)`

### stallo
Per ogni pezzo, controllo se può fare una mossa legale.

Per ogni pezzo, chiamo `isValidMove()` con `start_cell` quella del pezzo e `end_cell` ogni cella della scacchiera. Se c'è una sola mossa valida allora non si è in stallo.

**complessità**: `O(numero pezzi * 8 * 8)`

### computer
Per trovare le celle in cui un pezzo può muoversi chiamo `isValidMove()` con `start_cell` quella del pezzo e `end_cell` ogni cella della scacchiera.

**complessità**: `O(numeri pezzi * 8 * 8)`

## `getValidMoves()`
### mossa singola 
mi faccio dare tutte le mosse che può fare il pezzo che voglio muovere.
Controllo se la cella in cui voglio muovere è in quelle in cui il pezzo può andare.
Peggiore.

### scacco
per ogni pezzo avversario controllo se può attaccare il Re.

Per ogni pezzo mi faccio dare le celle in cui può muovere e controllo se in queste c'è quella del Re.

**complessità**: `O(numero pezzi avversari * numero celle in cui il pezzo può andare)`

Viene chiamata ad ogni mossa, se la mossa mette sotto scacco il proprio Re la mossa è illegale.

### scacco matto
peggiore

**complessità**: `O(?)`

### stallo
Per ogni pezzo, controllo se può fare una mossa legale.

**complessità**: `O(numero pezzi )`

### computer
Per trovare le celle in cui un pezzo può muoversi chiamo `isValidMove()` con `start_cell` quella del pezzo e `end_cell` ogni cella della scacchiera.

**complessità**: `O(numeri pezzi * 8 * 8)`

# Ciclo di gioco
    do {
        getNextMove();
        move();
        alternateTurn();
        isInCheck();
    } while (!IsGameOver());
    
In `IsGameOver()` chiama il metodo `canMove(colour c)`. Se non può muovere allora, se è in scacco è scacco matto altrimenti è patta.

`canMove(colour c)` ha complessità `O(numero pezzi avversari * 8 * 8 * numero pezzi avversari)`


# Considerazioni

Ad ogni mossa del colore c bisogna controllare:
prima della mossa:
- se la casella iniziale ha un pezzo del colore c
- se la casella finale è vuota o ha un pezzo del colore opposto
- se quel pezzo può fare la mossa -> `isValidMove()`

dopo la mossa:
- che il re di colore c non sia in scacco -> `isInCheck()` -> in chessboard
- se il re del colore opposto è in scacco -> `isInCheck()`
- se c'è uno stallo, se si -> patta -> `isStalemate()`


# Prossimi step
- aggiungere costanti - done
- `isInCheck(Colour c)` - done
- `canMove(Colour c)` - done
- `move()` - done
- mosse speciali 
    - promozione - done
    - en passant
    - arrocco
- classe `Game`
- classe `Player`
- classe `Computer` e `Human` derivate di `Player`

- ricordarsi di aggiornare `hasMoved()`
