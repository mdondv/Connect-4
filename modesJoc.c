#include "minimaxBis.h"
#include "heuristicBis.h"
#include "printaTauler.h"
#include "modesJoc.h"

void dosJugadors(Node *node) {
    int col;
    char str[3];
    srand(time(0));
    
    for(int k=0; k<NFILES*NCOLS; k++) {
        printf("A quina columna vols tirar?\n");
        fflush(stdin);
        fgets(str, 3, stdin);
        col = atoi(str);
        
        while(col > NCOLS || col <= 0 || node->tauler[0][col-1] != ' ') {
            printf("Resposta errònia. Respon amb un número enter entre 1 i 8\n");
            fflush(stdin);
            fgets(str, 3, stdin);
            col = atoi(str);
        }
        ferTirada(node, col-1, k);
    
        printaTauler(node);
        if(checkWin(node) == 1) break;
    }
}


void jugadorAleatori(Node *node, int prof) {
    int col;
    char str[3];
    
    srand(time(0));
    int quiComença = rand() % 2;
    
    printf("\n");
    for(int k = quiComença; k<NFILES*NCOLS; k++) {
        fflush(stdin);
        if(k % 2 == 0) {
            fflush(stdin);
            printf("A quina columna vols tirar?\n");
            fgets(str, 3, stdin);
            col = atoi(str);
            while(col > NCOLS || col <= 0 || node->tauler[0][col-1] != ' ') {
                fflush(stdin);
                printf("Resposta errònia. Respon amb un número enter entre 1 i 8\n");
                fgets(str, 3, stdin);
                col = atoi(str);
            }
            ferTirada(node, col-1, k);
        }
        else if(k % 2 == 1) {
            if(k == 1) {
                int col2 = rand() % 4 + 3;
                printf("\nL'ordinador ha començat tirant a la columna %d\n", col2);
                ferTirada(node, col2-1, k);
            }
            else {
                crearArbreRec(node, 1, prof);
                minimax(node, 0, 0);
                for(int i=0; i<node->n_fills; i++) {
                    destrueixArbreRec(node->fills[i]);
                }
            }
        }
        node->n_fills = numFills(node);
        printaTauler(node);
        if(checkWin(node) == 1) break;
    }
}


void jugadorRotacio(Node *node, int prof) {
    int col;
    char str[3];

    srand(time(0));
    int quiComença = rand() % 2;
    
    printf("\n");
    for(int k = quiComença; k<NFILES*NCOLS; k++) {
        fflush(stdin);
        if(k % 2 == 0) {
            printf("Vols fer una rotació al tauler? Respon amb y/n\n");
            fflush(stdin);
            fgets(str, 2, stdin);
            while(strcmp(str, "y") != 0 && strcmp(str, "n") != 0) {
                fflush(stdin);
                printf("Resposta errònia. Respon amb y/n\n");
                fgets(str, 2, stdin);
            }
            if(strcmp(str, "y") == 0) {
                printf("Atenció! El tauler ha rotat\n");
                rotacio(node);
                printaTauler(node);
                if(checkWin(node) == 1) break;
            }
            else if (strcmp(str, "n") == 0) {
                fflush(stdin);
                printf("A quina columna vols tirar?\n");
                fgets(str, 3, stdin);
                col = atoi(str);
                while(col > NCOLS || col <= 0 || node->tauler[0][col-1] != ' ') {
                    fflush(stdin);
                    printf("Resposta errònia. Respon amb un número enter entre 1 i 8\n");
                    fgets(str, 3, stdin);
                    col = atoi(str);
                }
                ferTirada(node, col-1, k);
            }
        }
        else if(k % 2 == 1) {
            if(k == 1) {
                int col2 = rand() % 4 + 3;
                printf("\nL'ordinador ha començat tirant a la columna %d\n", col2);
                ferTirada(node, col2-1, k);
            }
            else {
                crearArbreRec(node, 1, prof);
                minimax(node, 0, 0);
                for(int i=0; i<node->n_fills; i++) {
                    destrueixArbreRec(node->fills[i]);
                }
            }
        }
        node->n_fills = numFills(node);
        printaTauler(node);
        if(checkWin(node) == 1) break;
    }
}


