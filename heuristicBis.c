#include "minimaxBis.h"
#include "heuristicBis.h"
#include "printaTauler.h"
#include "modesJoc.h"

double tresEspais(Node *node) {
    double valor = 0;
    int contX = 0, contO = 0;
    for(int i=NFILES-1; i>=0; i--) {
        for(int j=1; j<NCOLS-2; j++){
            for(int k=0; k<2; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i][j+k]) contX += 1;
                if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i][j+k]) contO += 1;
            }
            if(contX == 2 && node->tauler[i][j-1] == ' ' && node->tauler[i][j+2] == ' ') {
                if(i<NFILES-1 && (node->tauler[i+1][j-1] != ' ' && node->tauler[i+1][j+2] != ' ')) valor -= 2e2;
                else if(i == NFILES-1) valor -= 2e2;
            }
            if(contO == 2 && node->tauler[i][j-1] == ' ' && node->tauler[i][j+2] == ' ') {
                if(i<NFILES-1 && (node->tauler[i+1][j-1] != ' ' && node->tauler[i+1][j+2] != ' ')) valor += 1e2;
                else if(i == NFILES-1) valor += 1e2;
            }
            contX = 0, contO = 0;
        }
    }
    for(int i=NFILES-1; i>=0; i--) {
        for(int j=1; j<NCOLS-3; j++){
            for(int k=0; k<3; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i][j+k]) contX += 1;
                if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i][j+k]) contO += 1;
            }
            if(contX == 3 && node->tauler[i][j-1] == ' ' && node->tauler[i][j+3] == ' ') {
                if(i<NFILES-1 && (node->tauler[i+1][j-1] != ' ' && node->tauler[i+1][j+3] != ' ')) valor -= 2e6;
                else if(i == NFILES-1 && (node->tauler[i][j-1] == ' ' && node->tauler[i][j+3] == ' ')) valor -= 2e6;
            }
            if(contO == 3 && node->tauler[i][j-1] == ' ' && node->tauler[i][j+3] == ' ') {
                if(i<NFILES-1 && (node->tauler[i+1][j-1] != ' ' && node->tauler[i+1][j+3] != ' ')) valor += 1e5;
                else if(i == NFILES-1 && (node->tauler[i][j-1] == ' ' && node->tauler[i][j+3] == ' ')) valor += 1e5;
            }
            contX = 0, contO = 0;
        }
    }
    return valor;
}

double tresEspaisAntiGravetat(Node *node) {
    double valor = 0;
    int contX = 0, contO = 0;
    for(int i=0; i<NFILES; i++) {
        for(int j=1; j<NCOLS-2; j++){
            for(int k=0; k<2; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i][j+k]) contX += 1;
                if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i][j+k]) contO += 1;
            }
            if(contX == 2 && node->tauler[i][j-1] == ' ' && node->tauler[i][j+2] == ' ') {
                if(i<NFILES-1 && (node->tauler[i-1][j-1] != ' ' && node->tauler[i-1][j+2] != ' ')) valor -= 2e2;
                else if(i == NFILES-1) valor -= 2e2;
            }
            if(contO == 2 && node->tauler[i][j-1] == ' ' && node->tauler[i][j+2] == ' ') {
                if(i<NFILES-1 && (node->tauler[i-1][j-1] != ' ' && node->tauler[i-1][j+2] != ' ')) valor += 1e2;
                else if(i == NFILES-1) valor += 1e2;
            }
            contX = 0, contO = 0;
        }
    }
    for(int i=0; i<NFILES; i++) {
        for(int j=1; j<NCOLS-3; j++){
            for(int k=0; k<3; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i][j+k]) contX += 1;
                if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i][j+k]) contO += 1;
            }
            if(contX == 3 && node->tauler[i][j-1] == ' ' && node->tauler[i][j+3] == ' ') {
                if(i<NFILES-1 && (node->tauler[i-1][j-1] != ' ' && node->tauler[i-1][j+3] != ' ')) valor -= 2e6;
                else if(i == NFILES-1 && (node->tauler[i][j-1] == ' ' && node->tauler[i][j+3] == ' ')) valor -= 2e6;
            }
            if(contO == 3 && node->tauler[i][j-1] == ' ' && node->tauler[i][j+3] == ' ') {
                if(i<NFILES-1 && (node->tauler[i-1][j-1] != ' ' && node->tauler[i-1][j+3] != ' ')) valor += 1e5;
                else if(i == NFILES-1 && (node->tauler[i][j-1] == ' ' && node->tauler[i][j+3] == ' ')) valor += 1e5;
            }
            contX = 0, contO = 0;
        }
    }
    return valor;
}

