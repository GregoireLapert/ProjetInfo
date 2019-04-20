#include "proto.h"
#include <allegro.h>

BITMAP* objet(int tx,int ty,int couleur, int type)
{

    BITMAP* obj=create_bitmap(tx,ty);
				clear_bitmap(obj);

    switch (type)
    {
    	case 1 :
				rectfill(obj,0,0,tx,ty,couleur);
			break;

		case 2:
				rectfill(obj,0,0,tx,ty,couleur);
			break;
    }


    return obj;
}
BITMAP* ActeursG(int tx,int ty )
{
    BITMAP* sprite=load_bitmap("vaisseau.bmp",NULL);
    draw_sprite(screen, sprite, tx, ty);


    return sprite;
}

BITMAP* ActeursM(int tx,int ty )
{
    BITMAP* sprite=load_bitmap("images/spaceship.bmp",NULL);
    draw_sprite(screen, sprite, tx, ty);


    return sprite;
}

void Affichage (int *xPage,int *xFond,BITMAP* screenBuffer,BITMAP*page,BITMAP* fond,BITMAP* bufColi,t_listeActeurs* ancre)
{


   /* a supprimer BITMAP* buffer=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(buffer);*/
    //scroll infini de Page Background
	blit(page,screenBuffer,*xPage,0,0,0,SCREEN_W,SCREEN_H);


	*xPage=*xPage+10;

	if (*xPage>1600)
	{
		*xPage=0;
	}
	//fin scroll infini



	*xFond=*xFond+3;

    masked_blit(fond,screenBuffer,*xFond,0,0,0,SCREEN_W,SCREEN_H);
	//
    int i=0;
    for(i=0;i<ancre->maxiActeur;i++)
    {

         if(ancre->tabActeur[i]!=NULL)
         {
             if(ancre->tabActeur[i]->etat!=0)
             {
                masked_blit(ancre->tabActeur[i]->affiche,screenBuffer,0,0,ancre->tabActeur[i]->posx,ancre->tabActeur[i]->posy,ancre->tabActeur[i]->tx,ancre->tabActeur[i]->ty);
             }
         }
    }
    for(i=0;i<ancre->maxiInter;i++)
    {

         if(ancre->tabInter[i]!=NULL)
         {
             if(ancre->tabInter[i]->etat!=0)
             {
                masked_blit(ancre->tabInter[i]->affiche,screenBuffer,0,0,ancre->tabInter[i]->posx,ancre->tabInter[i]->posy,ancre->tabInter[i]->tx,ancre->tabInter[i]->ty);
             }
         }
    }

    blit(screenBuffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);

   // free(buffer); a supprimer
}

