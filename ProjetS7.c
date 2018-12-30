#include <stdlib.h>
#include "projets7.h"
#include <stdio.h>

float pi =3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f;
ville* creer_ville(int k,char name [],double latitude,double longitude){
	ville* n = (ville*) malloc(sizeof(ville));

	if(name!=NULL){		
	strcpy(&n->nom,name);
	}
	else{
		strcpy(&n->nom,"defaut_name");
	}
	n->latitude=latitude;
	n->longitude=longitude;
	n->longueurlogique=k;
	n->routes=(ville*) malloc(k*sizeof(ville*));
	n->km=(int) malloc(k*sizeof(int));
		for(int i = 0;i<k;i++){
			n->km[i]=0;
			n->routes[i]=0;
		}
	return n;
}
double convertRad(double input){
	        return ((pi * input)/180);
}
 double Distance(double lat_a_degre,double lon_a_degre,double lat_b_degre,double lon_b_degre){
     
	int R = 6371; //Rayon  moyen de la terre en km (UGGI)
	double lat_a = convertRad(lat_a_degre);
	double lon_a = convertRad(lon_a_degre);
	double lat_b = convertRad(lat_b_degre);
	double lon_b = convertRad(lon_b_degre);
	double value=R * (pi/2 - asin( sin(lat_b) * sin(lat_a) + cos(lon_b - lon_a) * cos(lat_b) * cos(lat_a)));
	return value ;
}
double DistanceVille(ville* premiere,ville* seconde){

	int R = 6371; //Rayon  moyen de la terre en km (UGGI)
	double lat_a = convertRad(premiere->latitude);
	double lon_a = convertRad(premiere->longitude);
	double lat_b = convertRad(seconde->latitude);
	double lon_b = convertRad(seconde->longitude);
	 double value=(R * (pi/2 - asin( sin(lat_b) * sin(lat_a) + cos(lon_b - lon_a) * cos(lat_b) * cos(lat_a))));
	 return value;
}
element * create_liste(){
	
	element* v=(element*)malloc(sizeof(element));
	v->cout=0;
	v->bfr=NULL;
	v->nxt=NULL;
	v->villeactuelle=NULL;
	v->villeparent=NULL;
	v->heuristique=0;
		return v;
 }
