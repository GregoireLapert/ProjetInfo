#include "proto.h"
#include <allegro.h>

void jeu(int clear1, int clear2, int clear3)
{
    int retour=0;
                            /***** BOUCLE DE JEU *****/
    while (retour!=1)
    {
        if(clear1==0)
            clear1=Niveau(1);
        if(clear1==1 && clear2==0)
            clear2=Niveau(2);
        if(clear2==1)
            clear3=Niveau(3);
        if(clear3==1)
            retour=1;
        if(clear1==-1 || clear2==-1 || clear3==-1)
        {
            clear_bitmap(screen);
            rest(200);
            rectfill(screen,SCREEN_W/2-200,SCREEN_H/2-50,SCREEN_W/2+200,SCREEN_H/2+50,makecol(255,255,255));
            textprintf_centre_ex(screen,font,SCREEN_W/2,SCREEN_H/2-30,makecol(0,0,0),-1,"REESSAYER ?");
            textprintf_centre_ex(screen,font,SCREEN_W/2,SCREEN_H/2,makecol(0,0,0),-1,"Oui : O");
            textprintf_centre_ex(screen,font,SCREEN_W/2,SCREEN_H/2+20,makecol(0,0,0),-1,"Retourner au menu principal : X");
            while(!key[KEY_O] && !key[KEY_X])
            {
                if(key[KEY_O])
                {
                    if(clear1==-1)
                        clear1=0;
                    else if(clear2==-1)
                        clear2=0;
                    else if(clear3==-1)
                        clear3=0;
                }
                else if(key[KEY_X])
                    retour=1;
            }
        }
        else retour=1;
    }
}
