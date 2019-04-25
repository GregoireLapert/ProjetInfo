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
        nouveau->tx=40;
        nouveau->ty=5;
        nouveau->affiche=load_bitmap("laser ami.bmp",NULL);
        nouveau->degat=5;
        break;
    case 2: ///missile
        nouveau->depx=5;
        nouveau->depy=rand()%5-2;
        nouveau->tx=39;
        nouveau->ty=10;
        nouveau->affiche=load_bitmap("missile ami.bmp",NULL);
        nouveau->degat=10;
        break;
   case 3://laser boss1
        nouveau->depx=rand()%10-5;
        nouveau->depy=rand()%10-5;
        nouveau->tx=30;
        nouveau->ty=15;
        nouveau->affiche=objet(nouveau->tx,nouveau->ty,makecol(255,165,0));
        nouveau->degat=2;
        break;
   case 4://lance flammes boss 2
        nouveau->depx=-10;
        nouveau->depy=0;
        nouveau->tx=22;
        nouveau->ty=5;
        nouveau->affiche=objet(nouveau->tx,nouveau->ty,makecol(255,165,0));
        nouveau->degat=2;
        break;

    case 5: ///laser vaisseau ennemi
        nouveau->depx=-20;
        nouveau->depy=0;
        nouveau->tx=15;
        nouveau->ty=1;
        nouveau->affiche=load_bitmap("laserennemi.bmp",NULL);
        nouveau->degat=1;
        break;

    case 6: ///Missile reserve aux tourelles!!!!!!!!!!
        nouveau->depx=-9;
        nouveau->depy= - rand()%10;
        nouveau->tx=40;
        nouveau->ty=18;
        nouveau->affiche=load_bitmap("missileennemi.bmp",NULL);
        nouveau->degat=1;
        break;

    case 7://bonus vitesse
        nouveau->depx=-5;
        nouveau->depy=0;
        nouveau->tx=40;
        nouveau->ty=41;
        nouveau->affiche=load_bitmap("images\\speed.bmp",NULL);
        nouveau->degat=0;
        break;
    case 8:// bonus sp
        nouveau->depx=-5;
        nouveau->depy=0;
        nouveau->tx=40;
        nouveau->ty=41;
        nouveau->affiche=load_bitmap("images\\plusmissils.bmp",NULL);
        nouveau->degat=0;
        break;
    case 9://bonus hp
        nouveau->depx=-5;
        nouveau->depy=0;
        nouveau->tx=40;
        nouveau->ty=41;
        nouveau->affiche=load_bitmap("images\\health.bmp",NULL);
        nouveau->degat=0;
        break;
        case 10://lance flammes boss3
        nouveau->depx=-10;
        nouveau->depy=-rand()%8 +6;
        nouveau->tx=40;
        nouveau->ty=10;
        nouveau->affiche=objet(nouveau->tx,nouveau->ty,makecol(255,0,0));
        nouveau->degat=2;
        break;
    }

    if(!nouveau->affiche)
    {
        allegro_message("N'a pas pu trouver un intervenant.");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    if(nouveau->type<7 || nouveau->type==10)
        nouveau->collision=objet(nouveau->tx,nouveau->ty,makecol(255,0,0));
    else nouveau->collision=objet(nouveau->tx,nouveau->ty,makecol(0,0,255));

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
        if(ancre->tabInter[i]!=NULL )
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

void popBonus(int xFond,t_listeActeurs* ancre)
{
    if(xFond%800==0)
    {
        ajoutIntervenant(ancre,SCREEN_W,rand()%(349)+100,rand()%(9-7+1)+7);
    }
}
