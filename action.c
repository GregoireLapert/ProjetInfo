#include "proto.h"
#include <allegro.h>

///Tirs des projectiles du personnage selon la touche appuyee
void tirPersonnage(t_listeActeurs* ancre)
{
    if(ancre->tabActeur[0]->sp>0)
    {
        if(key[KEY_SPACE])
        {
            ajoutIntervenant(ancre,ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx,ancre->tabActeur[0]->posy+12+ancre->tabActeur[0]->ty/2,1);    ///Rajouter des types pour d'autres missiles
        }
        if (key[KEY_W])
        {
            ///Un missile coute 30 SP
            if(ancre->tabActeur[0]->sp>=30)
            {
                ajoutIntervenant(ancre,ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx,ancre->tabActeur[0]->posy+8+ancre->tabActeur[0]->ty/2,2);    ///Rajouter des types pour d'autres missiles
                ancre->tabActeur[0]->sp-=30;
            }
        }
    }

    ///SP se recharge avec le temps
    if(ancre->tabActeur[0]->sp<100)
        ancre->tabActeur[0]->sp++;
}
