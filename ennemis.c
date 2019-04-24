#include "proto.h"

int PopEnnemis(t_listeActeurs* ancre, int place, int val1, int val2, int val3)
{
    int creerE1,creerE2,creerE3;
    int yes;

    if(ancre->tabActeur[place]!=NULL)
        yes=0;
    else
    {
        if(val1!=0)
            creerE1=rand()%val1;
        if(val2!=0)
            creerE2=rand()%val2;
        if(val3!=0)
            creerE3=rand()%val3;
        if(creerE1==1)
            ancre->tabActeur[place] = constructeurActeur(800,rand()%(349)+100,2);
        if(creerE2==1)
            ancre->tabActeur[place] = constructeurActeur(800,rand()%(349)+100,3);
        if(creerE3==1)
            ancre->tabActeur[place] = constructeurActeur(800,480,4);

        yes=1;
    }
    return yes;
}

///Deplacement ennemis
void deplacementEnnemi(t_listeActeurs* ancre)
{
    int i;
    for(i=1;i<ancre->maxiActeur;i++)
    {
        if(ancre->tabActeur[i]!=NULL)
        {
            t_acteur* ennemi=ancre->tabActeur[i];

            ennemi->posx -= ennemi->depx;

            if(ennemi->type==2)
            {
                if(ennemi->posx%200>100)
                    ennemi->posy += ennemi->depy;
                else ennemi->posy -= ennemi->depy;
            }
            if(ennemi->type==5 || ennemi->type==6)
            {
                if(rand()%8==0)
                {
                    ennemi->posx+=7;
                    ennemi->posy+=ennemi->depy;
                }

                else if(rand()%8==1)
                {
                     ennemi->posx+=7;
                    ennemi->posy-=ennemi->depy;
                }
            }
        }
    }
}

void popBoss(int x,t_listeActeurs* ancre,int* actif,int typ)
{
    if(ancre->tabActeur[0]->posx+x >9400 && *actif==0)
    {
        ajoutActeur(ancre,600,200,typ);
        *actif+=1;
    }
}

void TirEnnemi (t_listeActeurs *ancre)
{
    int i,a;

    for (i=0;i<ancre->maxiActeur;i++)
    {
        if(ancre->tabActeur[i]!=NULL)
        {
            ///Recherche et attaque tourelle
            if ((ancre->tabActeur[i]->type==4)&& ancre->tabActeur[i]->posx%200<20 && ancre->tabActeur[i]->posx%2==0)
                ajoutIntervenant(ancre,ancre->tabActeur [i]->posx,ancre->tabActeur [i]->posy+ ancre->tabActeur[i]->ty/2, 6);

            ///Recherche et attaque vaisseau ennemi
            else if ((ancre->tabActeur[i]->type==3)&& ancre->tabActeur[i]->posx%200<30 && ancre->tabActeur[i]->posx%2==0)
                ajoutIntervenant(ancre,ancre->tabActeur [i]->posx,ancre->tabActeur [i]->posy+ ancre->tabActeur[i]->ty/2, 5);

            ///Recherche et attaque boss 1
            else if(ancre->tabActeur[i]->type==5)
            {
                if(rand()%50==1)
                {
                    for(a=0;a<15;a++)
                    {
                        ajoutIntervenant(ancre,ancre->tabActeur[i]->posx+ancre->tabActeur[i]->tx/2,ancre->tabActeur[i]->posy+ancre->tabActeur[i]->ty/2,3);
                    }

                }
            }

            ///Recherche et attaque boss 2
            else if(ancre->tabActeur[i]->type==6)
            {
                if(rand()%5==1)
                {
                    for(a=0;a<2;a++)
                    {
                        ajoutIntervenant(ancre,ancre->tabActeur[i]->posx,ancre->tabActeur[i]->posy+ancre->tabActeur[i]->ty/2+rand()%100,4);
                    }

                }
            }
             ///Recherche et attaque boss 3
            else if(ancre->tabActeur[i]->type==7)
            {
                if(rand()%5==1)
                {
                    for(a=0;a<2;a++)
                    {
                        ajoutIntervenant(ancre,ancre->tabActeur[i]->posx+ancre->tabActeur[i]->tx/2,ancre->tabActeur[i]->posy+ancre->tabActeur[i]->ty/2,10);
                        ajoutIntervenant(ancre,ancre->tabActeur[i]->posx+ancre->tabActeur[i]->tx/2,ancre->tabActeur[i]->posy+ancre->tabActeur[i]->ty/2,3);
                    }

                }
            }
        }
    }
}


void AffichageBuffer(BITMAP* buffer,t_listeActeurs* ancre)
{
    int i;
    clear_to_color(buffer,makecol(255,0,255));

     for(i=0;i<ancre->maxiActeur;i++)
    {
         if(ancre->tabActeur[i]!=NULL)
         {
             if(ancre->tabActeur[i]->etat!=0)
                blit(ancre->tabActeur[i]->collision,buffer,0,0,ancre->tabActeur[i]->posx,ancre->tabActeur[i]->posy,ancre->tabActeur[i]->tx,ancre->tabActeur[i]->ty);
         }
    }

    ///Parcours et affichage des intervenants
    for(i=0;i<ancre->maxiInter;i++)
    {
         if(ancre->tabInter[i]!=NULL)
         {
             if(ancre->tabInter[i]->etat!=0)
                blit(ancre->tabInter[i]->collision,buffer,0,0,ancre->tabInter[i]->posx,ancre->tabInter[i]->posy,ancre->tabInter[i]->tx,ancre->tabInter[i]->ty);
         }
    }

}