void jugadorRotacioRandom(Node *node, int prof) {
    int col;
    char str[3];

    srand(time(0));
    int quiComença = rand() % 2;
    
    printf("\n");
    for(int k = quiComença; k<NFILES*NCOLS; k++) {
        fflush(stdin);
        if(k % 2 == 0) {
            if(rand() % 2 == 0) {
                rotacio(node);
                printf("Atenció! El tauler ha rotat\n");
                printaTauler(node);
                if(checkWin(node) == 1) break;
            }
            fflush(stdin);
            printf("A quina columna vols tirar?\n");
            fgets(str, 3, stdin);
            col = atoi(str);
            while(col > NCOLS || col <= 0 || node->tauler[0][col-1] != ' ') {
                fflush(stdin);
                printf("Resposta errònia. Respon amb un número enter entre 1 i 8\n");
                fgets(str, 3, stdin);
                col = atoi(str);
            }
            ferTirada(node, col-1, k);
        }
        else if(k % 2 == 1) {
            if(k == 1) {
                int col2 = rand() % 4 + 3;
                printf("\nL'ordinador ha començat tirant a la columna %d\n", col2);
                ferTirada(node, col2-1, k);
            }
            else {
                crearArbreRec(node, 1, prof);
                minimax(node, 0, 0);
                for(int i=0; i<node->n_fills; i++) {
                    destrueixArbreRec(node->fills[i]);
                }
            }
        }
        node->n_fills = numFills(node);
        printaTauler(node);
        if(checkWin(node) == 1) break;
    }
}


void antiGravetat(Node *node, int prof) {
    
    int col;
    char str[3];

    srand(time(0));
    int quiComença = rand() % 2;
    int mode = 0;//iniciem el tauler com un tauler normal. Mode 0 és amb gravetat i mode 1 amb gravetat invertida
    
    printf("\n");
    for(int k = quiComença; k<NFILES*NCOLS; k++) {
        fflush(stdin);
        if(k % 2 == 0) {
            printf("Vols invertir la gravetat del tauler? Respon amb y/n\n");
            fflush(stdin);
            fgets(str, 2, stdin);
            while(strcmp(str, "y") != 0 && strcmp(str, "n") != 0) {
                printf("Resposta errònia. Respon amb y/n\n");
                fflush(stdin);
                fgets(str, 2, stdin);
            }
            if(strcmp(str, "y") == 0) {
                canviaGravetat(node, mode);
                if(mode == 0) mode = 1;
                else mode = 0;
                printf("Atenció! S'ha invertit la gravetat del tauler!\n");
                printaTauler(node);
                if(checkWin(node) == 1) break;
            }
            else if(strcmp(str, "n") == 0) {
                printf("A quina columna vols tirar?\n");
                fflush(stdin);
                fgets(str, 3, stdin);
                col = atoi(str);
                if(mode == 0) {
                    while(col > NCOLS || col <= 0 || node->tauler[0][col-1] != ' ') {
                        fflush(stdin);
                        printf("Resposta errònia. Respon amb un número enter entre 1 i 8\n");
                        fgets(str, 3, stdin);
                        col = atoi(str);
                    }
                    ferTirada(node, col-1, k);
                }
                if(mode == 1) {
                    while(col > NCOLS || col <= 0 || node->tauler[NFILES-1][col-1] != ' ') {
                        printf("Resposta errònia. Respon amb un número enter entre 1 i 8\n");
                        fflush(stdin);
                        fgets(str, 3, stdin);
                        col = atoi(str);
                    }
                    ferTiradaAntiGrav(node, col-1, k);
                }
            }
        }
        else if(k % 2 == 1) {
            if(k == 1) {
                int col2 = rand() % 4 + 3;
                printf("\nL'ordinador ha començat tirant a la columna %d\n", col2);
                if(k == 1) {
                    int col2 = rand() % 4 + 3;
                    printf("\nL'ordinador ha començat tirant a la columna %d\n", col2);
                    if(mode == 0) ferTirada(node, col2-1, k);
                    if(mode == 1) ferTiradaAntiGrav(node, col2-1, k);
                }
            }
            else {
                if(mode == 0) {
                    crearArbreRec(node, 1, prof);
                    minimax(node, 0, mode);
                    for(int i=0; i<node->n_fills; i++) {
                        destrueixArbreRec(node->fills[i]);
                    }
                }
                if(mode == 1) {
                    crearArbreRecAntiGrav(node, 1, prof);
                    minimax(node, 0, mode);
                    for(int i=0; i<node->n_fills; i++) {
                        destrueixArbreRec(node->fills[i]);
                    }
                }
            }
        }
        if(mode == 0) {
            node->n_fills = numFills(node);
        }
        if(mode == 1) {
            node->n_fills = numFillsAntiGrav(node);
        }
        printaTauler(node);
        if(checkWin(node) == 1) break;
    }
}

