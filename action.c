#include "proto.h"
#include <allegro.h>
#include <time.h>

///Tirs des projectiles du personnage selon la touche appuyee
void tirPersonnage(t_listeActeurs* ancre, int *xpage)
{
    if(ancre->tabActeur[0]->sp>0)
    {
        if(key[KEY_SPACE])
        {
            if (*xpage%5==0)
            {
                ajoutIntervenant(ancre,ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx,ancre->tabActeur[0]->posy+12+ancre->tabActeur[0]->ty/2,1);    ///Rajouter des types pour d'autres missiles
            }

        }

        if (key[KEY_W])
        {
            ///Un missile coute 20 SP
            if(ancre->tabActeur[0]->sp>=20)
            {
                ajoutIntervenant(ancre,ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx,ancre->tabActeur[0]->posy+8+ancre->tabActeur[0]->ty/2,2);    ///Rajouter des types pour d'autres missiles
                ancre->tabActeur[0]->sp-=20;
            }
        }

        if(ancre->tabActeur[0]->sp==0)
            ancre->tabActeur[0]->sp=1;
    }
}
