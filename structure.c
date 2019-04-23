#include "proto.h"

///Cree une liste : initialisation des elements du jeu.
t_listeActeurs* creerListe(int maxi)
{
    int i=0;
    t_listeActeurs* nouveau=(t_listeActeurs*)malloc(sizeof(t_listeActeurs));
    nouveau->maxiActeur=10;
    nouveau->maxiInter=maxi;
    nouveau->nActeur=0;
    nouveau->nInter=0;
    nouveau->tabActeur=(t_acteur**)malloc(maxi*sizeof(t_acteur*));
    nouveau->tabInter=(t_intervenant**)malloc(maxi*sizeof(t_intervenant*));

    for(i=0;i<maxi;i++) ///Initialisation a NULL pour parcours tableau
    {
        nouveau->tabActeur[i]=NULL;
        nouveau->tabInter[i]=NULL;
    }

    nouveau->tabActeur[0]=constructeurActeur(100,100,1);
    nouveau->nActeur+=1;

    ///Recupere les bitmaps du decor.
    recupBitmapDecor(nouveau);

    return nouveau;
}

///Supprime les elements hors de l'ecran
void testMort(t_listeActeurs* ancre)
{
    int i=0;
    for(i=0;i<ancre->maxiActeur;i++)
    {
        if(ancre->tabActeur[i]!=NULL)
        {
            if(ancre->tabActeur[i]->etat==0 || ancre->tabActeur[i]->posx + ancre->tabActeur[i]->tx<0 || ancre->tabActeur[i]->hp==0)
            {
                free(ancre->tabActeur[i]);
                ancre->tabActeur[i]=NULL;
                ancre->nActeur-=1;
            }
        }
    }
    for(i=0;i<ancre->maxiInter;i++)
    {
        if(ancre->tabInter[i]!=NULL)
        {
            if(ancre->tabInter[i]->etat==0||ancre->tabInter[i]->posx>SCREEN_W||ancre->tabInter[i]->posx<0)
            {
                free(ancre->tabInter[i]);
                ancre->tabInter[i]=NULL;
                ancre->nInter-=1;
            }
        }
    }
}
