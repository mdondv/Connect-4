#include "minimax.h"
#include "heuristic.h"
#include "printaTauler.h"
#include "modesJoc.h"

int numFills(Node *pare) {
    int n_fills = 0;
    for(int j=0; j<NCOLS; j++) {
        if(pare->tauler[0][j] == ' ' && checkWinBis(pare) != 1)  {
            n_fills += 1;
        }
    }
    return n_fills;
}

int numFillsAntiGrav(Node *pare) {
    int n_fills = 0;
    for(int j=0; j<NCOLS; j++) {
        if(pare->tauler[NFILES-1][j] == ' ' && checkWinBis(pare) != 1)  {
            n_fills += 1;
        }
    }
    return n_fills;
}

void ferTirada(Node *fill, int numDeFill, int nivell) {
    for(int i=NFILES-1; i>=0; i--) {
        if(fill->tauler[i][numDeFill] == ' ') {
            if(nivell % 2 == 0){
                fill->tauler[i][numDeFill] = 'X';
            }
            else fill->tauler[i][numDeFill] = 'O';
            break;
        }
    }
}

void ferTiradaAntiGrav(Node *fill, int numDeFill, int nivell) {
    for(int i=0; i<NFILES; i++) {
        if(fill->tauler[i][numDeFill] == ' ') {
            if(nivell % 2 == 0){
                fill->tauler[i][numDeFill] = 'X';
            }
            else fill->tauler[i][numDeFill] = 'O';
            break;
        }
    }
}

Node *crearNode(Node *pare, int numDeFill, int nivell, int prof) {
    Node *p = malloc(sizeof(Node));
    initTauler(p);
    copiaTauler(p, pare);
    ferTirada(p, numDeFill, nivell);
    p->valor = heuristic(p);

    if (nivell<prof && checkWinBis(pare) != 1) {
        p->n_fills = numFills(p);
        p->fills = malloc(p->n_fills * sizeof(Node *));
    }
    else {
        p->n_fills = 0;
        p->fills = NULL;
    }
    return p;
}

Node *crearNodeAntiGrav(Node *pare, int numDeFill, int nivell, int prof) {
    Node *p = malloc(sizeof(Node));
    initTauler(p);
    copiaTauler(p, pare);
    ferTiradaAntiGrav(p, numDeFill, nivell);
    p->valor = heuristicAntiGravetat(p);

    if (nivell<prof && checkWinBis(pare) != 1) {
        p->n_fills = numFills(p);
        p->fills = malloc(p->n_fills * sizeof(Node *));
    }
    else {
        p->n_fills = 0;
        p->fills = NULL;
    }
    return p;
}

void crearNivell(Node *pare, int nivell, int prof) {
    int k = 0;
    for(int i=0; i<pare->n_fills; i++) {
        for(int j=k; j<NCOLS; j++) {
            if(pare->tauler[0][j] == ' ' && checkWinBis(pare) != 1)  {
                pare->fills[i] = crearNode(pare, j, nivell, prof);
                k = j+1;
                break;
            }
        }
    }
}

void crearNivellAntiGrav(Node *pare, int nivell, int prof) {
    int k = 0;
    for(int i=0; i<pare->n_fills; i++) {
        for(int j=k; j<NCOLS; j++) {
            if(pare->tauler[NFILES-1][j] == ' ' && checkWinBis(pare) != 1)  {
                pare->fills[i] = crearNodeAntiGrav(pare, j, nivell, prof);
                k = j+1;
                break;
            }
        }
    }
}

void crearArbreRec(Node *arrel, int nivell, int prof) {
    crearNivell(arrel, nivell, prof);
    if (arrel->n_fills>0) {
        for(int i=0; i<arrel->n_fills; i++) {
            crearArbreRec(arrel->fills[i], nivell+1, prof);
        }
    }
}

void crearArbreRecAntiGrav(Node *arrel, int nivell, int prof) {
    crearNivellAntiGrav(arrel, nivell, prof);
    if (arrel->n_fills>0) {
        for(int i=0; i<arrel->n_fills; i++) {
            crearArbreRecAntiGrav(arrel->fills[i], nivell+1, prof);
        }
    }
}

void minimax(Node *arrel, int nivell, int mode) {
    double aux;
    
    srand(time(0));
    if(arrel->n_fills>0) {
        for(int i=0; i<arrel->n_fills; i++) {
            minimax(arrel->fills[i], nivell+1, 0);
            if(i == 0)  {
                aux = (arrel->fills[i])->valor;
            }
            if ((nivell % 2) == 0) {
                if(aux < (arrel->fills[i])->valor) {
                    aux = (arrel->fills[i])->valor;
                }
                else aux += 0;
            }
            else if((nivell % 2) == 1) {
                if (aux > (arrel->fills[i])->valor) {
                    aux = (arrel->fills[i])->valor;
                }
                else aux += 0;
            }
        }
        arrel->valor = aux;
        if(nivell == 0) {
            for(int i=0; i<arrel->n_fills; i++) {
                if (arrel->valor == (arrel->fills[i])->valor) {
                    int cont = -1;
                    for(int k=0; k<NCOLS; k++) {
                        if(mode == 0) {
                            if(arrel->tauler[0][k] == ' ') {
                                cont += 1;
                            }
                            if(cont == i) {
                                printf("La màquina ha decidit tirar a la columna %d\n", k+1);
                                break;
                            }
                        }
                        else if(mode == 1) {
                            if(arrel->tauler[NFILES-1][k] == ' ') {
                                cont += 1;
                            }
                            if(cont == i) {
                                printf("La màquina ha decidit tirar a la columna %d\n", k+1);
                                break;
                            }
                        }
                    }
                    copiaTauler(arrel, arrel->fills[i]);
                    break;
                }
            }
        }
    }
}

