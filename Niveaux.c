#include "proto.h"

int Niveau1()
{
    int place=0, yes=0, clear=0;

    while(clear==0)
    {
        ///Affichage aleatoire d'ennemis
        if(boss==0)
        {
            while(yes==0)
            {
                place++;
                yes=PopEnnemis(ancre,place,90,100,300);
            }
        }

        testMort(ancre);

        if(ancre->tabActeur[0]==NULL)
        {
            rest(200);
            masked_blit(GameOver,screen,0,0,SCREEN_W/2-GameOver->w/2,SCREEN_H/2-GameOver->h/2,GameOver->w,GameOver->h);

            while(!key[KEY_SPACE])
                rest(5);
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
        }


        ///Pause
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
}
