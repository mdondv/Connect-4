#ifndef heuristic_h
#define heuristic_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

double tresEspais(struct node *node);
double lookForFour(struct node *node);
double lookForFive(struct node *node);
double lookForThree(struct node *node);
double lookForTwo(struct node *node);
double heuristic(struct node *node);
double tresEspaisAntiGravetat(struct node *node);
double lookForFourAntiGravetat(struct node *node);
double lookForFiveAntiGravetat(struct node *node);
double lookForThreeAntiGravetat(struct node *node);
double lookForTwoAntiGravetat(struct node *node);
double heuristicAntiGravetat(struct node *node);

#endif /* heuristic_h */