void antiGravetatRandom(Node *node, int prof) {
    int col;
    char str[3];

    srand(time(0));
    int quiComença = rand() % 2;
    int mode = 0;
    
    printf("\n");
    for(int k = quiComença; k<NFILES*NCOLS; k++) {
        fflush(stdin);
        if(k % 2 == 0) {
            if(rand() % 2 == 0) {
                canviaGravetat(node, mode);
                if(mode == 0) mode = 1;
                else mode = 0;
                printf("Atenció! S'ha invertit la gravetat del tauler!\n");
                printaTauler(node);
                if(checkWin(node) == 1) break;
            }
            printf("A quina columna vols tirar?\n");
            fflush(stdin);
            fgets(str, 3, stdin);
            col = atoi(str);
            if(mode == 0) {
                while(col > NCOLS || col <= 0 || node->tauler[0][col-1] != ' ') {
                    fflush(stdin);
                    printf("Resposta errònia. Respon amb un número enter entre 1 i 8\n");
                    fgets(str, 3, stdin);
                    col = atoi(str);
                }
                ferTirada(node, col-1, k);
            }
            if(mode == 1) {
                while(col > NCOLS || col <= 0 || node->tauler[NFILES-1][col-1] != ' ') {
                    printf("Resposta errònia. Respon amb un número enter entre 1 i 8\n");
                    fflush(stdin);
                    fgets(str, 3, stdin);
                    col = atoi(str);
                }
                ferTiradaAntiGrav(node, col-1, k);
            }
        }
        else if(k % 2 == 1) {
            if(k == 1) {
                int col2 = rand() % 4 + 3;
                printf("\nL'ordinador ha començat tirant a la columna %d\n", col2);
                if(mode == 0) ferTirada(node, col2-1, k);
                if(mode == 1) ferTiradaAntiGrav(node, col2-1, k);
            }
            else {
                if(mode == 0) {
                    crearArbreRec(node, 1, prof);
                    minimax(node, 0, mode);
                    for(int i=0; i<node->n_fills; i++) {
                        destrueixArbreRec(node->fills[i]);
                    }
                }
                if(mode == 1) {
                    crearArbreRecAntiGrav(node, 1, prof);
                    minimax(node, 0, mode);
                    for(int i=0; i<node->n_fills; i++) {
                        destrueixArbreRec(node->fills[i]);
                    }
                }
            }
        }
        if(mode == 0) {
            node->n_fills = numFills(node);
        }
        if(mode == 1) {
            node->n_fills = numFillsAntiGrav(node);
        }
        printaTauler(node);
        if(checkWin(node) == 1) break;
    }
}

void handle(int sig) {
    printf("\nGAME OVER! \u2620\n");
    printf("Si vols tornar a jugar, torna a executar el programa.\n");
    exit(0);
}

void contraRellotge(Node *node, int prof) {
    
    int col;
    char str[3], limitTemps[3];
    signal(SIGALRM, handle);
    
    printf("Quin vols que sigui el límit de temps (en segons) per jugada?\n");
    fflush(stdin);
    fgets(limitTemps, 3, stdin);
    while(atoi(limitTemps) > 20) {
        printf("El marge de temps que has donat és massa gran. Arrisca't una mica i rebaixa'l!");
        fflush(stdin);
        fgets(limitTemps, 3, stdin);
    }
    
    srand(time(0));
    int quiComença = rand() % 2;
    
    printf("\n");
    for(int k=quiComença; k<NFILES*NCOLS; k++) {
        fflush(stdin);
        if(k % 2 == 0) {
            alarm(atoi(limitTemps));
            fflush(stdin);
            printf("A quina columna vols tirar?\n");
            fgets(str, 3, stdin);
            col = atoi(str);
            while(col > NCOLS || col <= 0 || node->tauler[0][col-1] != ' ') {
                fflush(stdin);
                printf("Resposta errònia. Respon amb un número enter entre 1 i 8\n");
                fgets(str, 3, stdin);
                col = atoi(str);
            }
            ferTirada(node, col-1, k);
        }
        else if(k % 2 == 1) {
            if(k == 1) {
                int col2 = rand() % 4 + 3;
                printf("\nL'ordinador ha començat tirant a la columna %d\n", col2);
                ferTirada(node, col2-1, k);
            }
            else {
                crearArbreRec(node, 1, prof);
                minimax(node, 0, 0);
                for(int i=0; i<node->n_fills; i++) {
                    destrueixArbreRec(node->fills[i]);
                }
            }
        }
        alarm(0);
        node->n_fills = numFills(node);
        printaTauler(node);
        if(checkWin(node) == 1) break;
    }
}