llist inserer_en_queue(llist liste,element* city){
	element* nouvelElement = malloc(sizeof(element));
	nouvelElement->cout = city->cout;
	nouvelElement->heuristique = city->heuristique;
	nouvelElement->villeactuelle=city->villeactuelle;
	nouvelElement->bfr=NULL;
	nouvelElement->nxt=NULL;
	nouvelElement->villeparent=city->villeparent;
    if(liste->heuristique == 0&&liste->cout ==0 )
    {
  return nouvelElement;
    }
    else
    {
        
        element* temp=liste;
        while(temp->nxt != NULL)
        {
            temp = temp->nxt;
        }
        temp->nxt = nouvelElement;
		nouvelElement->bfr=temp;

		//mauvaise attribution dans  bfr et ça beug
		 while(temp->bfr != NULL)
        {
            temp = temp->bfr;
        }
        return temp;
    }
}
llist insertion_croissant(element* liste,element* city,int cout,int heuristique,ville* villeparent ){
	element* nouvelElement = (element*)malloc(sizeof(element));
	element* temptransition = (element*)malloc(sizeof(element));
	nouvelElement->cout = cout;
	nouvelElement->heuristique = heuristique;
	nouvelElement->villeactuelle=city->villeactuelle;
	nouvelElement->villeparent=villeparent;
	nouvelElement->nxt=NULL;
	nouvelElement->bfr=NULL;
	bool condition=true;
    if(liste == NULL)
    {
  return nouvelElement;
    }
    else
    {
         temptransition=liste;
        element* temp=liste;
        while(condition)
        {	if((nouvelElement->cout+nouvelElement->heuristique)<=(temp->heuristique+temp->cout)&&temp->bfr!=NULL){
			nouvelElement->villeactuelle=city->villeactuelle;
			nouvelElement->nxt=temp;
			nouvelElement->bfr=temp->bfr;
			temptransition=temp->bfr;
			temptransition->nxt=nouvelElement;
			temp->bfr=nouvelElement;
			condition=false;
			  
			}
				if((nouvelElement->cout+nouvelElement->heuristique)<=(temp->heuristique+temp->cout)&&temp->bfr==NULL){
			nouvelElement->nxt=temp;
			nouvelElement->villeactuelle=city->villeactuelle;
			nouvelElement->bfr=NULL;
			temp->bfr=nouvelElement;
			condition=false;
			liste=nouvelElement;
			  
				}
			 if(temp->nxt == NULL&&condition){
				 temp->nxt= nouvelElement;
				 nouvelElement->bfr=temp;
				 nouvelElement->nxt=NULL;
				 condition=false;
			 }
				if(temp->nxt != NULL){
				temp = temp->nxt;
				}
           
        }
        return liste;
    }
}
llist supprimer_en_tete(llist liste){
	if(liste->nxt!=NULL){		
		liste->nxt->bfr=NULL;
		element* nouvelElement = malloc(sizeof(element));
		return liste->nxt;
		liste=NULL;
		free(liste);
		
	}
}
llist supprimer_dans_la_liste(llist liste,int position){
	element* temp=liste;
	int pos=0;
	while (temp!=NULL&&pos!=position){
		temp=temp->nxt;
		pos++;
	}
	
	element* tempbfr=(element*)malloc(sizeof(element));
	tempbfr=NULL;
	 if(temp->bfr!=NULL)
	{tempbfr=temp->bfr;}
	else{
		// faut renvoyer en void le second élément et couper le before du second élément
	temp=temp->nxt;
	temp->bfr->nxt=NULL;
	temp->bfr=NULL;
	}
	element* tempaftr=(element*)malloc(sizeof(element));
	tempaftr=NULL;
	 if(temp->nxt!=NULL)
	{ tempaftr=temp->nxt;}
	 if(temp->bfr!=NULL){
		 tempbfr->nxt=tempaftr;
	 }
	  if(temp->nxt!=NULL){
	tempaftr->bfr=temp;
	  }
	  while (temp->bfr!=NULL){
		temp=temp->bfr;
		}
	  return temp;
}
bool recherche_element(llist liste,element* city){
	bool condition=true;
	
	ville* villeParcourue;
	ville* villeARajouter=city->villeactuelle; 

	      while(liste!= NULL&&condition)
        {
			villeParcourue=liste->villeactuelle;
			if(villeParcourue->longitude==villeARajouter->longitude&& villeARajouter->latitude==villeParcourue->latitude)
			{
				condition=false;
			}
			if(condition){				
			liste=liste->nxt;
			}
		} 
		
		return !condition;
}
int recherche_position_element(llist liste,ville* city){
	bool condition=true;
	int value=-1;
	element* temp=liste;
	      while(temp!= NULL&&condition)
        {
			if(temp->villeactuelle==city){				
				condition=false;
				}
			temp = temp->nxt;
		 value++;
					}
		return value;
}
bool NoeudBut(element* NoeudTeste,ville* villeDestination){
	bool EstDestination=false;
	ville* villeTest=NoeudTeste->villeactuelle;
	if(villeTest->latitude==villeDestination->latitude&&villeTest->longitude==villeDestination->longitude){
		EstDestination=true;
	}
	return EstDestination;
}
element* retourne_position_element(llist liste,element* city){
	bool condition=true;
	element* temp=liste;
	ville* villetemp;
	ville *perm=city->villeactuelle;
	      while(temp!= NULL&&condition)
        {
			villetemp=temp->villeactuelle;
			if(villetemp->latitude==perm->latitude&&villetemp->longitude==perm->longitude){				
				condition=false;
				}
			if(condition)
				{				
				temp = temp->nxt;
				}

			 }
		return temp;
}
llist astar(ville* initial,ville* destination,ville* villeInterdite){
	ville* n =NULL;
	ville* nprim = NULL;
	llist open=create_liste();
	llist closed=create_liste();
	closed->bfr=NULL;
	closed->nxt=NULL;
	bool condition=true;
	element* nouvelElement = malloc(sizeof(element));
	open->heuristique=DistanceVille(initial,destination);
	open->villeactuelle=initial;
	open->cout=0;
	open->villeparent=0;
	open->bfr=NULL;
	open->nxt=NULL;
	while(condition){
		if(open==NULL){	
			condition=false; 
			// Graph vide  
		}
		ville* tempville = (ville*) malloc(sizeof(ville));
		n=open->villeactuelle;
		tempville=open->villeactuelle;
		//printf("\n Noeud courant :  %s",tempville->nom);	
		if(open->heuristique == 0){
			condition =false;
			//but  atteint 
			closed=inserer_en_queue(closed,open);	
		}
		else{
			ville* villetemp ;
			closed=inserer_en_queue(closed,open);					
				
			for(int i =0;i<n->longueurlogique;i++)
			{
				nouvelElement->cout=n->km[i]+open->cout;
				villetemp=n->routes[i];
				nouvelElement->villeparent=n;
				nouvelElement->villeactuelle=n->routes[i];
				
				nouvelElement->heuristique= DistanceVille(nouvelElement->villeactuelle,destination);				
				nouvelElement->nxt=NULL;
				nouvelElement->bfr=open;
				
				if(villeInterdite != nouvelElement->villeactuelle){		
					//printf("\n parcour du fils    : %s ",villetemp->nom);	
					element* temp=(element*)malloc(sizeof(element));
					temp= NULL;
					bool PresentDansOpen=false;
					bool PresentDansClose=false;
					bool presence=true;
				
					PresentDansOpen=recherche_element(open,nouvelElement);
					PresentDansClose=recherche_element(closed,nouvelElement);
				
				
					if( PresentDansOpen&&presence)
					{ 
					//printf("\n noeud déjà présent dans open    %d");
					temp= retourne_position_element(open,nouvelElement);
					if((nouvelElement->cout+nouvelElement->heuristique)<=(temp->heuristique+temp->cout)){
					
						int value =recherche_position_element(open,nouvelElement->villeactuelle);
						open =supprimer_dans_la_liste(open,value);				
						open=insertion_croissant(open,nouvelElement,nouvelElement->cout,nouvelElement->heuristique,n);
						presence=false;
						}
					}
					if( PresentDansClose&&presence)
					{
					temp= retourne_position_element(open,nouvelElement);
					if((nouvelElement->cout+nouvelElement->heuristique)<=(open->heuristique+open->cout)){
						int value =recherche_position_element(closed,nouvelElement->villeactuelle);
						closed =supprimer_dans_la_liste(closed,value);
						closed=inserer_en_queue(closed,nouvelElement);
						presence=false;
					}
					
					}
					if(!PresentDansOpen&&!PresentDansClose&&presence)
					{	
					open=insertion_croissant(open,nouvelElement,nouvelElement->cout,nouvelElement->heuristique,n);
					//printf("\n ajout de la ville %s dans open   ",villetemp->nom);
					} 
				}
			}
			int value =recherche_position_element(open,n);
			open =supprimer_dans_la_liste(open,value);
		}
	}
	closed=inserer_en_queue(closed,nouvelElement);	
	
	
ville* parcour ;
printf("\nTrajet %s  <----> %s ",initial->nom,destination->nom);

element* trajetFinal=NULL;
element* debutListe=closed;
ville* villeTemps=destination;
ville* nomvilleactuelle;
while(villeTemps!=initial){	
	while(closed->villeactuelle!=villeTemps)
	{
		closed=closed->nxt;
	}
	nomvilleactuelle=closed->villeactuelle;
	parcour=closed->villeparent;
	//printf("\n %s   en  %d  km  avec pour ville parent  %s ",nomvilleactuelle->nom,solution->cout,parcour->nom);
	villeTemps=parcour;
	element* noeudcourant=(element*)malloc(sizeof(element));
	noeudcourant->bfr=NULL;	
	noeudcourant->nxt=trajetFinal;
	if(noeudcourant->nxt!=NULL){
		noeudcourant->nxt->bfr=noeudcourant;
	}
	noeudcourant->cout=closed->cout;
	noeudcourant->heuristique=closed->heuristique;
	noeudcourant->villeactuelle=closed->villeactuelle;
	noeudcourant->villeparent=closed->villeparent; 
	trajetFinal=noeudcourant;
	closed=debutListe;
}
if(closed->villeactuelle==villeTemps){
	element* noeudcourant=(element*)malloc(sizeof(element));
	noeudcourant->bfr=NULL;
	noeudcourant->nxt=trajetFinal;
	if(noeudcourant->nxt!=NULL){
		noeudcourant->nxt->bfr=noeudcourant;
	}
	noeudcourant->cout=closed->cout;
	noeudcourant->heuristique=closed->heuristique;
	noeudcourant->villeactuelle=closed->villeactuelle;
	noeudcourant->villeparent=closed->villeparent; 
	trajetFinal=noeudcourant;	
}	
	return trajetFinal ;
}
int rechercheNbElement(llist list,element* e){
	int compteur =0 ;
	while(list!=NULL){
		if( list->villeparent== e->villeactuelle){
			compteur++;
		}
		list=list->nxt;
	}
}
int choixVille(int valeurDejaChoisie){
	bool condition =true;
	while(condition){
	 int n=-1;
	 if(valeurDejaChoisie==-1){
    printf("\nEntrez un entier entre 0 et 31: ");
	 }
	 else{
		 printf("\nEntrez un entier entre  0 et 31  et pas %d: ",valeurDejaChoisie);
	 }
	 
		while(scanf("%d",&n) != 1)
    {	n=NULL;
        printf("\nEntrez un entier entre 0 et 31:");
        while(getchar() != '\n');
    }
	
	if(n>-1&&n<32&&n!=valeurDejaChoisie){
		condition=false;
		return n ;
	}	
	printf("Saisi: %d\n",n);
	}
    
}
void intialisation(){
 //debut de la creation du graph
	ville* avignon = creer_ville(3,"avignon",43.949317,4.805528);
	ville* amiens = creer_ville(5,"amiens",49.894067,2.295753);
	ville* angers = creer_ville(3,"angers",47.471162,-0.551826);
	ville* bordeaux = creer_ville(4,"bordeaux",44.837789,-0.57918);
	ville* bayonne = creer_ville(2,"bayonne",43.492949,-1.474841);
	ville* besancon = creer_ville(2,"besancon",47.237829,6.024054);
	ville* calais = creer_ville(2,"calais",50.95129,1.858686);
	ville* caen = creer_ville(2,"caen",49.182863,-0.370679);
	ville* clermontferrand = creer_ville(5,"clermontferrand",45.777222,3.087025);
	ville* dunkerque = creer_ville(2,"dunkerque",51.034368,2.376776);
	ville* dijon = creer_ville(3,"dijon",47.322047,5.04148);
	ville* laRochelle = creer_ville(2,"la rochelle",46.160329,-1.151139);
	ville* leMans = creer_ville(3,"le mans",48.00611,0.199556);
	ville* lille = creer_ville(3,"lille",50.62925,3.057256);
	ville* lyon = creer_ville(3,"lyon",45.764043,4.835659);
	ville* marseille = creer_ville(3,"marseille",43.296482,5.36978);
	ville* montpellier = creer_ville(3,"montpellier",43.610769,3.876716);
	ville* nancy = creer_ville(3,"nancy",48.692054,6.184417);
	ville* nantes = creer_ville(2,"nantes",47.218371,-1.553621);
	ville* metz= creer_ville(5,"metz",49.119309,6.175716);
	ville* nimes = creer_ville(3,"nimes",43.836699,4.360054);
	ville* nice = creer_ville(1,"nice",43.710173,7.261953);
	ville* orleans = creer_ville(3,"orleans",47.902964,1.909251);	
	ville* paris = creer_ville(6,"paris",48.862725,2.87592);
	ville* perpignan = creer_ville(2,"perpignan",42.688659,2.894833);
	ville* poitiers = creer_ville(2,"perpignan",46.580224,0.340375);
	ville* rennes = creer_ville(2,"rennes",48.117266,-1.677793);
	ville* rouen = creer_ville(4,"rouen",49.443232,1.099971);	
	ville* strasbourg = creer_ville(3,"strasbourg",48.573405,7.752111);
	ville* toulouse = creer_ville(4,"toulouse",43.604652,1.444209);
	ville* tours =creer_ville(4,"tours",47.394144,0.68484);
	ville* troyes= creer_ville(3,"troyes",48.297345,4.074401);


	amiens->routes[0]=rouen;
	amiens->km[0]=119;
	amiens->routes[1]=paris;
	amiens->km[1]=143;
	amiens->routes[2]=metz;
	amiens->km[2]=367;
	amiens->routes[3]=calais;
	amiens->km[3]=160;
	amiens->routes[4]=lille;
	amiens->km[4]=130;
	
	avignon->routes[0]=lyon;
	avignon->km[0]=229;
	avignon->routes[1]=marseille;
	avignon->km[1]=105;
	avignon->routes[2]=nimes;
	avignon->km[2]=45;
	
	angers->routes[0]=leMans;
	angers->km[0]=96;
	angers->routes[1]=tours;
	angers->km[1]=127;	
	angers->routes[2]=nantes;
	angers->km[2]=92;
	
	bayonne->routes[0]=toulouse;
	bayonne->km[0]=297;
	bayonne->routes[1]=bordeaux;
	bayonne->km[1]=185;
	
	besancon->routes[0]=dijon;
	besancon->km[0]=93;
	besancon->routes[1]=strasbourg;
	besancon->km[1]=243;
	
	bordeaux->routes[0]=toulouse;
	bordeaux->km[0]=245;
	bordeaux->routes[1]=poitiers;
	bordeaux->km[1]=251;
	bordeaux->routes[2]=laRochelle;
	bordeaux->km[2]=184;
	bordeaux->routes[3]=bayonne;
	bordeaux->km[3]=185;
	
	caen->routes[0]=rennes;
	caen->km[0]=185;
	caen->routes[1]=rouen;
	caen->km[1]=131;
	
	calais->routes[0]=dunkerque;
	calais->km[0]=45;
	calais->routes[1]=amiens;
	calais->km[1]=160;


clermontferrand->routes[0]=toulouse;
clermontferrand->km[0]=376;
clermontferrand->routes[1]=tours;
clermontferrand->km[1]=339;
clermontferrand->routes[2]=montpellier;
clermontferrand->km[2]=332;
clermontferrand->routes[3]=lyon;
clermontferrand->km[3]=165;
clermontferrand->routes[4]=orleans;
clermontferrand->km[4]=300;

dijon->routes[0]=lyon;
dijon->km[0]=196;
dijon->routes[1]=troyes;
dijon->km[1]=188;
dijon->routes[2]=besancon;
dijon->km[2]=93;

	
	dunkerque->routes[0]=calais;
	dunkerque->km[0]=45;
	dunkerque->routes[1]=lille;
	dunkerque->km[1]=80;
	
	laRochelle->routes[0]=nantes;
	laRochelle->km[0]=138;
	laRochelle->routes[1]=bordeaux;
	laRochelle->km[1]=184;

	leMans->routes[0]=paris;
	leMans->km[0]=209;
	leMans->routes[1]=rouen;
	leMans->km[1]=211;
	leMans->routes[2]=nantes;
	leMans->km[2]=92;
	
	lille->routes[0]=metz;
	lille->km[0]=393;
	lille->routes[1]=amiens;
	lille->km[1]=130;
	lille->routes[2]=dunkerque;
	lille->km[2]=80;
	
	lyon->routes[0]=avignon;
	lyon->km[0]=229;
	lyon->routes[1]=clermontferrand;
	lyon->km[1]=165;
	lyon->routes[2]=dijon;
	lyon->km[2]=196;
	
	marseille->routes[0]=nice;
	marseille->km[0]=199;
	marseille->routes[1]=nimes;
	marseille->km[1]=122;
	marseille->routes[2]=avignon;
	marseille->km[2]=105;
	
	metz->routes[0]=lille;
	metz->km[0]=393;
	metz->routes[1]=paris;
	metz->km[1]=331;
	metz->routes[2]=strasbourg;
	metz->km[2]=166;
	metz->routes[3]=nancy;
	metz->km[3]=59;
	metz->routes[4]=amiens;
	metz->km[4]=367;
	
	montpellier->routes[0]=clermontferrand;
	montpellier->km[0]=332;
	montpellier->routes[1]=perpignan;
	montpellier->km[1]=157;
	montpellier->routes[2]=nimes;
	montpellier->km[2]=56;
	
	nantes->routes[0]=laRochelle;
	nantes->km[0]=138;
	nantes->routes[1]=angers;
	nantes->km[1]=92;
	
	nancy->routes[0]=troyes;
	nancy->km[0]=209;
	nancy->routes[1]=metz;
	nancy->km[1]=59;
	nancy->routes[2]=strasbourg;
	nancy->km[2]=150;
	
	nimes->routes[0]=avignon;
	nimes->km[0]=45;
	nimes->routes[1]=montpellier;
	nimes->km[1]=56;
	nimes->routes[2]=marseille;
	nimes->km[2]=122;
	
	nice->routes[0]=marseille;
	nice->km[0]=199;
	
	orleans->routes[0]=paris;
	orleans->km[0]=133;
	orleans->routes[1]=clermontferrand;
	orleans->km[1]=300;
	orleans->routes[2]=tours;
	orleans->km[2]=124;
	
	paris->routes[0]=leMans;
	paris->km[0]=209;
	paris->routes[1]=troyes;
	paris->km[1]=183;
	paris->routes[2]=orleans;
	paris->km[2]=133;
	paris->routes[3]=rouen;
	paris->km[3]=138;
	paris->routes[4]=amiens;
	paris->km[4]=143;
	paris->routes[5]=metz;
	paris->km[5]=331;
	
	poitiers->routes[0]=tours;
	poitiers->km[0]=105;
	poitiers->routes[1]=bordeaux;
	poitiers->km[1]=251;
	
	perpignan->routes[0]=montpellier;
	perpignan->km[0]=157;
	perpignan->routes[1]=toulouse;
	perpignan->km[1]=217;
	
	rennes->routes[0]=caen;
	rennes->km[0]=185;
	rennes->routes[1]=nantes;  
	rennes->km[1]	=251;
	
	rouen->routes[0]=paris;
	rouen->km[0]=138;
	rouen->routes[1]=caen;
	rouen->km[1]=131;
	rouen->routes[2]=leMans;
	rouen->km[2]=211;
	rouen->routes[3]=amiens;
	rouen->km[3]=119;
	
	strasbourg->routes[0]=metz;
	strasbourg->km[0]=166;
	strasbourg->routes[1]=nancy;
	strasbourg->km[1]=150;
	strasbourg->routes[2]=besancon;
	strasbourg->km[2]=243;
	
	toulouse->routes[0]=clermontferrand;
	toulouse->km[0]=376;
	toulouse->routes[1]=bordeaux;
	toulouse->km[1]=245;
	toulouse->routes[2]=bayonne;
	toulouse->km[2]=297;
	toulouse->routes[3]=perpignan;
	toulouse->km[3]=217;
	
	tours->routes[0]=clermontferrand;
	tours->km[0]=339;
	tours->routes[1]=orleans;
	tours->km[1]=124;
	tours->routes[2]=angers;
	tours->km[2]=127;
	tours->routes[3]=poitiers;
	tours->km[3]=105;
	
	troyes->routes[0]=paris;
	troyes->km[0]=183;
	troyes->routes[1]=nancy;
	troyes->km[1]=249;
	troyes->routes[2]=dijon;
	troyes->km[2]=188;

//fin de la creation du graph

//creation du tableau permettant de lier le choix de l'utilisateur et la ville 
	int* tabVille=(int*)malloc(32*sizeof(int));
	tabVille[0]=avignon;
	tabVille[1]=amiens;
	tabVille[2]=angers;
	tabVille[3]=bordeaux;
	tabVille[4]=bayonne;
	tabVille[5]=besancon;
	tabVille[6]=calais;
	tabVille[7]=caen;
	tabVille[8]=clermontferrand;
	tabVille[9]=dunkerque;
	tabVille[10]=dijon;
	tabVille[11]=laRochelle;
	tabVille[12]=leMans;
	tabVille[13]=lille;
	tabVille[14]=lyon;
	tabVille[15]=marseille;
	tabVille[16]=montpellier;
	tabVille[17]=nancy;
	tabVille[18]=nantes;
	tabVille[19]=metz;
	tabVille[20]=nimes;
	tabVille[21]=nice;
	tabVille[22]=orleans;
	tabVille[23]=paris;
	tabVille[24]=perpignan;
	tabVille[25]=poitiers;
	tabVille[26]=rennes;
	tabVille[27]=rouen;
	tabVille[28]=strasbourg;
	tabVille[29]=toulouse;
	tabVille[30]=tours;
	tabVille[31]=troyes;
	
// affichage des villes disponibles 
	for(int i =0;i<32;i++){
	ville* test=tabVille[i];
	printf("\n%d  :  %s ",i, test->nom);	
	}
	printf("\n");

//choix des villes 
	printf("\nVeuillez choisir la ville de depart");	
	int villeDepartIndex =choixVille(-1);	
	printf("\nVeuillez choisir la ville d'arrivee");	
	int villeArriveeIndex =choixVille(villeDepartIndex);
	
	ville* villeDepart=tabVille[villeDepartIndex];
	ville* villeArrivee=tabVille[villeArriveeIndex];
	printf("\n choix de la ville de depart :  %s", villeDepart->nom);	
	printf("\n choix de la ville d'arrivee %s", villeArrivee->nom);
	printf("\n");
	
element* solution=(element*)malloc(sizeof(element));
//ASTAR
solution=astar(villeDepart,villeArrivee,NULL);

//affichage de la solution initale 
ville* parcour;
ville* nomvilleactuelle;
element * positionInitial=solution;
int valeurMin=-1;
printf("\n Solution intiale");
printf("\n Le trajet  pour  aller de %s a %s est  :\n",villeDepart->nom,villeArrivee->nom) ;

while(solution!=NULL){
 parcour=solution->villeparent;
 nomvilleactuelle=solution->villeactuelle;
printf("%s    ",nomvilleactuelle->nom );
	if(solution->nxt==NULL){
		printf("\n Cout total de la solution  en  %d  km \n",solution->cout);
		valeurMin=solution->cout;
	}
solution=solution->nxt;
}
solution=positionInitial;
 
 
//affichage des solutions alternatives avec la possibilite de redondance
int indexSolution=1;
while(solution!=NULL){	 
	 if(solution->villeactuelle!=villeDepart&&solution->villeactuelle!=villeArrivee){
		 element* autreSolution=(element*)malloc(sizeof(element));
		autreSolution=astar(villeDepart,villeArrivee,solution->villeactuelle);	
		printf("\n\n Solution alternative  %d",indexSolution);
		indexSolution++;
			while(autreSolution!=NULL)
			{	
				parcour=autreSolution->villeparent;
				nomvilleactuelle=autreSolution->villeactuelle;			
				printf("\n %s   en  %d  km ",nomvilleactuelle->nom,autreSolution->cout);
				if(autreSolution->nxt==NULL){
					double coutSolution= ((double)autreSolution->cout/valeurMin)-1;
					printf("\n Cout suplementaire de cette solution en poucentage %lg   \n",coutSolution*100);
				}
				autreSolution=autreSolution->nxt;
			}
			
	 }

	 solution=solution->nxt;
 }
}