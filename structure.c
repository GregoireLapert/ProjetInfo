#include <stdlib.h>
#include <stdio.h>
#include "proto.h"
#include <time.h>

t_acteur* constructeurActeur(int x,int y,int typ)
{
    t_acteur* nouveau=(t_acteur*)malloc(sizeof(t_acteur));
    nouveau->posx=x;
    nouveau->posy=y;
    nouveau->type=typ;
    nouveau->etat=1;
    switch(nouveau->type)
    {
    case 1:
        nouveau->depx=0;
        nouveau->depy=0;
        nouveau->hp=10;
        nouveau->sp=100.0;
        nouveau->id=makecol(rand()%255,rand()%255,rand()%255);
        nouveau->tx=100;
        nouveau->ty=100;
        nouveau->affiche=objet(nouveau->tx,nouveau->ty,nouveau->id);
        break;
    case 2:
        nouveau->depx=0;
        nouveau->depy=0;
        nouveau->hp=10;
        nouveau->sp=100.0;
        nouveau->id=makecol(rand()%255,rand()%255,rand()%255);
        nouveau->tx=100;
        nouveau->ty=100;
        nouveau->affiche=objet(nouveau->tx,nouveau->ty,nouveau->id);
        break;
    }

    return nouveau;
}

t_intervenant* constructeurIntervenant(int x,int y,int typ)
{
    t_intervenant* nouveau=(t_intervenant*)malloc(sizeof(t_intervenant));
    nouveau->posx=x;
    nouveau->posy=y;
    nouveau->type=typ;
    nouveau->etat=1;
    switch(nouveau->type)
    {
    case 1:
        nouveau->depx=0;
        nouveau->depy=0;
        nouveau->tx=100;
        nouveau->ty=100;
        nouveau->affiche=objet(nouveau->tx,nouveau->ty,makecol(255,0,0));
        nouveau->degat=0;
        break;
   case 2:
        nouveau->depx=0;
        nouveau->depy=0;
        nouveau->tx=100;
        nouveau->ty=100;
        nouveau->affiche=objet(nouveau->tx,nouveau->ty,makecol(255,0,0));
        nouveau->degat=0;
        break;
    }
    return nouveau;
}

t_listeActeurs* creerListe(int maxi)
{
    t_listeActeurs* nouveau=(t_listeActeurs*)malloc(sizeof(t_listeActeurs));
    nouveau->maxiActeur=maxi;
    nouveau->maxiInter=maxi;
    nouveau->nActeur=0;
    nouveau->nInter=0;
    nouveau->tabActeur=(t_acteur**)malloc(maxi*sizeof(t_acteur*));
    nouveau->tabInter=(t_intervenant**)malloc(maxi*sizeof(t_intervenant*));
    int i=0;
    for(i=0;i<maxi;i++)
    {
        nouveau->tabActeur[i]=NULL;
        nouveau->tabInter[i]=NULL;
    }
    nouveau->tabActeur[0]=constructeurActeur(100,100,1);
    nouveau->nActeur+=1;
    return nouveau;
}

void ajoutActeur(t_listeActeurs* ancre,int x,int y,int typ)
{
    int i=0;
    while(ancre->tabActeur[i]!=NULL&&i<ancre->maxiActeur)
    {
        i+=1;
    }
    ancre->tabActeur[i]=constructeurActeur(x,y,typ);
    ancre->nActeur+=1;
}

void ajoutIntervenant(t_listeActeurs* ancre,int x,int y,int typ)
{
    int i=0;
    while(ancre->tabInter[i]!=NULL&&i<ancre->maxiInter)
    {
        i+=1;
    }
    ancre->tabInter[i]=constructeurIntervenant(x,y,typ);
    ancre->nInter+=1;
}

void testMort(t_listeActeurs* ancre)
{
    int i=0;
    for(i=0;i<ancre->maxiActeur;i++)
    {
        if(ancre->tabActeur[i]!=NULL)
        {
             if(ancre->tabActeur[i]->etat==0)
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
             if(ancre->tabInter[i]->etat==0)
        {
            free(ancre->tabInter[i]);
            ancre->tabInter[i]=NULL;
            ancre->nInter-=1;
        }
        }

    }
}
