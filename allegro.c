#include "proto.h"
#include <allegro.h>

BITMAP* objet(int tx,int ty,int couleur)
{
    BITMAP* obj=create_bitmap(tx,ty);
    clear_bitmap(obj);
    rectfill(obj,0,0,tx,ty,couleur);
    return obj;
}

void Affichage (int *x,BITMAP*page, BITMAP* screen, t_listeActeurs* ancre)
{
    BITMAP* buffer=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(buffer);
    
	blit(page,buffer,*x,0,0,0,SCREEN_W,SCREEN_H);	
	
		
	*x=*x+10;
	
	if (*x>1600)
	{
		*x=0;
	}	
	
    int i=0;
    for(i=0;i<ancre->maxiActeur;i++)
    {

         if(ancre->tabActeur[i]!=NULL)
         {
             if(ancre->tabActeur[i]->etat!=0)
             {
                masked_blit(ancre->tabActeur[i]->affiche,buffer,0,0,ancre->tabActeur[i]->posx,ancre->tabActeur[i]->posy,ancre->tabActeur[i]->tx,ancre->tabActeur[i]->ty);
             }
         }
    }
    for(i=0;i<ancre->maxiInter;i++)
    {

         if(ancre->tabInter[i]!=NULL)
         {
             if(ancre->tabInter[i]->etat!=0)
             {
                masked_blit(ancre->tabInter[i]->affiche,buffer,0,0,ancre->tabInter[i]->posx,ancre->tabInter[i]->posy,ancre->tabInter[i]->tx,ancre->tabInter[i]->ty);
             }
         }
    }
    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    	
    free(buffer);
}

