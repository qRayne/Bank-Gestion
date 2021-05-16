#pragma once

// FONCTIONS PRINCIPALES DU PROGRAMME
void CMD_AjouterUnParticipant();
void CMD_AfficherUnParticipant();
void CMD_AjouterDesDepenses();
void CMD_SupprimerDesDepenses();
void CMD_AfficherEtatDesComptes();
void CMD_AfficherUnScenarionDeReglements();
void CMD_SupprimerTousLesParticipants();
void CMD_QuitterLeProgramme();

// FONCTION D'AFFICHAGE
void affichage(size_t no, Participant& p);
void affichage_Depenses(Participant& p);
void affichage_QuitterCommande();
void affichage_QuitterCommandeDepense();

// FONCTIONS DE VALIDATION ET DE SOMMATION
double lireUnMontantValide(double max);
double sommeDepenseParticipant(double MontantDepense,Participant& p);
double sommeQuotePart(double Total, size_t no);

// FONCTIONS D'INPUT 
void input_Depense_Description(Participant& p);
int lire_no_Supprimer(int nbDepenses);

// FONCTIONS DE MODIFICATION DE VALEUR
void supprimer_Client(int participant, Participant& p);
void supprimer_Depenses_Total(Participant& p);

// FONCTIONS DE VÉRIFICATION D'INPUT 
void noDepenseValideEtAffichage(size_t no, int noInput, Participant& p);