#ifndef printaTauler_h
#define printaTauler_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void copiaTauler(struct node *fill, struct node *pare);
void printaTauler(struct node *arrel);
void printaGoldVert(struct node *arrel, int l, int m);
void printaGoldHorit(struct node *arrel, int l, int m);
void printaGoldObl45(struct node *arrel, int l, int m);
void printaGoldObl135(struct node *arrel, int l, int m);
void initTauler(struct node *pare);
void rotacio(Node *node);
void canviaGravetat(Node *node, int mode);
void canviaColumnes(Node *node, int l, int m);

#endif /* printaTauler_h */
