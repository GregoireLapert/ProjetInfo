#ifndef PROTO_H_INCLUDED
#define PROTO_H_INCLUDED
#include <allegro.h>
//acteur= tout PJ ou PNJ primaire ennemi, gentil
typedef struct acteur{
int posx;
int posy;
int depx;
int depy;
int hp;//pts de vie acteur
float sp;//pts énergie acteur en pourcent
int id;//correspond au makecol du buffer de collision
int etat;//0=mort 1=vie
BITMAP* affiche;//a remplacer par un tableau de bitmap* si animation
int tx;//taille =>facilite collision
int ty;
int type;//0 pour joueur 1 pour ennemi 1...
}t_acteur;


//tout les élement NJ: missile, bonus...
typedef struct intervenant{
BITMAP* affiche;
int etat;
int posx;
int posy;
int depx;
int depy;
int degat;
int tx;//taille =>facilite collision
int ty;
int type;
}t_intervenant;

typedef struct listeActeurs
{
    // nombre maxi d'éléments
    // =taille du tableau de pointeurs
    int maxiActeur;

    // nombre effectif de pointeurs utilisés
    // (les autres sont à NULL)
    int nActeur;

    // le tableau de pointeurs (alloué dynamiquement)
    t_acteur **tabActeur;

    int maxiInter;
    int nInter;
    t_intervenant **tabInter;

} t_listeActeurs;


////liste de fonctions////

////allegro/////
BITMAP* objet(int tx,int ty,int couleur, int type);
BITMAP* ActeursG(int tx,int ty ); //Acteurs gentils
BITMAP* ActeursM(int tx,int ty );// acteurs mechants


////structure////
t_acteur* constructeurActeur(int x,int y,int typ);//crée objet acteur
t_listeActeurs* creerListe(int maxi);//créer ancre
void testMort(t_listeActeurs* ancre);//test si etat=0 donc tue
void ajoutActeur(t_listeActeurs* ancre,int x,int y,int typ);//test si peut ajouter acteur et ajoute
t_intervenant* constructeurIntervenant(int x,int y,int typ);//creer objet intervenant
void ajoutIntervenant(t_listeActeurs* ancre,int x,int y,int typ);//test et ajoute intervenant
void detruireInter(t_listeActeurs* ancre);//permet de detruire tout les inter car bug
/////action////
void deplacementPersonnage(t_listeActeurs* ancre);
void tirPersonnage(t_listeActeurs* ancre);
void deplacementIntervenant(t_listeActeurs* ancre);
void Affichage (int *x,BITMAP*page, BITMAP* screen, t_listeActeurs* ancre);
void jeu();
#endif // PROTO_H_INCLUDED
