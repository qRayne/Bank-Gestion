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
void affichage_Depenses(Participant* p);

// FONCTIONS DE VALIDATION
double lireUnMontantValide(double max);
double sommeDepenseParticipant(double MontantDepense,Participant* p);