#ifndef minimax_h
#define minimax_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define NFILES 8
#define NCOLS 8

typedef struct node {
    char tauler[NFILES][NCOLS];
    struct node* *fills;
    int n_fills;
    double valor;
} Node;

int numFills(struct node *pare);
int numFillsAntiGrav(struct node *pare);
void ferTirada(struct node *fill, int numDeFill, int nivell);
void ferTiradaAntiGrav(Node *fill, int numDeFill, int nivell);
struct node *crearNode(struct node *pare, int numDeFill, int nivell, int prof);
struct node *crearNodeAntiGrav(Node *pare, int numDeFill, int nivell, int prof);
void crearNivell(struct node *pare, int nivell, int prof);
void crearNivellAntiGrav(struct node *pare, int nivell, int prof);
void crearArbreRec(struct node *arrel, int nivell, int prof);
void crearArbreRecAntiGrav(struct node *arrel, int nivell, int prof);
void minimax(struct node *arrel, int nivell, int mode);
void destrueixArbreRec(struct node *node);
int checkWin(struct node *node);
int checkWinBis(struct node *node);

#endif /* minimax_h */
