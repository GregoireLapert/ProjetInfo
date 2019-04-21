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
            nouveau->tx=153;
            nouveau->ty=90;
            nouveau->affiche = load_bitmap("vaisseau.bmp",NULL);
            break;

        case 2:     ///méchant 1
            nouveau->depx=5;
            nouveau->depy=5;
            nouveau->hp=10;
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
void deplacementPersonnage(t_listeActeurs* ancre, BITMAP *bufferColi)
{
    t_acteur* joueur=ancre->tabActeur[0];
    if(key[KEY_LEFT])
    {
        if (getpixel(bufferColi,joueur->posx,joueur->posy)!= makecol(255,0,255) ) 
        {
           if (getpixel(bufferColi,joueur->posx,joueur->posy + joueur->ty/2)!= makecol(255,0,255) )  
            {
                if (getpixel(bufferColi,joueur->posx,joueur->posy + joueur->ty)!= makecol(255,0,255) )  
                {
                    joueur->posx -= joueur->depx;
                }
                
            }
            
        }
        
        if (joueur->posx<0)
        {
          
            joueur->posx=0;
        }
    }

    if(key[KEY_RIGHT])
    {
        if (getpixel(bufferColi,joueur->posx+ joueur->tx ,joueur->posy )!= makecol(255,0,255) ) 
        {
            if (getpixel(bufferColi,joueur->posx+ joueur->tx ,joueur->posy+ joueur->ty/2 )!= makecol(255,0,255) ) 
            {
                if (getpixel(bufferColi,joueur->posx+ joueur->tx ,joueur->posy+ joueur->ty )!= makecol(255,0,255) ) 
                {
                    joueur->posx += joueur->depx;      
                }
            }
          
        }
        
        if (joueur->posx+joueur->tx > SCREEN_W)
        {
            joueur->posx=SCREEN_W-joueur->tx;
        }
    }

    if (key[KEY_UP])
    {
        if (getpixel(bufferColi,joueur->posx ,joueur->posy )!= makecol(255,0,255) ) 
        {
            if (getpixel(bufferColi,joueur->posx + joueur->tx/2 ,joueur->posy)!= makecol(255,0,255) ) 
            {
                if (getpixel(bufferColi,joueur->posx + joueur->tx ,joueur->posy )!= makecol(255,0,255) ) 
                {
                    joueur->posy -= joueur->depy;    
                }
                
            }
            
        }
        
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
