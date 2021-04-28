/*  
	BUT : CE FICHIER D'EN-TÊTE PERMET DE GARDER LES STRUCTURES,LES CONSTANTES ET LES VARIABLES GLOBALES POUR QU'ELLES SOIENT APPELÉS DANS LES AUTRES FICHIERS 
*/
#pragma once 

#include <windows.h>

using namespace std;

// LES CONSTANTES DU PROGRAMMES 
const int Longeur_NoCivique = 9, Longeur_Rue = 31, Longeur_Ville = 31, Longeur_CodeP = 8, Longeur_NoTel = 17;	// CONSTANTES STRUCT ADRESSE
const int Longeur_Descript = 65;	// CONSTANTES STRUCT DÉPENSE
const int Longeur_Prenom = 21, Longeur_Nom = 21;	// CONSTANTES STRUCT PARTICIPANT
const int nbDepenseMax = 10;				// CONSTANTES NB DE DÉPENSE MAX PAR PARTICIPANT
const double MontantDep_Max = 99999.99;		// CONSTANTES MONTANT MAX PAR DÉPENSE

// LES STRUCTURES DE DONNÉES
struct Adresse
{
	char	noCivique[Longeur_NoCivique];
	char	rue[Longeur_Rue];
	char	ville[Longeur_Ville];
	char	codePostal[Longeur_CodeP];
	char	telephone[Longeur_NoTel];
};

struct Depense
{
	double	montant;
	char	description[Longeur_Descript];
	time_t	dateHeureDepense;				// VARIABLE QUI PERMET DE SAVOIR LA DATE ET HEURE EXACTE DE LA DÉPENSE
};

struct Participant
{
	char	prenom[Longeur_Prenom];
	char	nom[Longeur_Nom];
	Adresse adresse;
	int		nbDepenseActuel;
	int		liste_nbDepense[nbDepenseMax];
};


// VARIABLES GLOBALES EXTERNES 
extern size_t noParticipant;
extern size_t nbParticipant;

// LES PROTOTYPES DE FONCTIONS POUR DB.CPP
int db_size();
void db_read(size_t noParticipant, Participant* p);
void db_write(size_t noParticipant, Participant* p);