void contraRellotgeRandom(Node *node, int prof) {
    int col;
    char str[3], limitTemps[3];
    signal(SIGALRM, handle);
    
    printf("Quin vols que sigui el límit de temps (en segons) per jugada?\n");
    fflush(stdin);
    fgets(limitTemps, 3, stdin);
    while(atoi(limitTemps) > 20) {
        printf("El marge de temps que has donat és massa gran. Arrisca't una mica i rebaixa'l!");
        fflush(stdin);
        fgets(limitTemps, 3, stdin);
    }
    
    srand(time(0));
    int quiComença = rand() % 2;
    int mode = 0;
    
    printf("\n");
    for(int k = quiComença; k<NFILES*NCOLS; k++) {
        fflush(stdin);
        if(k % 2 == 0) {
            if(rand() % 2 == 0) {
                canviaGravetat(node, mode);
                if(mode == 0) mode = 1;
                else mode = 0;
                printf("Atenció! S'ha invertit la gravetat del tauler!\n");
                printaTauler(node);
                if(checkWin(node) == 1) break;
            }
            alarm(atoi(limitTemps));
            printf("A quina columna vols tirar?\n");
            fflush(stdin);
            fgets(str, 3, stdin);
            col = atoi(str);
            if(mode == 0) {
                while(col > NCOLS || col <= 0 || node->tauler[0][col-1] != ' ') {
                    fflush(stdin);
                    printf("Resposta errònia. Respon amb un número enter entre 1 i 8\n");
                    fgets(str, 3, stdin);
                    col = atoi(str);
                }
                ferTirada(node, col-1, k);
            }
            if(mode == 1) {
                while(col > NCOLS || col <= 0 || node->tauler[NFILES-1][col-1] != ' ') {
                    printf("Resposta errònia. Respon amb un número enter entre 1 i 8\n");
                    fflush(stdin);
                    fgets(str, 3, stdin);
                    col = atoi(str);
                }
                ferTiradaAntiGrav(node, col-1, k);
            }
        }
        else if(k % 2 == 1) {
            if(k == 1) {
                int col2 = rand() % 4 + 3;
                printf("\nL'ordinador ha començat tirant a la columna %d\n", col2);
                ferTirada(node, col2-1, k);
            }
            else {
                if(mode == 0) {
                    crearArbreRec(node, 1, prof);
                    minimax(node, 0, mode);
                    for(int i=0; i<node->n_fills; i++) {
                        destrueixArbreRec(node->fills[i]);
                    }
                }
                if(mode == 1) {
                    crearArbreRecAntiGrav(node, 1, prof);
                    minimax(node, 0, mode);
                    for(int i=0; i<node->n_fills; i++) {
                        destrueixArbreRec(node->fills[i]);
                    }
                }
            }
        }
        alarm(0);
        if(mode == 0) {
            node->n_fills = numFills(node);
        }
        if(mode == 1) {
            node->n_fills = numFillsAntiGrav(node);
        }
        printaTauler(node);
        if(checkWin(node) == 1) break;
    }
}


void tetris(Node *node, int prof) {
    int col;
    char str[3];
    
    srand(time(0));
    int quiComença = rand() % 2;
    
    printf("\n");
    for(int k = quiComença; k<NFILES*NCOLS; k++) {
        fflush(stdin);
        if(k % 2 == 0) {
            fflush(stdin);
            printf("A quina columna vols tirar?\n");
            fgets(str, 3, stdin);
            col = atoi(str);
            while(col > NCOLS || col <= 0 || node->tauler[0][col-1] != ' ') {
                fflush(stdin);
                printf("Resposta errònia. Respon amb un número enter entre 1 i 8\n");
                fgets(str, 3, stdin);
                col = atoi(str);
            }
            ferTirada(node, col-1, k);
        }
        else if(k % 2 == 1) {
            if(k == 1) {
                int col2 = rand() % 4 + 3;
                printf("\nHa començat tirant l'ordinador a la columna %d\n", col2);
                ferTirada(node, col2-1, k);
            }
            else {
                crearArbreRec(node, 1, prof);
                minimax(node, 0, 0);
                for(int i=0; i<node->n_fills; i++) {
                    destrueixArbreRec(node->fills[i]);
                }
            }
        }
        node->n_fills = numFills(node);
        if(checkWin(node) == 1) break;
        int cont = 0;
        for(int j=0; j<NCOLS; j++) {
            if(node->tauler[NFILES-1][j] != ' ') {
                cont += 1;
            }
        }
        if(cont == NCOLS) {
            for(int j=0; j<NCOLS; j++) {
                for(int i=NFILES-1; i>=1; i--) {
                    node->tauler[i][j] = node->tauler[i-1][j];
                }
                node->tauler[0][j] = ' ';
            }
        }
        node->n_fills = numFills(node);
        printaTauler(node);
    }
}

