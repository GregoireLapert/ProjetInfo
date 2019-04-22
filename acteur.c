#include "proto.h"

///Cree les acteurs
///AJOUTER COLLISIONS
t_acteur* constructeurActeur(int x,int y,int typ)
{
    t_acteur* nouveau=(t_acteur*)malloc(sizeof(t_acteur));
    nouveau->posx=x;
    nouveau->posy=y;
    nouveau->type=typ;
    nouveau->etat=1;
    switch(nouveau->type)
    {
        case 1:     ///gentil
            nouveau->depx=10;
            nouveau->depy=10;
            nouveau->hp=10;
            nouveau->sp=100.0;
            nouveau->id=makecol(rand()%255,rand()%255,rand()%255);  ///Mettre une couleur fixe
            nouveau->affiche = load_bitmap("vaisseau.bmp",NULL);

            break;

        case 2:     ///Ennemi 1 : Asteroides
            nouveau->depx=5;
            nouveau->depy=2;
            nouveau->hp=10;
            nouveau->sp=100.0;
            nouveau->id=makecol(rand()%255,rand()%255,rand()%255);
            nouveau->affiche = load_bitmap("images\\ennemies\\m3.bmp",NULL);
            break;
        case 3:

            break;
    }
    nouveau->tx=nouveau->affiche->w;
    nouveau->ty=nouveau->affiche->h;

        case 3:     ///Ennemi 2 : Vaisseau
            nouveau->depx=5;
            nouveau->depy=0;
            nouveau->hp=10;
            nouveau->sp=100.0;
            nouveau->id=makecol(rand()%255,rand()%255,rand()%255);
            nouveau->affiche = load_bitmap("ennemi.bmp",NULL);
            nouveau->tx=nouveau->affiche->w;
            nouveau->ty=nouveau->affiche->h;
            break;

        case 4:     ///Ennemi 3 : Tourelle
            nouveau->depx=3;
            nouveau->depy=0;
            nouveau->hp=5;
            nouveau->sp=100.0;
            nouveau->id=makecol(rand()%255,rand()%255,rand()%255);
            nouveau->affiche = load_bitmap("ennemi.bmp",NULL);
            nouveau->tx=nouveau->affiche->w;
            nouveau->ty=nouveau->affiche->h;
            break;
    }

    return nouveau;
}

///Ajoute un acteur.
void ajoutActeur(t_listeActeurs* ancre,int x,int y,int typ)
{
    int i=0;

    if(ancre->nActeur<ancre->maxiActeur)
    {
        while(ancre->tabActeur[i]!=NULL&&i<ancre->maxiActeur)
            i+=1;

        ancre->tabActeur[i]=constructeurActeur(x,y,typ);
        ancre->nActeur+=1;
    }

}

///Deplace le personnage jouable selon la touche appuyee
void deplacementPersonnage(t_listeActeurs* ancre)
{
    t_acteur* joueur=ancre->tabActeur[0];
    if(key[KEY_LEFT])
    {
        joueur->posx -= joueur->depx;
        if (joueur->posx<0)
        {
            joueur->posx=0;
        }
    }

    if(key[KEY_RIGHT])
    {
        joueur->posx += joueur->depx;
        if (joueur->posx+joueur->tx > SCREEN_W)
        {
            joueur->posx=SCREEN_W-joueur->tx;
        }
    }

    if (key[KEY_UP])
    {
        joueur->posy -= joueur->depy;
        if (joueur->posy<0)
        {
            joueur->posy=0;
        }
    }

    if (key[KEY_DOWN])
    {
        joueur->posy += joueur->depy;
        if (joueur->posy+joueur->ty > SCREEN_H)
        {
            joueur->posy=SCREEN_H-joueur->ty;
        }
    }
}

void collisionDecor(BITMAP* fond,int x,t_listeActeurs* ancre)
{
        //collision d�cor en +- x si couleur diff�rente de magenta alors rebondi



// 3 pts en haut

    if(getpixel(fond,x+ancre->tabActeur[0]->posx-5,ancre->tabActeur[0]->posy)!=16711935)
            {
               ancre->tabActeur[0]->posx+=ancre->tabActeur[0]->depx;
            }

    if(getpixel(fond,x+ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx/2,ancre->tabActeur[0]->posy-5)!=16711935)
            {
               ancre->tabActeur[0]->posy+=ancre->tabActeur[0]->depy;

            }
    if(getpixel(fond,x+ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx+5,ancre->tabActeur[0]->posy)!=16711935)
            {
               ancre->tabActeur[0]->posx-=ancre->tabActeur[0]->depx;

            }
            // fin
        // debut de en bas
    if(getpixel(fond,x+ancre->tabActeur[0]->posx-5,ancre->tabActeur[0]->posy+ancre->tabActeur[0]->ty+5)!=16711935)
            {
                ancre->tabActeur[0]->posx+=ancre->tabActeur[0]->depx;
                ancre->tabActeur[0]->posy-=ancre->tabActeur[0]->depy;

            }
    if(getpixel(fond,ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx/2,ancre->tabActeur[0]->posy+ancre->tabActeur[0]->ty+5)!=16711935)
            {
               ancre->tabActeur[0]->posy-=ancre->tabActeur[0]->depy;

            }
    if(getpixel(fond,x+ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx+5,ancre->tabActeur[0]->posy+ancre->tabActeur[0]->ty+5)!=16711935)
            {
               ancre->tabActeur[0]->posx-=ancre->tabActeur[0]->depx;

            }
           //fin pts du bas
        //debut du millieu cot�
    if(getpixel(fond,x+ancre->tabActeur[0]->posx-5,ancre->tabActeur[0]->posy+ancre->tabActeur[0]->ty/2)!=16711935)
            {
               ancre->tabActeur[0]->posx+=ancre->tabActeur[0]->depx;

            }
    if(getpixel(fond,x+ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx+5,ancre->tabActeur[0]->posy+ancre->tabActeur[0]->ty/2)!=makecol(255,0,255))
            {
               ancre->tabActeur[0]->posx-=ancre->tabActeur[0]->depx;

            }

}
