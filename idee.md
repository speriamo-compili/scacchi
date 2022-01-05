# Generali

Il bianco muove sempre per primo.

Al giocatore umano è assegnato il colore bianco o nero a caso.

Nel log le lettere maiuscole sono utilizzate per i pezzi neri e quelle minuscole per i pezzi bianchi.

Con il comando "XX XX" il giocatore chiede di stampare la scacchiera.

Partite di due tipi:
- giocatore vs computer
- computer vs computer

# Regole



# Classi

## `Piece` (classe astratta)
contiene la funzione astratta:

`virtual bool isValidMove(Cell& start_cell, Cell& end_cell) = 0;`

`virtual char print_piece() = 0;`

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

## Alla fine
- controllare che ci sia `const` dove deve andare 
- controllare che i parametri siano passati per reference (dove deve andare)