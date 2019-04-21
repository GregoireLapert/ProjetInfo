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
	blit(page,screenBuffer,*xPage,0,0,0,SCREEN_W,SCREEN_H);

	*xPage=*xPage+10;

	if (*xPage>1600)
		*xPage=0;
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

    ///Copie de buffer sur screen
    blit(screenBuffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
}