void permutaColumnes(Node *node, int prof) {
    int col, col2;
    char str[2], str2[2], str3[3];

    srand(time(0));
    int quiComença = rand() % 2;
    
    printf("\n");
    for(int k = quiComença; k<NFILES*NCOLS; k++) {
        fflush(stdin);
        if(k % 2 == 0) {
            if(rand() % 2 == 0) {
                printf("Vols intercanviar dues columnes aleatòriament?\n");
                fflush(stdin);
                fgets(str, 2, stdin);
                while(strcmp(str, "y") != 0 && strcmp(str, "n") != 0) {
                    printf("Resposta errònia. Respon amb y/n\n");
                    fflush(stdin);
                    fgets(str, 2, stdin);
                }
                if(strcmp(str, "y") == 0) {
                    printf("Escull la primera columna que vols permutar\n");
                    fflush(stdin);
                    fgets(str2, 3, stdin);
                    col = atoi(str2);
                    while(col > NCOLS || col <= 0 || node->tauler[0][col-1] != ' ') {
                        fflush(stdin);
                        printf("Resposta errònia. Respon amb un número enter entre 1 i 8\n");
                        fgets(str2, 3, stdin);
                    }
                    printf("Escull la segona columna que vols permutar\n");
                    fflush(stdin);
                    fgets(str3, 3, stdin);
                    col = atoi(str3);
                    while(col > NCOLS || col <= 0 || node->tauler[0][col-1] != ' ') {
                        fflush(stdin);
                        printf("Resposta errònia. Respon amb un número enter entre 1 i 8\n");
                        fgets(str3, 3, stdin);
                    }
                    printf("Atencio! S'han permutat les columnes %d-%d", atoi(str2), atoi(str3));
                    canviaColumnes(node, atoi(str2)-1, atoi(str3)-1);
                    printaTauler(node);
                    if(checkWin(node) == 1) break;
                }
                else if (strcmp(str, "n") == 0) {
                    fflush(stdin);
                    printf("A quina columna vols tirar?\n");
                    fgets(str, 3, stdin);
                    col = atoi(str);
                    while(col > NCOLS || col <= 0 || node->tauler[0][col-1] != ' ') {
                        fflush(stdin);
                        printf("Resposta errònia. Respon amb un número enter entre 1 i 8\n");
                        fgets(str, 3, stdin);
                        col = atoi(str);
                    }
                    ferTirada(node, col-1, k);
                }
            }
            else {
                fflush(stdin);
                printf("A quina columna vols tirar?\n");
                fgets(str, 3, stdin);
                col = atoi(str);
                while(col > NCOLS || col <= 0 || node->tauler[0][col-1] != ' ') {
                    fflush(stdin);
                    printf("Resposta errònia. Respon amb un número enter entre 1 i 8\n");
                    fgets(str, 3, stdin);
                    col = atoi(str);
                }
                ferTirada(node, col-1, k);
            }
        }
        else if(k % 2 == 1) {
            if(k == 1) {
                col2 = rand() % 4 + 3;
                printf("\nHa començat tirant l'ordinador a la columna %d\n", col2);
                ferTirada(node, col2-1, k);
            }
            else {
                crearArbreRec(node, 1, prof);
                minimax(node, 0, 0);
                for(int i=0; i<node->n_fills; i++) {
                    destrueixArbreRec(node->fills[i]);
                }
            }
        }
        node->n_fills = numFills(node);
        printaTauler(node);
        if(checkWin(node) == 1) break;
    }
}

void info(void){
    printf("\n\t\x1b[33;40mBENVINGUT A LA SECCIÓ D'INFORMACIÓ DEL JOC DEL CONECTA 4\n\033[0m\n");
    printf("El joc disposa de set variants diferents:\n\n");
    printf("\t\x1b[36;40mDos jugadors\033[0m. Vols jugar amb algun amic per practicar abans d'enfrentar-te a la poderosa màquina? Aquesta és la oportunitat d'entrenar-te. Desafia algú i guanya'l!\n\t\x1b[36;40mNormal\033[0m. Aquest és el mode més senzill, més bàsic. Només tu i la màquina. Un cara a cara. Qui guanyarà?\n\t\x1b[36;40mRota el tauler!\033[0m Aquest mode introdueix rotacions al tauler. Pots seleccionar tant l'oportunitat de fer-les tu al començament de cada torn com deixar que apareguin de forma aleatòria al començament del teu torn amb probabilitat 0.5. Dóna igual quin mode agafis, acabaràs perdent igualment.\n\t\x1b[36;40mZero gravity \033[0m Vols viatjar a l'Estació Espacial Internacional per jugar al conecta 4 però no t'ho pots permetre? Sigues el primer en experimentar la gravetat zero amb aquest mode abans que algú se t'adelanti!\n\t\x1b[36;40mContrarrellotge \033[0m No en tens prou amb dificultat extrema? Doncs intenta guanyar la màquina amb límit de temps! I per si encara no en tens prou, pots afegir-hi gravetat zero!\n\t\x1b[36;40mTetris \033[0m Quan s'omple l'última fila del tauler, desapareix. No és el tetris en si, però si que conserva la essència\n\t\x1b[36;40mPermuta i guanya! \033[0m De forma aleatòria amb probabilitat 0.5 podràs permutar dues columnes i a més podràs fer la teva tirada. Potser és la única manera que tens de guanyar l'ordinador...\033[0m\n\n\x1b[33;40mATENCIÓ\033[0m: Les fitxes s'imprimiran en diferents colors per facilitar el joc, i quan algú guanyi s'imprimirà un nou tauler amb el 4 en ratlla guanyador ben diferenciat de la resta del tauler.\n");
}


