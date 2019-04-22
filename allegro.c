#include "proto.h"
#include <allegro.h>

BITMAP* objet(int tx,int ty,int couleur)
{
    BITMAP* obj=create_bitmap(tx,ty);
    clear_bitmap(obj);

    rectfill(obj,0,0,tx,ty,couleur);        ///Missile

    return obj;
}

///Affichage
void Affichage (int *xPage,int *xFond,BITMAP* screenBuffer,BITMAP*page,BITMAP* fond,BITMAP* bufColi,t_listeActeurs* ancre)
{
    int i=0;

    ///Scroll infini de Page Background
	*xPage=*xPage+10;

    if(*xPage>=page->w)
        *xPage=0;

    if(*xPage+SCREEN_W<page->w)
    {
        blit(page,screenBuffer,*xPage,0,0,0,SCREEN_W,SCREEN_H);
    }
    else
    {
        blit(page,screenBuffer,*xPage,0,0,0,page->w-*xPage,SCREEN_H);
        blit(page,screenBuffer,0,0,page->w-*xPage,0,SCREEN_W-(page->w-*xPage),SCREEN_H);
    }
	///Fin scroll infini


	///Scroll decor avant
	*xFond=*xFond+3;

    masked_blit(fond,screenBuffer,*xFond,0,0,0,SCREEN_W,SCREEN_H);
	///Fin scroll decor avant

	///Parcours et affichage des acteurs
    for(i=0;i<ancre->maxiActeur;i++)
    {
         if(ancre->tabActeur[i]!=NULL)
         {
             if(ancre->tabActeur[i]->etat!=0)
                masked_blit(ancre->tabActeur[i]->affiche,screenBuffer,0,0,ancre->tabActeur[i]->posx,ancre->tabActeur[i]->posy,ancre->tabActeur[i]->tx,ancre->tabActeur[i]->ty);
         }
    }

    ///Parcours et affichage des intervenants
    for(i=0;i<ancre->maxiInter;i++)
    {
         if(ancre->tabInter[i]!=NULL)
         {
             if(ancre->tabInter[i]->etat!=0)
                masked_blit(ancre->tabInter[i]->affiche,screenBuffer,0,0,ancre->tabInter[i]->posx,ancre->tabInter[i]->posy,ancre->tabInter[i]->tx,ancre->tabInter[i]->ty);
         }
    }

    ///Barre de vie
    int BarreVie=ancre->tabActeur[0]->hp;

    textprintf_ex(screenBuffer,font,10,485,makecol(255,255,255),-1,"VIE");

    for(i=0;i<BarreVie;i++)
        rectfill(screenBuffer,10,500,10+11*i,510,makecol(255,0,0));
    rect(screenBuffer,10,500,110,510,makecol(255,255,255));

    ///Jauge de missiles (nombre de missiles disponibles)
    int nbMissiles=ancre->tabActeur[0]->sp/20;

    textprintf_ex(screenBuffer,font,10,535,makecol(255,255,255),-1,"MISSILES");

    for(i=0;i<nbMissiles;i++)
        rect(screenBuffer,10+20*i,550,30+20*i,560,makecol(255,255,255));

    ///Copie de buffer sur screen
    blit(screenBuffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
}