void destrueixArbreRec(Node *node) {
    if(node->n_fills>0) {
        for(int i=0; i<node->n_fills; i++) {
            destrueixArbreRec(node->fills[i]);
        }
    }
    free(node);
}

int checkWinBis(Node *node) {
    int contX = 0, contO = 0, vertX = 0, vertO = 0;
    for(int j=0; j<NCOLS; j++) {//vertical check
        for(int i=NFILES-1; i>=3; i--){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i-k][j]) {
                    vertX += 1;
                }
                else if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i-k][j]) {
                    vertO += 1;
                }
            }
            if(vertX == 4) contX += 1;
            else if(vertO == 4) contO += 1;
            vertX = 0;
            vertO = 0;
        }
    }
    int horitX = 0, horitO = 0;
    for(int i=NFILES-1; i>=0; i--) {//horizontal check
        for(int j=NCOLS-1; j>=3; j--){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i][j-k]) horitX += 1;
                else if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i][j-k]) horitO += 1;
            }
            if(horitX == 4) contX += 1;
            else if(horitO == 4) contO += 1;
            horitX = 0;
            horitO = 0;
        }
    }
    int obl135X = 0, obl135O = 0;
    for(int j=0; j<NCOLS-3; j++){//check oblicuo de 135 grados
        for(int i=NFILES-4; i>=0; i--){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i+k][j+k]) obl135X += 1;
                else if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i+k][j+k]) obl135O += 1;
            }
            if(obl135X == 4) contX += 1;
            else if(obl135O == 4) contO += 1;
            obl135X = 0;
            obl135O = 0;
        }
    }
    int obl45X = 0, obl45O = 0;
    for(int j=0; j<NCOLS-3; j++){//check oblicuo de 45 grados
        for(int i=NFILES-1; i>=3; i--){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i-k][j+k]) obl45X += 1;
                else if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i-k][j+k]) obl45O += 1;
            }
            if(obl45X == 4) contX += 1;
            else if(obl45O == 4) contO += 1;
            obl45X = 0;
            obl45O = 0;
        }
    }
    if(contX >= 1 && contO == 0) return 1;
    else if(contX == 0 && contO >= 1) return 1;
    else if (contX > 0 && contO > 0) return 1;
    else return 0;
}

int checkWin(Node *node) {
    int contX = 0, contO = 0, vertX = 0, vertO = 0;
    for(int j=0; j<NCOLS; j++) {//vertical check
        for(int i=NFILES-1; i>=3; i--){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i-k][j]) {
                    vertX += 1;
                }
                else if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i-k][j]) {
                    vertO += 1;
                }
            }
            if(vertX == 4) {
                contX += 1;
                printaGoldVert(node, i, j);
            }
            else if(vertO == 4) {
                contO += 1;
                printaGoldVert(node, i, j);
            }
            vertX = 0;
            vertO = 0;
        }
    }
    int horitX = 0, horitO = 0;
    for(int i=NFILES-1; i>=0; i--) {//horizontal check
        for(int j=NCOLS-1; j>=3; j--){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i][j-k]) {
                    horitX += 1;
                }
                else if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i][j-k]) {
                    horitO += 1;
                }
            }
            if(horitX == 4) {
                contX += 1;
                printaGoldHorit(node, i, j);
            }
            else if(horitO == 4) {
                contO += 1;
                printaGoldHorit(node, i, j);
            }
            horitX = 0;
            horitO = 0;
        }
    }
    int obl135X = 0, obl135O = 0;
    for(int j=0; j<NCOLS-3; j++){//check oblicuo de 135 grados
        for(int i=NFILES-4; i>=0; i--){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i+k][j+k]) {
                    obl135X += 1;
                }
                else if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i+k][j+k]) {
                    obl135O += 1;
                }
            }
            if(obl135X == 4) {
                contX += 1;
                printaGoldObl135(node, i, j);
            }
            else if(obl135O == 4) {
                contO += 1;
                printaGoldObl135(node, i, j);
            }
            obl135X = 0;
            obl135O = 0;
        }
    }
    int obl45X = 0, obl45O = 0;
    for(int j=0; j<NCOLS-3; j++){//check oblicuo de 45 grados
        for(int i=NFILES-1; i>=3; i--){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i-k][j+k]) {
                    obl45X += 1;
                }
                else if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i-k][j+k]) {
                    obl45O += 1;
                }
            }
            if(obl45X == 4) {
                contX += 1;
                printaGoldObl45(node, i, j);
            }
            else if(obl45O == 4) {
                contO += 1;
                printaGoldObl45(node, i, j);
            }
            obl45X = 0;
            obl45O = 0;
        }
    }
    if(contX >= 1 && contO == 0) {
        printf("YOU WIN!\n\n");
        return 1;
    }
    else if(contX == 0 && contO >= 1) {
        printf("GAME OVER! \u2620\n\n");
        return 1;
    }
    else if (contX > 0 && contO > 0){
        printf("Draws!\n\n");
        return 1;
    }
    else return 0;
}