double lookForFour(Node *node) {
    
    double valor = 0;
    int contX = 0, contO = 0;
    for(int j=0; j<NCOLS; j++) {
        for(int i=NFILES-1; i>=3; i--){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i-k][j]) contX += 1;
                if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i-k][j]) contO += 1;
            }
            if(contX == 4)  return valor -= 2e6;
            if(contO == 4)  return valor += 1e6;
            contX = 0, contO = 0;
        }
    }
    for(int i=NFILES-1; i>=0; i--) {
        for(int j=0; j<NCOLS-3; j++){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i][j+k]) contX += 1;
                if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i][j+k]) contO += 1;
            }
            if(contX == 4) return valor -= 2e6;
            if(contO == 4) return valor += 1e6;
            contX = 0, contO = 0;
        }
    }
    for(int j=0; j<NCOLS-3; j++){//135 grados
        for(int i=NFILES-4; i>=0; i--){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i+k][j+k]) contX += 1;
                if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i+k][j+k]) contO += 1;
            }
            if(contX == 4) return valor -= 2e6;
            if(contO == 4) return valor += 1e6;
            contX = 0, contO = 0;
        }
    }
    for(int j=0; j<NCOLS-3; j++){//45 grados
        for(int i=NFILES-1; i>=3; i--){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i-k][j+k]) contX += 1;
                if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i-k][j+k]) contO += 1;
            }
            if(contX == 4) return valor -= 2e6;
            if(contO == 4) return valor += 1e6;
            contX = 0, contO = 0;
        }
    }
    return valor;
}

double lookForFourAntiGravetat(Node *node) {
    
    double valor = 0;
    int contX = 0, contO = 0;
    for(int j=0; j<NCOLS; j++) {
        for(int i=0; i<NFILES-3; i++){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i+k][j]) contX += 1;
                if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i+k][j]) contO += 1;
            }
            if(contX == 4)  return valor -= 2e6;
            if(contO == 4)  return valor += 1e6;
            contX = 0, contO = 0;
        }
    }
    for(int i=NFILES-1; i>=0; i--) {
        for(int j=0; j<NCOLS-3; j++){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i][j+k]) contX += 1;
                if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i][j+k]) contO += 1;
            }
            if(contX == 4) return valor -= 2e6;
            if(contO == 4) return valor += 1e6;
            contX = 0, contO = 0;
        }
    }
    for(int j=0; j<NCOLS-3; j++){//135 grados
        for(int i=NFILES-4; i>=0; i--){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i+k][j+k]) contX += 1;
                if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i+k][j+k]) contO += 1;
            }
            if(contX == 4) return valor -= 2e6;
            if(contO == 4) return valor += 1e6;
            contX = 0, contO = 0;
        }
    }
    for(int j=0; j<NCOLS-3; j++){//45 grados
        for(int i=NFILES-1; i>=3; i--){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i-k][j+k]) contX += 1;
                if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i-k][j+k]) contO += 1;
            }
            if(contX == 4) return valor -= 2e6;
            if(contO == 4) return valor += 1e6;
            contX = 0, contO = 0;
        }
    }
    return valor;
}

