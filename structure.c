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
    case 1://gentil
        nouveau->depx=10;
        nouveau->depy=10;
        nouveau->hp=10;
        nouveau->sp=100.0;
        nouveau->id=makecol(rand()%255,rand()%255,rand()%255);
        nouveau->tx=153;
        nouveau->ty=90;
        //nouveau->affiche=objet(nouveau->tx,nouveau->ty,nouveau->id);
        nouveau->affiche=ActeursG(nouveau->tx,nouveau->ty);
        break;
    case 2://méchant 1
        nouveau->depx=5;
        nouveau->depy=5;
        nouveau->hp=10;
        nouveau->sp=100.0;
        nouveau->id=makecol(rand()%255,rand()%255,rand()%255);
        nouveau->tx=20;
        nouveau->ty=20;
        //nouveau->affiche=objet(nouveau->tx,nouveau->ty,nouveau->id);
        nouveau->affiche=ActeursM(nouveau->tx,nouveau->ty);
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
    case 1://laser de base
        nouveau->depx=20;
        nouveau->depy=0;
        nouveau->tx=15;
        nouveau->ty=2;
        nouveau->affiche=objet(nouveau->tx,nouveau->ty,makecol(255,0,0),1);
        nouveau->degat=10;
        break;
   case 2://missile
        nouveau->depx=5;
        nouveau->depy=rand()%5-2;
        nouveau->tx=30;
        nouveau->ty=10;
        nouveau->affiche=objet(nouveau->tx,nouveau->ty,makecol(255,165,0),2);
        nouveau->degat=20;
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
    for(i=0;i<maxi;i++)// initialisation a null pour parcours tableau
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
    if(ancre->nActeur<ancre->maxiActeur)
    {
    int i=0;
    while(ancre->tabActeur[i]!=NULL&&i<ancre->maxiActeur)
    {
        i+=1;
    }
    ancre->tabActeur[i]=constructeurActeur(x,y,typ);
    ancre->nActeur+=1;
    }

}

void ajoutIntervenant(t_listeActeurs* ancre,int x,int y,int typ)
{
    if(ancre->nInter < ancre->maxiInter)
    {
        int i=0;

        while(ancre->tabInter[i]!=NULL&&i<ancre->maxiInter)
        {
            i+=1;
        }
        ancre->tabInter[i]=constructeurIntervenant(x,y,typ);
        ancre->nInter+=1;
    }
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
        if(ancre->tabInter[i]->etat==0||ancre->tabInter[i]->posx>SCREEN_W)
            {
                free(ancre->tabInter[i]);
                ancre->tabInter[i]=NULL;
                ancre->nInter-=1;
            }
        }

    }
}

void detruireInter(t_listeActeurs* ancre)
{
    int i=0;
     for(i=0;i<ancre->maxiInter;i++)
    {
        if(ancre->tabInter[i]!=NULL)
        {
             free(ancre->tabInter[i]);
            ancre->tabInter[i]=NULL;
            ancre->nInter-=1;
        }
    }
}
