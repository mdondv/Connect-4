#include "minimaxBis.h"
#include "heuristicBis.h"
#include "printaTauler.h"
#include "modesJoc.h"

void printaTauler(Node *arrel) {
    printf("+");
    for(int i=0; i<NCOLS; i++) {
        printf("---+");
    }
    
    for(int i=0; i<NFILES; i++) {
        printf("\n|");
        for(int j=0; j<NCOLS; j++) {
            if(arrel->tauler[i][j] == 'X') printf("\x1b[36;40m %c ", arrel->tauler[i][j]);
            else printf("\x1b[33;40m %c ", arrel->tauler[i][j]);
            printf("\033[0m|");
        }
    } printf("\n+");
    
    for(int i=0; i<NCOLS; i++) {
        printf("---+");
    } printf("\n");
    
    printf("|");
    for(int i=0; i<NCOLS; i++) {
        if(i < 9) printf(" %d ", i+1);
        else printf(" %d ", i+1);
        printf("|");
    }
    printf("\n+");
    
    for(int i=0; i<NCOLS; i++) {
        printf("---+");
    } printf("\n\n");
}

void printaGoldVert(Node *arrel, int l, int m) {
    printf("+");
    for(int i=0; i<NCOLS; i++) {
        printf("---+");
    }
    
    int n = 0;
    for(int i=0; i<NFILES; i++) {
        printf("\n|");
        for(int j=0; j<NCOLS; j++) {
            if(i == l-3 && j == m && n<4) {
                printf("\033[1;34m %c ", arrel->tauler[i][j]);
                n += 1;
                l += 1;
            }
            else {
                if(arrel->tauler[i][j] == 'X') printf("\x1b[36;40m %c ", arrel->tauler[i][j]);
                else printf("\x1b[33;40m %c ", arrel->tauler[i][j]);
            }
            printf("\033[0m|");
        }
    } printf("\n+");
    
    for(int i=0; i<NCOLS; i++) {
        printf("---+");
    } printf("\n");
    
    printf("|");
    for(int i=0; i<NCOLS; i++) {
        if(i < 9) printf(" %d ", i+1);
        else printf(" %d ", i+1);
        printf("|");
    }
    printf("\n+");
    
    for(int i=0; i<NCOLS; i++) {
        printf("---+");
    } printf("\n\n");
}

void printaGoldHorit(Node *arrel, int l, int m) {
    printf("+");
    for(int i=0; i<NCOLS; i++) {
        printf("---+");
    }
    
    int n = 0;
    for(int i=0; i<NFILES; i++) {
        printf("\n|");
        for(int j=0; j<NCOLS; j++) {
            if(i == l && j == m-3 && n<4) {
                printf("\033[1;34m %c ", arrel->tauler[i][j]);
                n += 1;
                m += 1;
            }
            else {
                if(arrel->tauler[i][j] == 'X') printf("\x1b[36;40m %c ", arrel->tauler[i][j]);
                else printf("\x1b[33;40m %c ", arrel->tauler[i][j]);
            }
            printf("\033[0m|");
        }
    } printf("\n+");
    
    for(int i=0; i<NCOLS; i++) {
        printf("---+");
    } printf("\n");
    
    printf("|");
    for(int i=0; i<NCOLS; i++) {
        if(i < 9) printf(" %d ", i+1);
        else printf(" %d ", i+1);
        printf("|");
    }
    printf("\n+");
    
    for(int i=0; i<NCOLS; i++) {
        printf("---+");
    } printf("\n\n");
}

void printaGoldObl45(Node *arrel, int l, int m) {
    printf("+");
    for(int i=0; i<NCOLS; i++) {
        printf("---+");
    }
    
    int n = 0;
    for(int i=0; i<NFILES; i++) {
        printf("\n|");
        for(int j=0; j<NCOLS; j++) {
            if(i == l-3 && j == m+3 && n<4) {
                printf("\033[1;34m %c ", arrel->tauler[i][j]);
                n += 1;
                m -= 1;
                l += 1;
            }
            else {
                if(arrel->tauler[i][j] == 'X') printf("\x1b[36;40m %c ", arrel->tauler[i][j]);
                else printf("\x1b[33;40m %c ", arrel->tauler[i][j]);
            }
            printf("\033[0m|");
        }
    } printf("\n+");
    
    for(int i=0; i<NCOLS; i++) {
        printf("---+");
    } printf("\n");
    
    printf("|");
    for(int i=0; i<NCOLS; i++) {
        if(i < 9) printf(" %d ", i+1);
        else printf(" %d ", i+1);
        printf("|");
    }
    printf("\n+");
    
    for(int i=0; i<NCOLS; i++) {
        printf("---+");
    } printf("\n\n");
}

