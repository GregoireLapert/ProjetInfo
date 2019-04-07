#include "proto.h"
#include <allegro.h>

void jeu()
{
    int x=0,retour=0;
    t_listeActeurs* ancre=creerListe(80);

    BITMAP *page=NULL;
    page=load_bitmap("back1.bmp",NULL);

    if (!page)
    {
        allegro_message("pas pu trouver/charger back.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    BITMAP* buffer1=NULL;
    buffer1=create_bitmap(SCREEN_W,SCREEN_H);

    if (!buffer1)
    {
        allegro_message("pas pu trouver/charger back.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // BOUCLE DE JEU
    while (retour==0)
    {
        testMort(ancre);
        deplacementPersonnage(ancre);
        deplacementIntervenant(ancre);
        tirPersonnage(ancre);
        Affichage(&x,page, screen, ancre);

        if(key[KEY_P])
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
