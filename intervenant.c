#include "proto.h"

///Cree les intervenants (projectiles)
t_intervenant* constructeurIntervenant(int x,int y,int typ)
{
    t_intervenant* nouveau=(t_intervenant*)malloc(sizeof(t_intervenant));
    nouveau->posx=x;
    nouveau->posy=y;
    nouveau->type=typ;
    nouveau->etat=1;
    switch(nouveau->type)
    {
    case 1: ///laser de base
        nouveau->depx=20;
        nouveau->depy=0;
        nouveau->tx=15;
        nouveau->ty=2;
        nouveau->affiche=objet(nouveau->tx,nouveau->ty,makecol(255,0,0));
        nouveau->degat=10;
        break;
    case 2: ///missile
        nouveau->depx=5;
        nouveau->depy=rand()%5-2;
        nouveau->tx=30;
        nouveau->ty=10;
        nouveau->affiche=objet(nouveau->tx,nouveau->ty,makecol(255,165,0));
        nouveau->degat=20;
        break;
   case 3://laser boss1
        nouveau->depx=rand()%10-5;
        nouveau->depy=rand()%10-5;
        nouveau->tx=30;
        nouveau->ty=15;
        nouveau->affiche=objet(nouveau->tx,nouveau->ty,makecol(255,165,0));
        nouveau->degat=20;
        break;
   case 4://lance flammes boss
        nouveau->depx=-10;
        nouveau->depy=0;
        nouveau->tx=22;
        nouveau->ty=5;
        nouveau->affiche=objet(nouveau->tx,nouveau->ty,makecol(255,165,0));
        nouveau->degat=20;
        break;


    case 5: ///laser vaisseau ennemi
        nouveau->depx=-20;
        nouveau->depy=0;
        nouveau->tx=15;
        nouveau->ty=3;
        nouveau->affiche=objet(nouveau->tx,nouveau->ty,makecol(0,210,220));
        nouveau->degat=1;
        break;

    case 6: ///Missile reserve aux tourelles!!!!!!!!!!
        nouveau->depx=-9;
        nouveau->depy= - rand()%10;
        nouveau->tx=15;
        nouveau->ty=5;
        nouveau->affiche=objet(nouveau->tx,nouveau->ty,makecol(210,120,120));
        nouveau->degat=1;
        break;
    }

    nouveau->collision=objet(nouveau->tx,nouveau->ty,makecol(255,0,0));

    return nouveau;
}

///Ajoute un intervenant
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

///Deplace les projectiles
void deplacementIntervenant(t_listeActeurs* ancre)
{
    int i=0,compteur=0;

    for(i=compteur;i<ancre->nInter+compteur;i++)
    {
        if(ancre->tabInter[i]!=NULL)
        {
            ancre->tabInter[i]->posx+=ancre->tabInter[i]->depx;
            ancre->tabInter[i]->posy+=ancre->tabInter[i]->depy;
        }
        else
        {
            if(i==compteur+ancre->nInter)
                compteur=0;
            else{
                    compteur++;
            }
        }
    }
}
