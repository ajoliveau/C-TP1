#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lireMessageEntree(char**, int);

int main(int argc, char* argv[])
{
    const TAILLE_BLOC = 128;

	int modeUtilisation = 0; // 1 = encryption, 2 = décryption
	int tailleEncodage = 0;
	char* message;

	int i;



	// Lecture et vérification des argumentsa
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

    lireMessageEntree(&message, TAILLE_BLOC);
    printf("%s\n", message);

	return 0;
}


void lireMessageEntree(char** messageARemplir, int tailleBloc) {
    int tailleMessageMax = tailleBloc;
    int tailleMessageActuel = 0;
    char carLu = '\n';
    char* message = malloc(tailleBloc);


    while ((carLu = getchar()) != '\n') {
        message[tailleMessageActuel] = (char) carLu;
        tailleMessageActuel++;

        if (tailleMessageActuel == tailleMessageMax) {
            tailleMessageMax += tailleBloc;
            message = realloc(message, tailleMessageMax);
        }
    }

    message[tailleMessageActuel] = '\0';
    printf("%s\n", message);
    messageARemplir = &message;
}
