#include <stdlib.h>
#include <stdio.h>
#include "proto.h"
#include <time.h>

#define A

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
    ///////partie décor/////
    recupBitmapDecor(nouveau);

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
///////partie décor///////



t_decor* constructeurdecor(int x,int y,int numDecor,t_listeActeurs* ancre)
{
    t_decor* nouveau=(t_decor*)malloc(sizeof(t_decor));
    nouveau->posx=x;
    nouveau->posy=y;
    nouveau->affiche=ancre->decor[numDecor];

    return nouveau;
}

void generateurDecor(t_listeActeurs *ancre)
{
    int compteurZone=0;//écran a été divisé en 3 partie selon la posx(200 pixel chaque) car les 200 premiers pixel sont la copie de la dernière bitmap pour éviter les sauts
    int compteurNbParZone=0;// on met 5 élément de décor par zone
    int compteurElement=0;//max de 15 element de décor en tout
    int u=0;
    int posx=0;
    int posy=0;//bug donc alterne entre haut et bas

        for(compteurZone=1;compteurZone<=3;compteurZone++)
        {
            for(compteurNbParZone=0;compteurNbParZone<170;compteurNbParZone++)
            {
                posx=200+(compteurElement*50);/**compteurZone+(fibonnaci(u)%100);**///on place un element dans sa zone +- 200 pixel
                if(compteurElement%2!=0)
                {
                    posy=0;
                }
                else
                {
                    posy=550;
                }
                u=rand()%15;
                ancre->tabDecor[compteurElement]=constructeurdecor(posx,posy,u,ancre);
                compteurElement+=1;


            }
        }
}

BITMAP* fondDecor(t_listeActeurs *ancre,BITMAP* ancienFond)//copie les 200 premiers pixels de l'ancien fond pour créer une continuité partiel et pas de bug de generation de décor
{
    int i=0;
    BITMAP* nouveau=create_bitmap(10000,600);
    clear_to_color(nouveau,makecol(255,0,255));
    generateurDecor(ancre);
    for(i=0;i<510;i++)
    {
        if(ancre->tabDecor[i]->posy==0)
        {
            draw_sprite_v_flip(nouveau,ancre->tabDecor[i]->affiche,ancre->tabDecor[i]->posx,ancre->tabDecor[i]->posy);
        }

        if(ancre->tabDecor[i]->posy==550)
        {
                draw_sprite(nouveau,ancre->tabDecor[i]->affiche,ancre->tabDecor[i]->posx,ancre->tabDecor[i]->posy);
        }


    }
    return nouveau;
}

BITMAP *fondBuffer(t_listeActeurs* ancre,BITMAP* ancienFond)
{
    int i=0;
    BITMAP* nouveau=create_bitmap(10000,600);
    clear_bitmap(nouveau);
    /*masked_blit(screen,nouveau,600,0,0,0,200,600);*/
    generateurDecor(ancre);
    for(i=0;i<510;i++)
    {
        if(ancre->tabDecor[i]->posy==0)
        {
            BITMAP* transition=create_bitmap(ancre->tabDecor[i]->affiche->w,ancre->tabDecor[i]->affiche->h);
            clear_to_color(transition,makecol(255,0,255));
            draw_sprite_v_flip(transition,ancre->tabDecor[i]->affiche,ancre->tabDecor[i]->posx,ancre->tabDecor[i]->posy);
            blit(transition,nouveau,0,0,ancre->tabDecor[i]->posx,ancre->tabDecor[i]->posy,ancre->tabDecor[i]->affiche->w,ancre->tabDecor[i]->affiche->h);
        }

        if(ancre->tabDecor[i]->posy==550)
        {
            blit(ancre->tabDecor[i]->affiche,nouveau,0,0,ancre->tabDecor[i]->posx,ancre->tabDecor[i]->posy,ancre->tabDecor[i]->affiche->w,ancre->tabDecor[i]->affiche->h);
        }


    }
    return nouveau;
}

void recupBitmapDecor(t_listeActeurs *ancre)
{
    int i=0;
    for(i=0;i<15;i++)
    {
        switch(i)
        {
        case 0:

            ancre->decor[i]=load_bitmap("D:\\cour\\informatique\\projet perso\\Projet-informatique\\ProjetInfo\\images\\Decor\\image\\a.bmp",NULL);
            break;

        case 1:

            ancre->decor[i]=load_bitmap("D:\\cour\\informatique\\projet perso\\Projet-informatique\\ProjetInfo\\images\\Decor\\image\\b.bmp",NULL);
            break;

        case 2:
            ancre->decor[i]=load_bitmap("D:\\cour\\informatique\\projet perso\\Projet-informatique\\ProjetInfo\\images\\Decor\\image\\c.bmp",NULL);
            break;
        case 3:

            ancre->decor[i]=load_bitmap("D:\\cour\\informatique\\projet perso\\Projet-informatique\\ProjetInfo\\images\\Decor\\image\\d.bmp",NULL);
            break;
        case 4:

            ancre->decor[i]=load_bitmap("D:\\cour\\informatique\\projet perso\\Projet-informatique\\ProjetInfo\\images\\Decor\\image\\e.bmp",NULL);
            break;
        case 5:

            ancre->decor[i]=load_bitmap("D:\\cour\\informatique\\projet perso\\Projet-informatique\\ProjetInfo\\images\\Decor\\image\\f.bmp",NULL);
            break;
        case 6:

            ancre->decor[i]=load_bitmap("D:\\cour\\informatique\\projet perso\\Projet-informatique\\ProjetInfo\\images\\Decor\\image\\g.bmp",NULL);
            break;
        case 7:

            ancre->decor[i]=load_bitmap("D:\\cour\\informatique\\projet perso\\Projet-informatique\\ProjetInfo\\images\\Decor\\image\\h.bmp",NULL);
            break;
        case 8:

            ancre->decor[i]=load_bitmap("D:\\cour\\informatique\\projet perso\\Projet-informatique\\ProjetInfo\\images\\Decor\\image\\i.bmp",NULL);
            break;
        case 9:

            ancre->decor[i]=load_bitmap("D:\\cour\\informatique\\projet perso\\Projet-informatique\\ProjetInfo\\images\\Decor\\image\\j.bmp",NULL);
            break;
        case 10:

            ancre->decor[i]=load_bitmap("D:\\cour\\informatique\\projet perso\\Projet-informatique\\ProjetInfo\\images\\Decor\\image\\k.bmp",NULL);
            break;
        case 11:

            ancre->decor[i]=load_bitmap("D:\\cour\\informatique\\projet perso\\Projet-informatique\\ProjetInfo\\images\\Decor\\image\\l.bmp",NULL);
            break;
        case 12:

            ancre->decor[i]=load_bitmap("D:\\cour\\informatique\\projet perso\\Projet-informatique\\ProjetInfo\\images\\Decor\\image\\m.bmp",NULL);
            break;
        case 13:

            ancre->decor[i]=load_bitmap("D:\\cour\\informatique\\projet perso\\Projet-informatique\\ProjetInfo\\images\\Decor\\image\\n.bmp",NULL);
            break;
        case 14:

            ancre->decor[i]=load_bitmap("D:\\cour\\informatique\\projet perso\\Projet-informatique\\ProjetInfo\\images\\Decor\\image\\o.bmp",NULL);
            break;

        }

    }
}