double lookForThree(Node *node) {
    
    double valor = 0;
    int contX = 0, contO = 0;
    for(int j=0; j<NCOLS; j++) {
        for(int i=NFILES-1; i>=3; i--){//vertical
            for(int k=0; k<3; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i-k][j]) contX += 1;
                if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i-k][j]) contO += 1;
            }
            if(contX == 3 && node->tauler[i-3][j] == ' ')  valor -= 2e4;
            if(contO == 3 && node->tauler[i-3][j] == ' ')  valor += 1e4;
            contX = 0, contO = 0;
        }
        if(node->tauler[2][j] == ' ' && node->tauler[2][j] == node->tauler[1][j] && node->tauler[2][j] == node->tauler[0][j]) valor -= 1e2;
    }
    int contBlank = 0;
    for(int i=NFILES-1; i>=0; i--) {//horitzonal
        for(int j=0; j<NCOLS-3; j++){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j+k] == 'X') contX += 1;
                if(node->tauler[i][j+k] == 'O') contO += 1;
                if(node->tauler[i][j+k] == ' ' && ((node->tauler[i+1][j+k] != ' ' && i<NFILES-1) || i == NFILES-1)) contBlank += 1;
            }
            if(contX == 3 && contBlank == 1) valor -= 2e4;
            if(contO == 3 && contBlank == 1) valor += 1e4;
            contX = 0, contO = 0, contBlank = 0;
        }
    }
    for(int j=0; j<NCOLS-3; j++){//135 graus
        for(int i=NFILES-4; i>=0; i--){
            for(int k=0; k<4; k++) {
                if(node->tauler[i+k][j+k] == 'X') contX += 1;
                if(node->tauler[i+k][j+k] == 'O') contO += 1;
                if(node->tauler[i+k][j+k] == ' ' && ((node->tauler[i+k+1][j+k] != ' ' && i<NFILES-1) || i == NFILES-1)) contBlank += 1;
            }
            if(contX == 3 && contBlank == 1) valor -= 2e4;
            if(contO == 3 && contBlank == 1) valor += 1e4;
            contX = 0, contO = 0, contBlank = 0;
        }
    }
    for(int j=0; j<NCOLS-3; j++){
        for(int i=NFILES-1; i>=3; i--){
            for(int k=0; k<4; k++) {
                if(node->tauler[i-k][j+k] == 'X') contX += 1;
                if(node->tauler[i-k][j+k] == 'O') contO += 1;
                if(node->tauler[i-k][j+k] == ' ' && ((node->tauler[i-k+1][j+k] != ' ' && i<NFILES-1) || i == NFILES-1)) contBlank += 1;
            }
            if(contX == 3 && contBlank == 1) valor -= 2e4;
            if(contO == 3 && contBlank == 1) valor += 1e4;
            contX = 0, contO = 0, contBlank = 0;
        }
    }
    return valor;
}

double lookForThreeAntiGravetat(Node *node) {
    
    double valor = 0;
    int contX = 0, contO = 0;
    for(int j=0; j<NCOLS; j++) {
        for(int i=0; i<NFILES-2; i++){//vertical
            for(int k=0; k<3; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i+k][j]) contX += 1;
                if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i+k][j]) contO += 1;
            }
            if(contX == 3 && node->tauler[i+3][j] == ' ')  valor -= 2e4;
            if(contO == 3 && node->tauler[i+3][j] == ' ')  valor += 1e4;
            contX = 0, contO = 0;
        }
        if(node->tauler[NFILES-3][j] == ' ' && node->tauler[NFILES-3][j] == node->tauler[NFILES-2][j] && node->tauler[NFILES-3][j] == node->tauler[NFILES-1][j]) valor -= 1e2;//si només queden 3 caselles no tiris allà, no aconseguiràs fer 4 en ratlla vertical
    }
    int contBlank = 0;
    for(int i=0; i<NFILES-2; i++){//horitzontal
        for(int j=0; j<NCOLS-3; j++){
            for(int k=0; k<4; k++) {
                if(node->tauler[i][j+k] == 'X') contX += 1;
                if(node->tauler[i][j+k] == 'O') contO += 1;
                if(node->tauler[i][j+k] == ' ' && ((node->tauler[i-1][j+k] != ' ' && i<NFILES-1) || i == 0)) contBlank += 1;
            }
            if(contX == 3 && contBlank == 1) valor -= 2e4;
            if(contO == 3 && contBlank == 1) valor += 1e4;
            contX = 0, contO = 0, contBlank = 0;
        }
    }
    for(int j=0; j<NCOLS-3; j++){//135 graus
        for(int i=NFILES-4; i>=0; i--){
            for(int k=0; k<4; k++) {
                if(node->tauler[i+k][j+k] == 'X') contX += 1;
                if(node->tauler[i+k][j+k] == 'O') contO += 1;
                if(node->tauler[i+k][j+k] == ' ' && ((node->tauler[i+k-1][j+k] != ' ' && i<NFILES-1) || i == 0)) contBlank += 1;
            }
            if(contX == 3 && contBlank == 1) valor -= 2e4;
            if(contO == 3 && contBlank == 1) valor += 1e4;
            contX = 0, contO = 0, contBlank = 0;
        }
    }
    for(int j=0; j<NCOLS-3; j++){//45 graus
        for(int i=NFILES-1; i>=3; i--){
            for(int k=0; k<4; k++) {
                if(node->tauler[i-k][j+k] == 'X') contX += 1;
                if(node->tauler[i-k][j+k] == 'O') contO += 1;
                if(node->tauler[i-k][j+k] == ' ' && ((node->tauler[i-k-1][j+k] != ' ' && i<NFILES-1) || i == 0)) contBlank += 1;
            }
            if(contX == 3 && contBlank == 1) valor -= 2e4;
            if(contO == 3 && contBlank == 1) valor += 1e4;
            contX = 0, contO = 0, contBlank = 0;
        }
    }
    return valor;
}