int main() {
    char str[2], str2[2], mode[3], dif[3];
    
    do {
        printf("\n\t\t\x1b[33;40mBENVINGUT AL JOC DEL CONECTA 4\n\n\033[0mEl joc disposa de set variants diferents i tres nivells de dificultat\n");
        printf("Un cop escollit el mode hauràs de triar el nivell de dificultat.\nT'atreviràs amb el més difícil...?\n\n");
        printf("A quin mode vols jugar? Per \x1b[36;40minformació \033[0mprémer -> \x1b[33;40m-1\n");
        printf("\t\x1b[36;40mDos jugadors \033[0m-> prémer \x1b[33;40m1\n\t\x1b[36;40mNormal \033[0m-> prémer \x1b[33;40m2\n\t\x1b[36;40mRota el tauler! \033[0m-> prémer \x1b[33;40m3\n\t\x1b[36;40mZero gravity \033[0m-> prémer \x1b[33;40m4\n\t\x1b[36;40mContrarrellotge \033[0m-> prémer \x1b[33;40m5\n\t\x1b[36;40mTetris \033[0m-> prémer \x1b[33;40m6\n\t\x1b[36;40mPermuta i guanya! \033[0m-> prémer \x1b[33;40m7\033[0m\n");
        fflush(stdin);
        fgets(mode, 3, stdin);
        if(atoi(mode) == -1) {
            info();
        }
        while(atoi(mode) != 1 && atoi(mode) != 2 && atoi(mode) != 3 && atoi(mode) != 4 && atoi(mode) != 5 && atoi(mode) != 6 && atoi(mode) != 7 && atoi(mode) != 8) {
            printf("\nNo has introduit un número vàlid. Recorda que els set modes de joc són:\n");
            printf("\t\x1b[36;40mDos jugadors \033[0m-> prémer \x1b[33;40m1\n\t\x1b[36;40mNormal \033[0m-> prémer \x1b[33;40m2\n\t\x1b[36;40mRota el tauler! \033[0m-> prémer \x1b[33;40m3\n\t\x1b[36;40mZero gravity \033[0m-> prémer \x1b[33;40m4\n\t\x1b[36;40mContrarrellotge \033[0m-> prémer \x1b[33;40m5\n\t\x1b[36;40mTetris \033[0m-> prémer \x1b[33;40m6\n\t\x1b[36;40mPermuta i guanya! \033[0m-> prémer \x1b[33;40m7\033[0m\n");
            fflush(stdin);
            fgets(mode, 3, stdin);
        }
        
        if(atoi(mode) != 1) {
            printf("\n\033[0mQuina vols que sigui la dificultat de la màquina?\n");
            printf("\t\x1b[36;40mFàcil \033[0m-> prémer \x1b[33;40m1\n\t\x1b[36;40mMitjana \033[0m-> prémer \x1b[33;40m2\n\t\x1b[36;40mDifícil \033[0m-> prémer \x1b[33;40m3\033[0m\n");
            fflush(stdin);
            fgets(dif, 3, stdin);
            while(atoi(dif) != 1 && atoi(dif) != 2 && atoi(dif) != 3) {
                printf("\nNo has introduit un número vàlid. Recorda que els tres nivells de dificultat són:\n");
                printf("\t\x1b[36;40mFàcil \033[0m-> prémer \x1b[33;40m1\n\t\x1b[36;40mMitjana \033[0m-> prémer \x1b[33;40m2\n\t\x1b[36;40mDifícil \033[0m-> prémer \x1b[33;40m3\033[0m\n");
                fflush(stdin);
                fgets(dif, 3, stdin);
            }
        }
    
        if(atoi(mode) == 1) {
            do {
                printf("\n");
                srand(time(0));
                Node *arrel = malloc(sizeof(Node));
                initTauler(arrel);
                arrel->n_fills = numFills(arrel);
                arrel->fills = malloc(arrel->n_fills * sizeof(Node *));
                arrel->valor = heuristic(arrel);
                
                dosJugadors(arrel);
                free(arrel);
                printf("Vols seguir jugant? Respon amb y/n\n");
                fflush(stdin);
                fgets(str, 2, stdin);
                while(strcmp(str, "y") != 0 && strcmp(str, "n") != 0) {
                    printf("Resposta errònia. Respon amb y/n\n");
                    fflush(stdin);
                    fgets(str, 2, stdin);
                }
            } while(strcmp(str, "y") == 0);
        }
        if(atoi(mode) == 2) {
            do {
                srand(time(0));
                Node *arrel = malloc(sizeof(Node));
                initTauler(arrel);
                arrel->n_fills = numFills(arrel);
                arrel->fills = malloc(arrel->n_fills * sizeof(Node *));
                arrel->valor = heuristic(arrel);
                
                jugadorAleatori(arrel, atoi(dif) * 2);
                free(arrel);
                printf("Vols seguir jugant? Respon amb y/n\n");
                fflush(stdin);
                fgets(str, 2, stdin);
                while(strcmp(str, "y") != 0 && strcmp(str, "n") != 0) {
                    printf("Resposta errònia. Respon amb y/n\n");
                    fflush(stdin);
                    fgets(str, 2, stdin);
                }
            } while(strcmp(str, "y") == 0);
        }
        if(atoi(mode) == 3) {
            do {
                srand(time(0));
                Node *arrel = malloc(sizeof(Node));
                initTauler(arrel);
                arrel->n_fills = numFills(arrel);
                arrel->fills = malloc(arrel->n_fills * sizeof(Node *));
                arrel->valor = heuristic(arrel);
                
                fflush(stdin);
                printf("\nA quina subvariant vols jugar?\n");
                printf("\t\x1b[36;40mRota el tauler! \033[0m-> prémer \x1b[33;40m1\n\t\x1b[36;40mQuan rotarà el tauler? \033[0m-> prémer \x1b[33;40m2\033[0m\n");
                fgets(mode, 3, stdin);
                while(atoi(mode) != 1 && atoi(mode) != 2) {
                    printf("\nNo has introduit un número vàlid. Recorda que els dos submodes de joc són:\n");
                    printf("\t\x1b[36;40mRota el tauler! \033[0m-> prémer \x1b[33;40m1\n\t\x1b[36;40mQuan rotarà el tauler? \033[0m-> prémer \x1b[33;40m2\033[0m\n");
                    fflush(stdin);
                    fgets(mode, 3, stdin);
                }
                if(atoi(mode) == 1) jugadorRotacio(arrel, atoi(dif) * 2);
                if(atoi(mode) == 2) jugadorRotacioRandom(arrel, atoi(dif) * 2);
                free(arrel);
                printf("Vols seguir jugant? Respon amb y/n\n");
                fflush(stdin);
                fgets(str, 2, stdin);
                while(strcmp(str, "y") != 0 && strcmp(str, "n") != 0) {
                    printf("Resposta errònia. Respon amb y/n\n");
                    fflush(stdin);
                    fgets(str, 2, stdin);
                }
            } while(strcmp(str, "y") == 0);
        }
        if(atoi(mode) == 4) {
            do {
                srand(time(0));
                Node *arrel = malloc(sizeof(Node));
                initTauler(arrel);
                arrel->n_fills = numFills(arrel);
                arrel->fills = malloc(arrel->n_fills * sizeof(Node *));
                arrel->valor = heuristic(arrel);
                
                fflush(stdin);
                printf("\nA quina subvariant vols jugar?\n");
                printf("\t\x1b[36;40mZero gravity \033[0m-> prémer \x1b[33;40m1\n\t\x1b[36;40mRandom zero gravity \033[0m-> prémer \x1b[33;40m2\033[0m\n");
                fgets(mode, 3, stdin);
                while(atoi(mode) != 1 && atoi(mode) != 2) {
                    printf("\nNo has introduit un número vàlid. Recorda que els dos submodes de joc són:\n");
                    printf("\t\x1b[36;40mZero gravity \033[0m-> prémer \x1b[33;40m1\n\t\x1b[36;40mRandom zero gravity \033[0m-> prémer \x1b[33;40m2\033[0m\n");
                    fflush(stdin);
                    fgets(mode, 3, stdin);
                }
                if(atoi(mode) == 1) antiGravetat(arrel, atoi(dif) * 2);
                if(atoi(mode) == 2) antiGravetatRandom(arrel, atoi(dif) * 2);
                free(arrel);
                printf("Vols seguir jugant? Respon amb y/n\n");
                fflush(stdin);
                fgets(str, 2, stdin);
                while(strcmp(str, "y") != 0 && strcmp(str, "n") != 0) {
                    printf("Resposta errònia. Respon amb y/n\n");
                    fflush(stdin);
                    fgets(str, 2, stdin);
                }
            } while(strcmp(str, "y") == 0);
        }
        if(atoi(mode) == 5) {
            do {
                printf("\n\x1b[33;40mATENCIÓ\033[0m: Has escollit el mode \x1b[36;40mcontrarrellotge \033[0m\n");
                printf("Si s'acaba el teu temps, el programa sortirà\n");
                printf("Si vols tornar a jugar o canviar de mode, torna a executar el programa\n");
                printf("Bona sort, la necesitaràs...\n");
                srand(time(0));
                Node *arrel = malloc(sizeof(Node));
                initTauler(arrel);
                arrel->n_fills = numFills(arrel);
                arrel->fills = malloc(arrel->n_fills * sizeof(Node *));
                arrel->valor = heuristic(arrel);
                
                fflush(stdin);
                printf("\nA quina subvariant vols jugar?\n");
                printf("\t\x1b[36;40mContrarrellotge \033[0m-> prémer \x1b[33;40m1\n\t\x1b[36;40mRandom zero gravity\033[0m-> prémer \x1b[33;40m3\033[0m\n");
                fgets(mode, 3, stdin);
                while(atoi(mode) != 1 && atoi(mode) != 2) {
                    printf("\nNo has introduit un número vàlid. Recorda que els dos submodes de joc són:\n");
                    printf("\t\x1b[36;40mContrarrellotge \033[0m-> prémer \x1b[33;40m1\n\t\x1b[36;40mRandom zero gravity\033[0m-> prémer \x1b[33;40m3\033[0m\n");
                    fflush(stdin);
                    fgets(mode, 3, stdin);
                }
                if(atoi(mode) == 1) contraRellotge(arrel, atoi(dif) * 2);
                if(atoi(mode) == 2) contraRellotgeRandom(arrel, atoi(dif) * 2);
                free(arrel);
                printf("Vols seguir jugant? Respon amb y/n\n");
                fflush(stdin);
                fgets(str, 2, stdin);
                while(strcmp(str, "y") != 0 && strcmp(str, "n") != 0) {
                    printf("Resposta errònia. Respon amb y/n\n");
                    fflush(stdin);
                    fgets(str, 2, stdin);
                }
            } while(strcmp(str, "y") == 0);
        }
        if(atoi(mode) == 6) {
            do {
                srand(time(0));
                Node *arrel = malloc(sizeof(Node));
                initTauler(arrel);
                arrel->n_fills = numFills(arrel);
                arrel->fills = malloc(arrel->n_fills * sizeof(Node *));
                arrel->valor = heuristic(arrel);
                
                tetris(arrel, atoi(dif) * 2);
                free(arrel);
                printf("Vols seguir jugant? Respon amb y/n\n");
                fflush(stdin);
                fgets(str, 2, stdin);
                while(strcmp(str, "y") != 0 && strcmp(str, "n") != 0) {
                    printf("Resposta errònia. Respon amb y/n\n");
                    fflush(stdin);
                    fgets(str, 2, stdin);
                }
            } while(strcmp(str, "y") == 0);
        }
        if(atoi(mode) == 7) {
            do {
                srand(time(0));
                Node *arrel = malloc(sizeof(Node));
                initTauler(arrel);
                arrel->n_fills = numFills(arrel);
                arrel->fills = malloc(arrel->n_fills * sizeof(Node *));
                arrel->valor = heuristic(arrel);
                
                permutaColumnes(arrel, atoi(dif) * 2);
                free(arrel);
                printf("Vols seguir jugant? Respon amb y/n\n");
                fflush(stdin);
                fgets(str, 2, stdin);
                while(strcmp(str, "y") != 0 && strcmp(str, "n") != 0) {
                    printf("Resposta errònia. Respon amb y/n\n");
                    fflush(stdin);
                    fgets(str, 2, stdin);
                }
            } while(strcmp(str, "y") == 0);
        }
        printf("Vols tornar al menú principal per canviar de variant del joc? Respon amb y/n\n");
        fflush(stdin);
        fgets(str2, 2, stdin);
        while(strcmp(str2, "y") != 0 && strcmp(str2, "n") != 0) {
            printf("Resposta errònia. Respon amb y/n\n");
            fflush(stdin);
            fgets(str2, 2, stdin);
        }
    } while(strcmp(str2, "y") == 0);

    return 0;
}