void collisionTir(BITMAP* buffer,t_listeActeurs* ancre)
{
    int gauche=0;
    int droite=0;
    int cpt=0;
    int i=0;

    SAMPLE*bonus=load_sample("valider1.wav");

    /////collision tir////
     for(i=0;i<ancre->maxiInter;i++)
    {
         if(ancre->tabInter[i]!=NULL)
         {
             if(ancre->tabInter[i]->etat==1)
               {
                gauche=getpixel(buffer,ancre->tabInter[i]->posx-5,ancre->tabInter[i]->posy+(ancre->tabInter[i]->ty/2));
                droite=getpixel(buffer,ancre->tabInter[i]->posx+ancre->tabInter[i]->tx,ancre->tabInter[i]->posy+(ancre->tabInter[i]->ty/2));

                if(ancre->tabInter[i]->type<=2)
                {//////// laser allié
                    if(gauche!=makecol(0,255,0) || droite !=makecol(0,255,0))
                    {
                        for(cpt=1;cpt<ancre->maxiActeur;cpt++)
                        {
                            if(ancre->tabActeur[cpt]!=NULL)
                            {
                                if(ancre->tabActeur[cpt]->etat!=0)
                                {
                                    if(ancre->tabActeur[cpt]->id==gauche || ancre->tabActeur[cpt]->id==droite)
                                    {
                                        ancre->tabActeur[cpt]->hp-=ancre->tabInter[i]->degat;
                                        //caler bitmap explosions
                                        if(ancre->tabInter[i]->type<7)
                                        {
                                           ancre->tabInter[i]->etat=2;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    if(gauche==makecol(0,255,0) || droite==makecol(0,255,0))
                    {
                        ancre->tabActeur[0]->hp-=ancre->tabInter[i]->degat;
                        ancre->tabInter[i]->etat=2;
                        if(ancre->tabInter[i]->type==7)
                        {
                            ancre->tabInter[i]->etat=8;
                            ancre->tabActeur[0]->depx+=1;
                            ancre->tabActeur[0]->depy+=1;
                            play_sample(bonus,40,128,1000,0);
                        }
                        if(ancre->tabInter[i]->type==8)
                        {
                            ancre->tabInter[i]->etat=8;
                            ancre->tabActeur[0]->sp=100;
                            play_sample(bonus,40,128,1000,0);
                        }
                        if(ancre->tabInter[i]->type==9)
                        {
                            ancre->tabInter[i]->etat=8;
                            ancre->tabActeur[0]->hp=10;
                            play_sample(bonus,40,128,1000,0);
                        }
                     }
                       //caler bitmap explosions
                }
            }
        }
    }





        //collision entre ennemi

        if(getpixel(buffer,ancre->tabActeur[0]->posx-5,ancre->tabActeur[0]->posy)!=16711935 && getpixel(buffer,ancre->tabActeur[0]->posx-5,ancre->tabActeur[0]->posy)!=makecol(0,0,255))
        {
           ancre->tabActeur[0]->hp-=0.1;
        }
        if(getpixel(buffer,ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx/2,ancre->tabActeur[0]->posy-5)!=16711935 && getpixel(buffer,ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx/2,ancre->tabActeur[0]->posy-5)!=makecol(0,0,255))
        {
           ancre->tabActeur[0]->hp-=0.1;
        }
        if(getpixel(buffer,ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx+5,ancre->tabActeur[0]->posy)!=16711935 && getpixel(buffer,ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx+5,ancre->tabActeur[0]->posy)!=makecol(0,0,255))
        {
           ancre->tabActeur[0]->hp-=0.1;
        }
                // fin
            // debut de en bas
        if(getpixel(buffer,ancre->tabActeur[0]->posx-5,ancre->tabActeur[0]->posy+ancre->tabActeur[0]->ty+5)!=16711935 && getpixel(buffer,ancre->tabActeur[0]->posx-5,ancre->tabActeur[0]->posy+ancre->tabActeur[0]->ty+5)!=makecol(0,0,255))
        {
            ancre->tabActeur[0]->hp-=0.1;
        }
        if(getpixel(buffer,ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx/2,ancre->tabActeur[0]->posy+ancre->tabActeur[0]->ty+5)!=16711935 && getpixel(buffer,ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx/2,ancre->tabActeur[0]->posy+ancre->tabActeur[0]->ty+5)!=makecol(0,0,255))
        {
           ancre->tabActeur[0]->hp-=0.1;
        }
        if(getpixel(buffer,ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx+5,ancre->tabActeur[0]->posy+ancre->tabActeur[0]->ty+5)!=16711935 && getpixel(buffer,ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx+5,ancre->tabActeur[0]->posy+ancre->tabActeur[0]->ty+5)!=makecol(0,0,255))
        {
           ancre->tabActeur[0]->hp-=0.1;
        }
               //fin pts du bas
            //debut du millieu cot�
        if(getpixel(buffer,ancre->tabActeur[0]->posx-5,ancre->tabActeur[0]->posy+ancre->tabActeur[0]->ty/2)!=16711935 && getpixel(buffer,ancre->tabActeur[0]->posx-5,ancre->tabActeur[0]->posy+ancre->tabActeur[0]->ty/2)!=makecol(0,0,255))
        {
           ancre->tabActeur[0]->hp-=0.1;
        }
        if(getpixel(buffer,ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx+5,ancre->tabActeur[0]->posy+ancre->tabActeur[0]->ty/2)!=makecol(255,0,255) && getpixel(buffer,ancre->tabActeur[0]->posx+ancre->tabActeur[0]->tx+5,ancre->tabActeur[0]->posy+ancre->tabActeur[0]->ty/2)!=makecol(0,0,255))
        {
           ancre->tabActeur[0]->hp-=0.1;
        }

    destroy_bitmap(bonus);
}
