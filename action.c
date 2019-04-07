#include "proto.h"
#include <allegro.h>

void deplacementPersonnage(t_listeActeurs* ancre)
{
    t_acteur* joueur=ancre->tabActeur[0];
      if (key[KEY_LEFT]){
        joueur->posx -= joueur->depx;
        if (joueur->posx<0)
        {
            joueur->posx=0;
        }
    }

    if (key[KEY_RIGHT]){
        joueur->posx += joueur->depx;
        if (joueur->posx+joueur->tx > SCREEN_W)
        {
            joueur->posx=SCREEN_W-joueur->tx;
        }
    }

    if (key[KEY_UP]){
        joueur->posy -= joueur->depy;
        if (joueur->posy<0)
        {
             joueur->posy=0;
        }
    }

    if (key[KEY_DOWN]){
        joueur->posy += joueur->depy;
        if (joueur->posy+joueur->ty > SCREEN_H)
        {
            joueur->posy=SCREEN_H-joueur->ty;
        }
    }
}

void tirPersonnage(t_listeActeurs* ancre)
{
    if(key[KEY_0_PAD])
    {
        detruireInter(ancre);
    }
    if(ancre->tabActeur[0]->sp>0)
    {
        if(key[KEY_SPACE])
        {
            ajoutIntervenant(ancre,ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx,ancre->tabActeur[0]->posy+ancre->tabActeur[0]->ty/2,1);//rajouter des types pour d'autres missiles


           /** ancre->tabActeur[0]->sp-=1; en attente de fonction de régen de sp**/
        }
        if (key[KEY_W])
        {
            ajoutIntervenant(ancre,ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx,ancre->tabActeur[0]->posy+ancre->tabActeur[0]->ty/2,2);//rajouter des types pour d'autres missiles
        }
    }
}
















void deplacementIntervenant(t_listeActeurs* ancre)
{
    int i=0,compteur=0;

    for(i=compteur;i<ancre->nInter+compteur;i++)
    {
        if(ancre->tabInter[i]!=NULL)
        {
            ancre->tabInter[i]->posx+=ancre->tabInter[i]->depx;
            ancre->tabInter[i]->posy+=ancre->tabInter[i]->depy;
        }
        else
        {
            if(i==compteur+ancre->nInter)
                compteur=0;
            else{
                    compteur++;
            }
        }
    }
}
