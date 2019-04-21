#include "proto.h"

///Deplacement ennemis
void deplacementEnnemi(t_listeActeurs* ancre)
{
    int i;
    for(i=1;i<ancre->maxiActeur;i++)
    {
        if(ancre->tabActeur[i]!=NULL)
        {
            t_acteur* ennemi=ancre->tabActeur[i];

            ennemi->posx -= ennemi->depx;
        }
    }
}
