#include "proto.h"
#include <allegro.h>

void jeu()
{
    int xPage=0,retour=0,xFond=0;
    t_listeActeurs* ancre=creerListe(80);

    ///Déclaration des bitmap a utiliser
    BITMAP *page=NULL;      ///scroll du fond
    page=load_bitmap("back1.bmp",NULL);
    clear_bitmap(screen);
    BITMAP* fond=fondDecor(ancre,screen);   ///fond = bitmap de 10k pixel de long de décor
    BITMAP* bufferColi=fondBuffer(ancre,screen);    ///fond de 10 k pixel de buffer
    BITMAP* screenBuffer=create_bitmap(800,600);    ///buffer de screen

    if (!page)
    {
        allegro_message("pas pu trouver/charger back.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


                            /***** BOUCLE DE JEU *****/
    while (retour!=1)
    {
        int place=1, yes=0, creerE;

        ///Affichage aleatoire d'ennemis
        while(yes==0)
        {
            if(ancre->tabActeur[place]!=NULL)
                place++;
            else
            {
                creerE=rand()%20;
                if(creerE==1)
                    ancre->tabActeur[place]=constructeurActeur(800,rand()%600,2);
                yes=1;
            }
        }

        testMort(ancre);
        deplacementPersonnage(ancre);
        deplacementEnnemi(ancre);
        deplacementIntervenant(ancre);
        tirPersonnage(ancre);
        collisionDecor(fond,xFond,ancre);
       Affichage(&xPage,&xFond,screenBuffer,page,fond,bufferColi,ancre);




        if(key[KEY_P] || key[KEY_ESC])
        {
            rectfill(screen,SCREEN_W/2-200,SCREEN_H/2-50,SCREEN_W/2+200,SCREEN_H/2+50,makecol(255,255,255));
            textprintf_centre_ex(screen,font,SCREEN_W/2,SCREEN_H/2-30,makecol(0,0,0),-1,"PAUSE");
            textprintf_centre_ex(screen,font,SCREEN_W/2,SCREEN_H/2,makecol(0,0,0),-1,"Reprendre : P");
            textprintf_centre_ex(screen,font,SCREEN_W/2,SCREEN_H/2+20,makecol(0,0,0),-1,"Retourner au menu principal : O");
            rest(200);
            while(!key[KEY_O] && !key[KEY_P])
            {
                if(key[KEY_P])
                    break;
                else if(key[KEY_O])
                    retour=1;
            }
            rest(200);
        }
        rest(30);
    }


    free(ancre);
}
