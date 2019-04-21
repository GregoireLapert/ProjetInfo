#include "proto.h"

int PopEnnemis(t_listeActeurs* ancre, int place)
{
    int creerE1,creerE2,creerE3;
    int yes;

    if(ancre->tabActeur[place]!=NULL)
        yes=0;
    else
    {
        creerE1=rand()%90;
        creerE2=rand()%90;
        creerE3=rand()%200;
        if(creerE1==1)
            ancre->tabActeur[place]=constructeurActeur(800,rand()%500,2);
        if(creerE2==1)
            ancre->tabActeur[place]=constructeurActeur(800,rand()%500,3);
        if(creerE3==1)
            ancre->tabActeur[place]=constructeurActeur(800,480,4);
        yes=1;
    }
    return yes;
}

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

            if(ennemi->type==2)
            {
                if(ennemi->posx%200>100)
                    ennemi->posy += ennemi->depy;
                else ennemi->posy -= ennemi->depy;
            }
        }
    }
}