void printaGoldObl135(Node *arrel, int l, int m) {
    printf("+");
    for(int i=0; i<NCOLS; i++) {
        printf("---+");
    }

    int n = 0;
    for(int i=0; i<NFILES; i++) {
        printf("\n|");
        for(int j=0; j<NCOLS; j++) {
            if(i == l && j == m && n<4) {
                printf("\033[1;34m %c ", arrel->tauler[i][j]);
                n += 1;
                m += 1;
                l += 1;
            }
            else {
                if(arrel->tauler[i][j] == 'X') printf("\x1b[36;40m %c ", arrel->tauler[i][j]);
                else printf("\x1b[33;40m %c ", arrel->tauler[i][j]);
            }
            printf("\033[0m|");
        }
    } printf("\n+");
    
    for(int i=0; i<NCOLS; i++) {
        printf("---+");
    } printf("\n");
    
    printf("|");
    for(int i=0; i<NCOLS; i++) {
        if(i < 9) printf(" %d ", i+1);
        else printf(" %d ", i+1);
        printf("|");
    }
    printf("\n+");
    
    for(int i=0; i<NCOLS; i++) {
        printf("---+");
    } printf("\n\n");
}

void initTauler(Node *pare) {
    for(int i=0; i<NFILES; i++) {
        for(int j=0; j<NCOLS; j++) {
            pare->tauler[i][j] = ' ';
        }
    }
}

void copiaTauler(Node *fill, Node *pare) {
    for(int i=0; i<NFILES; i++) {
        for(int j=0; j<NCOLS; j++) {
            fill->tauler[i][j] = pare->tauler[i][j];
        }
    }
}

void rotacio(Node *node) {
    char aux[NFILES][NCOLS];
    
    for(int i=0; i<NFILES; i++) {
        for(int j=0; j<NCOLS; j++) {
            aux[i][j] = node->tauler[j][i];
        }
    }
    for(int i=0; i<NFILES; i++) {
        for(int j=0; j<NCOLS; j++) {
            node->tauler[i][j] = aux[i][j];
        }
    }
    int k = 0;
    for(int j=0; j<NCOLS; j++) {
        for(int i=NFILES-1; i>=0; i--) {
            if(node->tauler[i][j] != ' ') {
                if(k != 0) {
                    node->tauler[i+k][j] = node->tauler[i][j];
                    node->tauler[i][j] = ' ';
                }
            }
            else k += 1;
        }
        k = 0;
    }
}

void canviaGravetat(Node *node, int mode) {
    if(mode == 0) {
        int k = 0;
        for(int j=0; j<NCOLS; j++) {
            for(int i=0; i<NFILES; i++) {
                if(node->tauler[i][j] != ' ') {
                    if(k != 0) {
                        node->tauler[i-k][j] = node->tauler[i][j];
                        node->tauler[i][j] = ' ';
                    }
                }
                else k += 1;
            }
            k = 0;
        }
    }
    if(mode == 1) {
        int k = 0;
        for(int j=0; j<NCOLS; j++) {
            for(int i=NFILES-1; i>=0; i--) {
                if(node->tauler[i][j] != ' ') {
                    if(k != 0) {
                        node->tauler[i+k][j] = node->tauler[i][j];
                        node->tauler[i][j] = ' ';
                    }
                }
                else k += 1;
            }
            k = 0;
        }
    }
}

void canviaColumnes(Node *node, int l, int m) {
    char aux[NFILES][NCOLS];
    
    for(int i=0; i<NFILES; i++) {
        for(int j=0; j<NCOLS; j++) {
            aux[i][j] = node->tauler[i][j];
        }
    }
    for(int i=0; i<NFILES; i++) {
        node->tauler[i][l] = aux[i][m];
        node->tauler[i][m] = aux[i][l];
    }
}

