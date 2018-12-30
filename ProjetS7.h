#ifndef projets7
#define projets7
#include <stdbool.h>

typedef struct _noeudpoly{
	char  nom[17]  ;
	int longueurlogique;
	int*  routes;
	int*  km ;
	double latitude;
	double longitude;
	
	};
typedef  struct _noeudpoly  ville;
typedef struct element element;
struct element {
	int  cout;
	int  heuristique;
	int* villeparent;
	int* villeactuelle;
	struct element *bfr;
	struct element *nxt;
};
typedef  element* llist;
typedef struct integer integer;
struct integer {
	int  value;
	struct integer *bfr;
	struct integer *nxt;
};
typedef  integer* llistInt;
element* create_liste();
ville* creer_ville(int k,char name [],double latitude,double longitude);
double convertRad(double input);
double Distance(double lat_a_degre,double lon_a_degre,double lat_b_degre,double lon_b_degre);
double DistanceVille(ville* premiere,ville* seconde);
 llist inserer_en_queue(llist liste,element* city);
llist insertion_croissant(llist liste,element* city,int cout,int heuristique,ville* villeParent );
llist supprimer_dans_la_liste(llist liste,int  position);
bool recherche_element(llist liste,element* city);
int recherche_position_element(llist liste,ville* city);
element* retourne_position_element(llist liste,element* city);
llist astar(ville* initial,ville* destination,ville* villeInterdite);
int rechercheNbElement(llist list,element* e);
int choixVille(int valeurDejaChoisie);
void intialisation();
#endif
