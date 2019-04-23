#include "proto.h"
#include <allegro.h>

void jeu()
{
    int xPage=0,retour=0,xFond=0;
    int boss=0;
    t_listeActeurs* ancre=creerListe(80);

    ///D�claration des bitmap a utiliser
    BITMAP *page=NULL;      ///scroll du fond
    page=load_bitmap("images\\Decor\\background\\Fond.bmp",NULL);
    clear_bitmap(screen);
    BITMAP* fond=fondDecor(ancre,screen);   ///fond = bitmap de 10k pixel de long de d�cor
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
        int place=0, yes=0;

        ///Affichage aleatoire d'ennemis
        while(yes==0)
        {
            place++;
            yes=PopEnnemis(ancre,place,90,90,200);
        }

        testMort(ancre);

        if(ancre->tabActeur[0]==NULL)
        {
            rest(10);
            rectfill(screen,SCREEN_W/2-100,SCREEN_H/2-30,SCREEN_W/2+100,SCREEN_H/2+30,makecol(255,255,255));
            textprintf_centre_ex(screen,font,SCREEN_W/2,SCREEN_H/2,makecol(0,0,0),-1,"GAME OVER");

            while(!key[KEY_SPACE])
            {
                rest(5);
            }
            retour=1;
        }
        else
        {
            deplacementPersonnage(ancre);
            deplacementEnnemi(ancre);
            deplacementIntervenant(ancre);
            tirPersonnage(ancre);
            TirEnnemi(ancre);
            collisionDecor(fond,xFond,ancre);
            Affichage(&xPage,&xFond,screenBuffer,page,fond,bufferColi,ancre);
            popBoss(xFond,ancre,&boss,6);
            TirEnnemie(ancre);
        }



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
