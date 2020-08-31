#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include <SDL/SDL.h>

int initialiser();
void afficher();
int deplacer();
/*
signature de la fonction collision.
*/
int collision(SDL_Rect p1, SDL_Rect p2);

void freememory();



#endif // FONCTIONS_H_INCLUDED
