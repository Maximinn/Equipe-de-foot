#include <iostream>
using namespace std;

const unsigned short TAILLE_NOM = 31;
const unsigned short TAILLE_PRENOM = 31;

const unsigned short MAX_NB_JOUEUR = 14;
const unsigned short NO_MAX = 100;
const unsigned short NO_MIN = 1;
const short PAS_TROUVER = -1;
const unsigned short ZERO = 0;

enum Menu {
	AJOUTER_JOUEUR = 1,
	MODIFIER_JOUEUR,
	RETIRER_JOUEUR,
	AFFICER_INFO_JOUEUR,
	AJOUTER_BUT,
	RETIRER_BUT,
	AFFICHER_JOUEUR_PAR_POSITION,
	TOTAL_BUT_EQUIPE,
	QUITTER
};

enum Position {
	GARDIEN_DE_BUT = 1,
	ATTAQUANT,
	DEFENSEUR,
	MILIEU_DE_TERRAIN,
	TOUTE_POSITION
};

struct joueur {
	unsigned short noDeJoueur;
	char nom[TAILLE_NOM];
	char prenom[TAILLE_PRENOM];
	unsigned short nbButs;
	Position position;
};

unsigned short afficherMenu();
void ajouterJoueur(joueur joueurs[], unsigned short &nbJoueurs);
int rechercherJoueur(joueur joueurs[], unsigned short nbJoueurs);
void modifierJoueur(joueur &joueur);
void retirerJoueur(joueur joueurs[], unsigned short &nbJoueurs, int indiceJoueurARetirer);
void afficherInfoJoueur(const joueur &JOUEUR);
void ajouterButJoueur(joueur &joueur);
void retirerButJoueur(joueur &joueur);
void afficherJoueursParPosition(joueur joueurs[], unsigned short nbJoueurs);
void afficherTotalDeButDeLEquipe(joueur joueurs[], unsigned short nbJoueurs);

//fonction suplementaire
void positionJoueur();
void detailJoueur(joueur &unjoueur);
joueur creeJoueur();
int validationShort();
int validationShort(unsigned short min, unsigned short max);
void validationChaine(char tabl[], unsigned short nbelement);
void verifierNumero(unsigned short &numero, joueur joueurs[], unsigned short nbJoueurs);

int main() {
	//À compléter
	joueur joueurs[MAX_NB_JOUEUR];
	unsigned short nbJoueur = ZERO;

	unsigned short option;

	do {
		system("cls");
		option = afficherMenu();
		system("cls");

		switch (option)
		{
		case AJOUTER_JOUEUR:
			ajouterJoueur(joueurs, nbJoueur);
			break;
		case MODIFIER_JOUEUR:
			modifierJoueur(joueurs[rechercherJoueur(joueurs, nbJoueur)]);
			break;
		case RETIRER_JOUEUR:
			retirerJoueur(joueurs, nbJoueur, rechercherJoueur(joueurs, nbJoueur));
			break;
		case AFFICER_INFO_JOUEUR:
			afficherInfoJoueur(joueurs[rechercherJoueur(joueurs, nbJoueur)]);
			system("pause");
			break;
		case AJOUTER_BUT:
			ajouterButJoueur(joueurs[rechercherJoueur(joueurs, nbJoueur)]);
			system("pause");
			break;
		case RETIRER_BUT:
			retirerButJoueur(joueurs[rechercherJoueur(joueurs, nbJoueur)]);
			system("pause");
			break;
		case AFFICHER_JOUEUR_PAR_POSITION:
			afficherJoueursParPosition(joueurs, nbJoueur);
			system("pause");
			break;
		case TOTAL_BUT_EQUIPE:
			afficherTotalDeButDeLEquipe(joueurs, nbJoueur);
			system("pause");
			break;
		}


	} while (option != QUITTER);
	return 0;
}

