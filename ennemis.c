#include "proto.h"

int PopEnnemis(t_listeActeurs* ancre, int place)
{
    int creerE1,creerE2,creerE3;
    int yes;

    if(ancre->tabActeur[place]!=NULL)
        yes=0;
    else
    {
        creerE1=rand()%90;
        creerE2=rand()%90;
        creerE3=rand()%200;
        if(creerE1==1)
            ancre->tabActeur[place] = constructeurActeur(800,rand()%500,2);
        if(creerE2==1)
            ancre->tabActeur[place] = constructeurActeur(800,rand()%500,3);
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
    if(ancre->tabActeur[0]->posx+x >9400 && *actif==2)
    {
        ajoutActeur(ancre,600,200,typ);
        *actif+=1;
    }
}

void TirEnnemie(t_listeActeurs* ancre)
{
    int i=0;
    int a=0;

    //recherche et attaque du boss 1
    for(i=0;i<ancre->maxiActeur;i++)
    {
        if(ancre->tabActeur[i]!=NULL)
        {
            if(ancre->tabActeur[i]->type==5)
            {
                if(rand()%50==1)
                {
                    for(a=0;a<15;a++)
                    {
                        ajoutIntervenant(ancre,ancre->tabActeur[i]->posx+ancre->tabActeur[i]->tx/2,ancre->tabActeur[i]->posy+ancre->tabActeur[i]->ty/2,3);
                    }

                }
            }
        }
    }

    //recherche et attaque boss 2


    for(i=0;i<ancre->maxiActeur;i++)
    {
        if(ancre->tabActeur[i]!=NULL)
        {


            if(ancre->tabActeur[i]->type==6)
            {
                if(rand()%5==1)
                {
                    for(a=0;a<2;a++)
                    {
                        ajoutIntervenant(ancre,ancre->tabActeur[i]->posx,ancre->tabActeur[i]->posy+ancre->tabActeur[i]->ty/2+rand()%100,4);
                    }

                }
            }
        }
    }
}

void TirEnnemi (t_listeActeurs *ancre)
{
    int i;

    for (i=0;i<ancre->maxiActeur;i++)
    {
        if (ancre->tabActeur[i]!=NULL )
        {
            if ((ancre->tabActeur[i]->type==4)&& ancre->tabActeur[i]->posx%200<20 && ancre->tabActeur[i]->posx%2==0)
                ajoutIntervenant(ancre,ancre->tabActeur [i]->posx,ancre->tabActeur [i]->posy+ ancre->tabActeur[i]->ty/2, 6);

            if ((ancre->tabActeur[i]->type==3)&& ancre->tabActeur[i]->posx%200<30 && ancre->tabActeur[i]->posx%2==0)
                ajoutIntervenant(ancre,ancre->tabActeur [i]->posx,ancre->tabActeur [i]->posy+ ancre->tabActeur[i]->ty/2, 5);
        }
    }
}
