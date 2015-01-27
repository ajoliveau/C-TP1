#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int modeUtilisation = 0; // 1 = encryption, 2 = décryption
	int tailleEncodage = 0;
	char *message;
	int i;



	// Lecture et vérification des arguments
	if (argc != 3) {
		fprintf(stderr, "Erreur dans %s : Nombre d'arguments invalides\n", argv[0]);
		exit(1);
	}

	for (i=1;i<3;i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
				case 'e' :
					modeUtilisation = 1;
					break;
				case 'd' :					
					modeUtilisation = 2;
					break;
				case 't' :
					sscanf(argv[i], "-taille=%d", &tailleEncodage);
			}
		}
	}
	if (modeUtilisation == 0) { // Si modeUtilisation garde sa valeur par défaut, -e ou -d n'ont pas été spécifiés
		fprintf(stderr, "Erreur dans %s : Mode d'utilisation (encodage ou décodage) non spécifié\n", argv[0]);
	}
	if (tailleEncodage == 0) {	// Si tailleEncodage garde sa valeur par défaut, -taille= n'a pas été spécifié
		fprintf(stderr, "Erreur dans %s : Taille d'encodage non spécifiée\n", argv[0]);
		exit(2);
	}


	//scanf("%s", message);

	//printf("Message : %s \n", message);






	return 0;
}