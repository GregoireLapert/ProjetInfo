#ifndef PROTO_H_INCLUDED
#define PROTO_H_INCLUDED
#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

///Creation structure pour d�cor
typedef struct decor
{
    BITMAP* affiche;    ///bitmap afficher sur screen
    int posx;
    int posy;
}t_decor;

///Acteur = tout PJ ou PNJ primaire ennemi, gentil
typedef struct acteur{
int posx;
int posy;
int depx;
int depy;
float hp;         ///pts de vie acteur
float sp;       ///pts �nergie acteur en pourcent
int id;         ///correspond au makecol du buffer de collision
int etat;       ///0=mort 1=vie
BITMAP* affiche;        ///a remplacer par un tableau de bitmap* si animation
BITMAP* collision;
int tx;         ///taille =>facilite collision
int ty;
int type;       ///0 pour joueur 1 pour ennemi 1...
}t_acteur;


///tout les �lement NJ: missile, bonus...
typedef struct intervenant{
BITMAP* affiche;
BITMAP* collision;
int etat;
int posx;
int posy;
int depx;
int depy;
int degat;
int tx;         ///taille =>facilite collision
int ty;
int type;
}t_intervenant;

typedef struct listeActeurs
{
    /// nombre maxi d'�l�ments = taille du tableau de pointeurs
    int maxiActeur;

    ///nombre effectif de pointeurs utilis�s
    ///(les autres sont � NULL)
    int nActeur;

    /// le tableau de pointeurs (allou� dynamiquement)
    t_acteur **tabActeur;

    int maxiInter;
    int nInter;
    t_intervenant **tabInter;

    /***d�cor***/
    BITMAP *decor[15];
    t_decor *tabDecor[510];

}t_listeActeurs;


                /*********Liste de fonctions**********/

/***Allegro***/
BITMAP* objet(int tx,int ty,int couleur);

/***Menu Principal***/
void MenuPrincipal(int*choix);
void MenuJouer(int*choix);
void MenuNiveau(int*choix);
void AffMJ();
void AffMP();
void AffMM();

/***Structure***/
t_acteur* constructeurActeur(int x,int y,int typ);  ///cr�e objet acteur
t_listeActeurs* creerListe(int maxi);               ///cr�e ancre
void testMort(t_listeActeurs* ancre);               ///test si etat=0 donc tue
void ajoutActeur(t_listeActeurs* ancre,int x,int y,int typ);    ///test si peut ajouter acteur et ajoute
t_intervenant* constructeurIntervenant(int x,int y,int typ);    ///creer objet intervenant
void ajoutIntervenant(t_listeActeurs* ancre,int x,int y,int typ);   ///test et ajoute intervenant

/***action***/
void deplacementPersonnage(t_listeActeurs* ancre);
void tirPersonnage(t_listeActeurs* ancre, int *xpage);

void deplacementIntervenant(t_listeActeurs* ancre);
void deplacementEnnemi(t_listeActeurs* ancre);

void jeu();
/***Decor***/
void recupBitmapDecor(t_listeActeurs *ancre);
BITMAP* fondDecor(t_listeActeurs *ancre,BITMAP* ancienFond);
void generateurDecor(t_listeActeurs *ancre);
BITMAP *fondBuffer(t_listeActeurs* ancre,BITMAP* ancienFond);
void creerDecor(t_listeActeurs* ancre,BITMAP* fond,BITMAP* buffer);
void Affichage (int *xPage,int *xFond,BITMAP* screenBuffer,BITMAP*page,BITMAP* fond,BITMAP* bufColi,t_listeActeurs* ancre);
void collisionDecor(BITMAP* fond,int x,t_listeActeurs* ancre);
void deplacementEnnemi(t_listeActeurs* ancre);
int PopEnnemis(t_listeActeurs* ancre, int place, int val1, int val2, int val3);


// en cours de travail
void popBoss(int x,t_listeActeurs* ancre,int* actif,int typ);
void TirEnnemi(t_listeActeurs* ancre);
void AffichageBuffer(BITMAP* buffer,t_listeActeurs* ancre);
void collisionTir(BITMAP* buffer,t_listeActeurs* ancre);

#endif // PROTO_H_INCLUDED