/*
	Tâche : fonction qui fait apparaitre un menu, demande de faire un
			choix à l'utilisateur, récupère ce choix et le retourne.
	Paramètre(s) : aucun
	Retour : Le choix effectué par l'utilisateur
*/
unsigned short afficherMenu() {
	//À compléter
	unsigned short choix;
	cout << "Choisissez la modification a apporter a l'equipe : " << endl;
	cout << "	-(" << Menu::AJOUTER_JOUEUR << ") Ajouter un joueur." << endl;
	cout << "	-(" << Menu::MODIFIER_JOUEUR << ") Modifier un joueur." << endl;
	cout << "	-(" << Menu::RETIRER_JOUEUR << ") Retirer un joueur." << endl;
	cout << "	-(" << Menu::AFFICER_INFO_JOUEUR << ") Afficher les informations d’un joueur selon son numéro de joueur." << endl;
	cout << "	-(" << Menu::AJOUTER_BUT << ") Ajouter un but à un joueur selon son numéro de joueur." << endl;
	cout << "	-(" << Menu::RETIRER_BUT << ") Retirer un but à un joueur selon son numéro de joueur." << endl;
	cout << "	-(" << Menu::AFFICHER_JOUEUR_PAR_POSITION << ") Afficher tous les joueurs(avec option de filtre)." << endl;
	cout << "	-(" << Menu::TOTAL_BUT_EQUIPE << ") Afficher le nombre total de buts comptés pour l’équipe." << endl;
	cout << "	-(" << Menu::QUITTER << ") Quitter l'application" << endl;
	cout << "Votre choix : ";
	choix = validationShort(AJOUTER_JOUEUR, QUITTER);
	return choix; // À remplacer car c'est seulement là pour que le code compile
}

/*
	Tâche : fonction qui sert à insérer UN SEUL nouveau joueur dans l'équipe. Demander une saisie pour chacune des informations d’un joueur, sauf pour le nombre de but, qui sera initialisé à 0 au moment de la création.
	Paramètre : un tableau de variable de type struct joueur
				le nombre de joueurs actuellement dans l'équipe
	Retour : aucun (sortie via les paramètres formels passés par adresse et/ou référence)
*/
//le nom et prénom des joueurs, son numéro de joueur, le nombre de buts marqués et sa position sur le terrain
void ajouterJoueur(joueur joueurs[], unsigned short &nbJoueurs) {
	//À compléter
	if (nbJoueurs < MAX_NB_JOUEUR) {
		joueurs[nbJoueurs] = creeJoueur();
		if (nbJoueurs > ZERO) {
			verifierNumero(joueurs[nbJoueurs].noDeJoueur, joueurs, nbJoueurs);
		}
		nbJoueurs++;
	}
	else {
		cout << "Effectif plein, suprimer un ou plusieurs joueurs pour en ajouter d'autre" << endl;
		system("pause");
	}
}

/*
	Tâche : fonction qui demande la saisie d'un numéro de joueur et
			cherche dans la liste des joueurs de l'équipe dans le
			but de retrouver ce joueur. Si le numéro du joueur saisi
			correspond au numéro d'un des joueurs de l'équipe, la
			fonction retourne l'indice ou se trouve le joueur dans
			le tableau, sinon la fonction affiche le message
			"Ce joueur n'existe pas" et retourne la valeur -1.
	Paramètre : un tableau de variable de type struct joueur
				le nombre de joueurs actuellement dans l'équipe
*/
int rechercherJoueur(joueur joueurs[], unsigned short nbJoueurs) {
	//À compléter
	unsigned short noJoueur;
	cout << "Entrez le numero du joueur rechercher : ";
	noJoueur = validationShort(NO_MIN, NO_MAX);

	short indice = PAS_TROUVER;
	int cpt = ZERO;
	while (cpt < nbJoueurs && indice == PAS_TROUVER) {
		if (joueurs[cpt].noDeJoueur == noJoueur) {
			indice = cpt;
		}
		cpt++;
	}
	if (indice == PAS_TROUVER) {
		cout << "Ce joueur n'existe pas" << endl;
	}
	system("cls");
	return indice; // À remplacer car c'est seulement là pour que le code compile 
}


