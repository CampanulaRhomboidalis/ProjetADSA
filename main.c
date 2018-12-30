#include <stdio.h>
#include <stdlib.h>
#include "projets7.h"
#include <stdbool.h>
#include <math.h>
int main(int argc, char **argv){
	
	char reponse='O';
	while(reponse!='N')
	{
	intialisation();
	printf("\n\nEntrez N to exit \n");
	scanf(" %c", &reponse);
	}
		return 0;
}
