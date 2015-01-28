#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_BLOC 128
#define CHAINE_CRYPTAGE "to be or not to be that is the question"

int decrypterMessage(char*, char**, int);
int encrypterMessage(char*, char**, int);
void lireMessageEntree(char**);
int convertirBinaireVersASCII (char*, int);
int convertirBinaireVersDecimal(char*);

int main(int argc, char* argv[])
{

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

    lireMessageEntree(&messageEntree);



    if (modeUtilisation == 1) {
        resultat = encrypterMessage(messageEntree, &messageTraite, tailleEncodage);
    } else {
        resultat = decrypterMessage(messageEntree, &messageTraite, tailleEncodage);
    }

    if (resultat == 1) {
        fprintf(stderr, "Erreur dans %s : Caractère non autorisé dans le message \n", argv[0]);
    }
    else if (resultat == 2) {
        fprintf(stderr, "Erreur dans %s : La taille du message ne correpond pas à l'encodage choisi \n", argv[0]);
    }
    else if (resultat == 3) {
        fprintf(stderr, "Erreur dans %s : L'encodage n'est pas correct pour ce message \n", argv[0]);
    }
    else {
        printf("%s\n", messageTraite);
    }


	return 0;
}


int encrypterMessage(char* messageEntree, char** messageTraite, int tailleEncodage) {
    return 0;
}

int decrypterMessage(char* messageEntree, char** messageTraite, int tailleEncodage) {
    int i;
    int j=0;
    int tailleMessageARenvoyer;
    int codeCaractereAscii;
    char codeBinaire[5];
    char* messageARenvoyer;

    for(i=0;i<strlen(messageEntree);i++) {
        if (messageEntree[i] >= 'a' && messageEntree[i] <= 'z') {
            messageEntree[j] = '0';
            j++;
        }
        else if (messageEntree[i] >= 'A' && messageEntree[i] <= 'Z') {
            messageEntree[j] = '1';
            j++;
        }
        else if (messageEntree[i] != ' ' && messageEntree[i]!= '\n') {
            return 1;
        }
    }
    messageEntree[j] = '\0';

    if ((strlen(messageEntree) % tailleEncodage) != 0) {
        return 2;
    }

    tailleMessageARenvoyer = strlen(messageEntree)/tailleEncodage;


    messageARenvoyer = malloc(tailleMessageARenvoyer*sizeof(char) + 1);
    messageARenvoyer[1] = 'a';
    messageARenvoyer[2] = '\0';

    for(i=0; i < tailleMessageARenvoyer;i++) {
        strncpy (codeBinaire, messageEntree, tailleEncodage);
        codeBinaire[5]= '\0';
        codeCaractereAscii = convertirBinaireVersASCII(codeBinaire, tailleEncodage);
        if (codeCaractereAscii == -1)
            return 3;
        messageARenvoyer[i] = (char) codeCaractereAscii;
        messageEntree += tailleEncodage;
    }
    messageARenvoyer[i] = '\0';
    *messageTraite = messageARenvoyer;

    return 0;

    
}

void lireMessageEntree(char** messageARemplir) {
    int tailleMessageMax = TAILLE_BLOC;
    int tailleMessageActuel = 0;
    char carLu = '\n';
    char* message = malloc(TAILLE_BLOC);


    while ((carLu = getchar()) != '\n') {
        message[tailleMessageActuel] = (char) carLu;
        tailleMessageActuel++;

        if (tailleMessageActuel == tailleMessageMax) {
            tailleMessageMax += TAILLE_BLOC;
            message = realloc(message, tailleMessageMax);
        }
    }

    message[tailleMessageActuel] = '\0';
    *messageARemplir = message;
}

int convertirBinaireVersASCII (char* codeBinaire, int tailleEncodage) {
    int valeurAscii;
    valeurAscii = convertirBinaireVersDecimal(codeBinaire);

    if (valeurAscii == 0) 
        return 32;
    
    if(tailleEncodage == 5) {
        if (valeurAscii>26)
            return -1 ;
        return valeurAscii+96;
    }

    return valeurAscii;    
}

int convertirBinaireVersDecimal(char* codeBinaire) {
    int valeurTotale = 0;
    int i;
    int puissanceDeDeux = 1;


    for (i = (strlen(codeBinaire) - 1); i>=0; i--) {
        if (codeBinaire[i] == '1') {
            valeurTotale += puissanceDeDeux;
        }
        puissanceDeDeux *= 2;
    }

    return valeurTotale;
}