double lookForTwo(Node *node) {
    
    double valor = 0;
    int contX = 0, contO = 0;
    for(int j=0; j<NCOLS; j++) {
        for(int i=NFILES-1; i>=3; i--){//vertical
            for(int k=0; k<2; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i-k][j]) contX += 1;
                if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i-k][j]) contO += 1;
            }
            if(contX == 2 && node->tauler[i-2][j] == ' ')  valor -= 2e2;
            if(contO == 2 && node->tauler[i-2][j] == ' ')  valor += 1e2;
            contX = 0, contO = 0;
        }
        if(node->tauler[2][j] == ' ' && node->tauler[2][j] == node->tauler[1][j] && node->tauler[2][j] == node->tauler[0][j]) valor -= 1e2;
    }
    int contBlank = 0;
    for(int i=NFILES-1; i>=0; i--) {//horitzonal
        for(int j=0; j<NCOLS-3; j++){
            for(int k=0; k<3; k++) {
                if(node->tauler[i][j+k] == 'X') contX += 1;
                if(node->tauler[i][j+k] == 'O') contO += 1;
                if(node->tauler[i][j+k] == ' ' && ((node->tauler[i+1][j+k] != ' ' && i<NFILES-1) || i == NFILES-1)) contBlank += 1;
            }
            if(contX == 2 && contBlank == 1) valor -= 2e2;
            if(contO == 2 && contBlank == 1) valor += 1e2;
            contX = 0, contO = 0, contBlank = 0;
        }
    }
    for(int j=0; j<NCOLS-3; j++){//135 graus
        for(int i=NFILES-4; i>=0; i--){
            for(int k=0; k<3; k++) {
                if(node->tauler[i+k][j+k] == 'X') contX += 1;
                if(node->tauler[i+k][j+k] == 'O') contO += 1;
                if(node->tauler[i+k][j+k] == ' ' && ((node->tauler[i+k+1][j+k] != ' ' && i<NFILES-1) || i == NFILES-1)) contBlank += 1;
            }
            if(contX == 2 && contBlank == 1) valor -= 2e2;
            if(contO == 2 && contBlank == 1) valor += 1e2;
            contX = 0, contO = 0, contBlank = 0;
        }
    }
    for(int j=0; j<NCOLS-3; j++){//45 graus
        for(int i=NFILES-1; i>=3; i--){
            for(int k=0; k<3; k++) {
                if(node->tauler[i-k][j+k] == 'X') contX += 1;
                if(node->tauler[i-k][j+k] == 'O') contO += 1;
                if(node->tauler[i-k][j+k] == ' ' && ((node->tauler[i-k+1][j+k] != ' ' && i<NFILES-1) || i == NFILES-1)) contBlank += 1;
            }
            if(contX == 2 && contBlank == 1) valor -= 2e2;
            if(contO == 2 && contBlank == 1) valor += 1e2;
            contX = 0, contO = 0, contBlank = 0;
        }
    }
    return valor;
}

