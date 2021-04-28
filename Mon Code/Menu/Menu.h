/*
	BUT : CE FICHIER D'EN TÊTE AVEC LE MENU.CPP PERMET DE DÉCLARER ET DÉFINIR LES FONCTIONS D'AFFICHAGE ET DE MANIPULATIONS DU MENU PRINCIPALE
*/
#pragma once

// INCLUDES PARTICULIERS
#include "../Database/db.h"

// LA STRUCTURE POUR MANIPULER LE MENU
enum Commandes { ajouterParticipant, afficherDossier, ajouterDépenses, suprimerDépenses, afficherÉtats, afficherScénario, SupprimerParticipants, quitter };


// LES PROTOTYPES DE FONCTIONS 
void ui_menu_Titre();	// PERMET D'ÊTRE UTILISER DANS LE MENU PRINCIPAL ET DANS CERTAINES FONCTIONS
void ui_afficherMenuPrincipal();
void ui_flushAll();
double arrondir(double v, int p);
Commandes ui_lireUnChoixValideDuMenuPrincipal();
