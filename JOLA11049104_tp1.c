#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lireMessageEntree(char**, int);
int decrypterMessage(char*, char**, int);
int encrypterMessage(char*, char**, int);

int main(int argc, char* argv[])
{
    const TAILLE_BLOC = 128;

	int modeUtilisation = 0; // 1 = encryption, 2 = décryption
	int tailleEncodage = 0;

	char* messageEntree;
	char* messageTraite;

    int resultat = 0;

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
	if (tailleEncodage != 5 && tailleEncodage != 7 && tailleEncodage != 8) {
        fprintf(stderr, "Erreur dans %s : Taille d'encodage incorrecte (5 ou 7 ou 8 seulement)\n", argv[0]);
		exit(3);
	}

    lireMessageEntree(&messageEntree, TAILLE_BLOC);



    if (modeUtilisation == 1) {
        resultat = encrypterMessage(messageEntree, &messageTraite, tailleEncodage);
    } else {
        resultat = decrypterMessage(messageEntree, &messageTraite, tailleEncodage);
    }

    printf("%d\n", resultat);


	return 0;
}


int encrypterMessage(char* messageEntree, char** messageTraite, int tailleEncodage) {
    return 0;
}

int decrypterMessage(char* messageEntree, char** messageTraite, int tailleEncodage) {
    int i;
    int j=0;

    for(i=0;i<strlen(messageEntree);i++) {
        if (messageEntree[i] >= 'a' && messageEntree[i] <= 'z') {
            messageEntree[j] = '0';
            j++;
        }
        else if (messageEntree[i] >= 'A' && messageEntree[i] <= 'Z') {
            messageEntree[j] = '1';
            j++;
        }
        else if (messageEntree[i] != ' ') {
            return 2;
        }
    }
    messageEntree[j] = '\0';

    printf("%s\n", messageEntree);
    if ((strlen(messageEntree) % tailleEncodage) != 0) {
        return 1;
    }
;
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
    *messageARemplir = message;
}