double lookForTwoAntiGravetat(Node *node) {
    
    double valor = 0;
    int contX = 0, contO = 0;
    for(int j=0; j<NCOLS; j++) {
        for(int i=NFILES-1; i>=3; i--){//vertical
            for(int k=0; k<2; k++) {
                if(node->tauler[i][j] == 'X' && node->tauler[i][j] == node->tauler[i+k][j]) contX += 1;
                if(node->tauler[i][j] == 'O' && node->tauler[i][j] == node->tauler[i+k][j]) contO += 1;
            }
            if(contX == 2 && node->tauler[i+2][j] == ' ')  valor -= 2e2;
            if(contO == 2 && node->tauler[i+2][j] == ' ')  valor += 1e2;
            contX = 0, contO = 0;
        }
        if(node->tauler[NFILES-3][j] == ' ' && node->tauler[NFILES-3][j] == node->tauler[NFILES-2][j] && node->tauler[NFILES-3][j] == node->tauler[NFILES-1][j]) valor -= 1e2;
    }
    int contBlank = 0;
    for(int i=NFILES-1; i>=3; i--){//horitzontal
        for(int j=0; j<NCOLS-3; j++){
            for(int k=0; k<3; k++) {
                if(node->tauler[i][j+k] == 'X') contX += 1;
                if(node->tauler[i][j+k] == 'O') contO += 1;
                if(node->tauler[i][j+k] == ' ' && ((node->tauler[i-1][j+k] != ' ' && i<NFILES-1) || i == 0)) contBlank += 1;
            }
            if(contX == 2 && contBlank == 1) valor -= 2e2;
            if(contO == 2 && contBlank == 1) valor += 1e2;
            contX = 0, contO = 0, contBlank = 0;
        }
    }
    for(int j=0; j<NCOLS-3; j++){//135 graus
        for(int i=NFILES-4; i>=0; i--){
            for(int k=0; k<3; k++) {
                if(node->tauler[i+k][j+k] == 'X') contX += 1;
                if(node->tauler[i+k][j+k] == 'O') contO += 1;
                if(node->tauler[i+k][j+k] == ' ' && ((node->tauler[i+k-1][j+k] != ' ' && i<NFILES-1) || i == 0)) contBlank += 1;
            }
            if(contX == 2 && contBlank == 1) valor -= 2e2;
            if(contO == 2 && contBlank == 1) valor += 1e2;
            contX = 0, contO = 0, contBlank = 0;
        }
    }
    for(int j=0; j<NCOLS-3; j++){
        for(int i=NFILES-1; i>=3; i--){
            for(int k=0; k<3; k++) {
                if(node->tauler[i-k][j+k] == 'X') contX += 1;
                if(node->tauler[i-k][j+k] == 'O') contO += 1;
                if(node->tauler[i-k][j+k] == ' ' && ((node->tauler[i-k-1][j+k] != ' ' && i<NFILES-1) || i == 0)) contBlank += 1;
            }
            if(contX == 2 && contBlank == 1) valor -= 2e2;
            if(contO == 2 && contBlank == 1) valor += 1e2;
            contX = 0, contO = 0, contBlank = 0;
        }
    }
    return valor;
}

double heuristic(Node *node) {
    double valor = 0;
    valor = tresEspais(node) + lookForFour(node) + lookForThree(node) + lookForTwo(node);
    return valor;
}

double heuristicAntiGravetat(Node *node) {
    double valor = 0;
    valor = tresEspaisAntiGravetat(node) + lookForFourAntiGravetat(node) + lookForThreeAntiGravetat(node) + lookForTwoAntiGravetat(node);
    return valor;
}