/*
	Tâche : fonction qui permet de modifier les informations D'UN SEUL joueur
		 passé en paramètre. Les seules informations que vous pouvez modifier
		 pour un joueur sont le nom, le prénom et la
		 position. Vous ne devez pas permettre de modifier le nombre de buts et le
 numéro.
Paramètre : une référence d'un joueur.
*/
void modifierJoueur(joueur &joueur) {
	//À compléter
	cout << "Vous modifier le joueur numero : " << joueur.noDeJoueur << endl;
	detailJoueur(joueur);
}


/*
	Tâche : fonction qui retire un joueur du tableau en fonction
			de l'indice où se trouve le joueur dans le tableau.
	Paramètre : un tableau de variable de type struct joueur
				le nombre de joueurs actuellement dans l'équipe
				l'indice où se trouve joueur dans le tableau
	Retour : aucun (sortie via les paramètres formels passés par
			 adresse et/ou référence)
*/
void retirerJoueur(joueur joueurs[], unsigned short &nbJoueurs, int indiceJoueurARetirer) {
	//À compléter
	for (int i = indiceJoueurARetirer; i < nbJoueurs; i++) {
		joueurs[i] = joueurs[i + 1];
	}

	nbJoueurs--;

}

/*
	Tâche : fonction qui affiche les informations D'UN SEUL joueur
			passé en paramètre.
	Paramètre : une référence constante d'un joueur pour éviter tout
			 risque de modification du joueur dans la fonction.
	Retour : aucun (affichage seulement)
*/
void afficherInfoJoueur(const joueur &JOUEUR) {
	//À compléter
	cout << "Info du joueur numero : " << JOUEUR.noDeJoueur << endl;
	cout << "	Nom      : " << JOUEUR.nom << endl;
	cout << "	Prenom   : " << JOUEUR.prenom << endl;
	cout << "	Position : ";
	switch (JOUEUR.position)
	{
	case GARDIEN_DE_BUT:
		cout << "gardien de but" << endl;
		break;
	case ATTAQUANT:
		cout << "attaquant" << endl;
		break;
	case DEFENSEUR:
		cout << "deffenceur" << endl;
		break;
	case MILIEU_DE_TERRAIN:
		cout << "millieu de terrain" << endl;
		break;
	}
	if (JOUEUR.nbButs > 1) {
		cout << "	Buts     : " << JOUEUR.nbButs << endl;
	}
	else {
		cout << "	But      : " << JOUEUR.nbButs << endl;
	}

}

/*
	Tâche : fonction qui ajoute un but à un joueur passé par référence
			en paramètre.
	Paramètre : une référence d'un joueur
	Retour : aucun (sortie via les paramètres formels passés par
			 adresse et/ou référence)
*/
void ajouterButJoueur(joueur &joueur) {
	cout << "Vous avez ajouter un but au joueur numero : " << joueur.noDeJoueur << endl;
	joueur.nbButs++;
}

/*
	Tâche : fonction qui retire un but à un joueur passé par référence
			en paramètre. La fonction doit prévoir que le nombre de but
			ne pourra pas jamais être inférieur à 0.
	Paramètre : une référence d'un joueur
	Retour : aucun (sortie via les paramètres formels passés par
			 adresse et/ou référence)
*/
void retirerButJoueur(joueur &joueur) {
	//À compléter
	cout << "Vous avez retirer un but au joueur numero : " << joueur.noDeJoueur << endl;
	if (joueur.nbButs == ZERO) {
		cout << "Erreur, vous ne pouvez pas retirer de but a ce joueur" << endl;
	}
	else
	{
		joueur.nbButs--;
	}

}


/*
	Tâche : fonction qui affiche les joueurs de l'équipe après avoir
			demandé la saisie de la position à afficher. Aussi, ajouter
			une option permettant d'afficher tous les joueurs.
	Paramètre : un tableau de variable de type struct joueur
				le nombre de joueurs actuellement dans l'équipe
	Retour : aucun (affichage seulement)
*/
void afficherJoueursParPosition(joueur joueurs[], unsigned short nbJoueurs) {
	unsigned short choix;
	cout << "Choisissez la position sur le terrain" << endl;
	positionJoueur();
	cout << "	-(" << Position::TOUTE_POSITION << ") pour tout les joueurs" << endl;
	cout << "votre choix : ";
	choix = validationShort(GARDIEN_DE_BUT, TOUTE_POSITION);
	system("cls");
	for (int i = ZERO; i < nbJoueurs; i++) {

		if (choix == TOUTE_POSITION) {
			afficherInfoJoueur(joueurs[i]);

		}
		else if (joueurs[i].position == choix)
		{
			afficherInfoJoueur(joueurs[i]);

		}
	}
}

/*
	Tâche : fonction qui calcule et affiche le nombre total de but(s)
			marqué(s) pour toutes l'équipes.
	Paramètre : un tableau de variable de type struct joueur
				le nombre de joueurs actuellement dans l'équipe
	Retour : aucun (affichage seulement)
*/
void afficherTotalDeButDeLEquipe(joueur joueurs[], unsigned short nbJoueurs) {
	//À compléter
	unsigned int totalBut = ZERO;
	for (int i = ZERO; i < nbJoueurs; i++) {
		totalBut += joueurs[i].nbButs;
	}
	cout << "L'equipes a marquer " << totalBut << " but";
	(totalBut > 1) ? (cout << "s") : (cout << "");
	cout << "." << endl;
}

void positionJoueur()
{
	cout << "	-(" << Position::GARDIEN_DE_BUT << ") pour gardien de but" << endl;
	cout << "	-(" << Position::ATTAQUANT << ") pour attaquant" << endl;
	cout << "	-(" << Position::DEFENSEUR << ") pour deffenseur" << endl;
	cout << "	-(" << Position::MILIEU_DE_TERRAIN << ") pour milieu de terrain" << endl;
}

void detailJoueur(joueur &unjoueur)
{
	cout << "entrez le nom du joueur : ";
	validationChaine(unjoueur.nom, TAILLE_NOM);

	cout << "entrez le prenom du joueur : ";
	validationChaine(unjoueur.prenom, TAILLE_PRENOM);

	unsigned short position;
	cout << "entrez la position du joueur sur le terrain : " << endl;
	positionJoueur();
	cout << "votre choix : ";
	position = validationShort(Position::GARDIEN_DE_BUT, Position::MILIEU_DE_TERRAIN);
	unjoueur.position = (Position)position;
}

joueur creeJoueur()
{
	joueur unjoueur;
	unjoueur.nbButs = ZERO;

	cout << "entrez le numero du joueur : ";
	unjoueur.noDeJoueur = validationShort(NO_MIN, NO_MAX);

	detailJoueur(unjoueur);
	return unjoueur;
}

int validationShort()
{
	int valeur;
	cin >> valeur;
	while (cin.fail() || cin.peek() != '\n' || valeur < ZERO || valeur > USHRT_MAX) {
		cin.clear();
		cin.ignore(512, '\n');

		cout << "Valeur invalide : ";
		cin >> valeur;
	}
	cin.ignore(512, '\n');
	return valeur;

}

int validationShort(unsigned short min, unsigned short max)
{
	int valeur;
	valeur = validationShort();
	while (valeur < min || valeur > max) {
		cout << "Valeur entre " << min << " et " << max << " inclusivement seulement : ";
		valeur = validationShort();
	}
	return valeur;
}

void validationChaine(char tabl[], unsigned short nbelement)
{
	cin.getline(tabl, nbelement);
	while (cin.fail()) {
		cin.clear();
		cin.ignore(512, '\n');

		cout << "erreur, entrez (" << nbelement + PAS_TROUVER << " caractere max) : ";
		cin.getline(tabl, nbelement);

	}
}

void verifierNumero(unsigned short &numero, joueur joueurs[], unsigned short nbJoueurs)
{
	short indice;
	int cpt;
	do {
		cpt = ZERO;
		indice = PAS_TROUVER;
		while (cpt < nbJoueurs && indice == PAS_TROUVER) {
			if (joueurs[cpt].noDeJoueur == numero) {
				indice = cpt;
			}
			cpt++;
		}
		if (indice != PAS_TROUVER) {
			cout << "le numero choisi est deja attribuer a un autre joueur : ";
			numero = validationShort(NO_MIN, NO_MAX);
		}

	} while (indice != PAS_TROUVER);
}
