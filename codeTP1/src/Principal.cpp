/**
 * \file Principal.cpp
 * \brief Programme principal pour la gestion de la flotte de drones.
 * \author Votre Nom
 * \version 0.1
 * \date Mai 2025
 */
#include "Gestionnaire.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;
using namespace microdrone;

void afficherMenu() {
    cout << endl;
    cout << "======= MENU =======\n";
    cout << "1. Charger un scénario\n";
    cout << "2. Planifier les missions\n";
    cout << "3. Lancer la prochaine mission\n";
    cout << "4. Terminer une mission en cours\n";
    cout << "5. Afficher l'état du système\n";
    cout << "6. Afficher les statistiques\n";
    cout << "7. Dernière notification\n";
    cout << "0. Quitter\n";
    cout << "Votre choix : ";
}

int main() {
#ifdef _WIN32
    // Basculer la console Windows en UTF-8 pour afficher correctement les accents
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    // En-tête du programme
    cout << "╔════════════════════════════════════╗" << endl;
    cout << "║   DRONE CONTROL SYSTEM             ║" << endl;
    cout << "╚════════════════════════════════════╝" << endl;

    Gestionnaire gestionnaire;
    int choix = -1;
    string fichierScenario;

    cout << "=== Programme de gestion de flotte de drones ===\n";
    
    while (choix != 0) {
        afficherMenu();
        cin >> choix;
        cout << endl << "Option choisie: " << choix << endl;
        
        try {
            switch (choix) {                case 1: // Charger un scénario
                    {
                        cout << endl << "[INITIALISATION...]" << endl;
                        
                        try {
                            // Pour l'exemple, on utilise un chemin fixe
                            // Dans une vraie application, on pourrait demander le chemin
                            gestionnaire.chargerScenario("../data/scenario_demo.txt");
                            cout << "[SUCCÈS] Données chargées !" << endl;
                        }
                        catch (const exception& e) {
                            cout << "[ÉCHEC] Impossible de charger le scénario: " << e.what() << endl;
                        }
                    }
                    break;
                    
                case 2: // Planifier les missions
                    cout << endl << "[PLANIFICATION]" << endl;
                    gestionnaire.planifierMissions();
                    break;
                    
                case 3: // Lancer la prochaine mission
                    cout << endl << "[LANCEMENT]" << endl;
                    gestionnaire.lancerMission();
                    break;
                    
                case 4: // Terminer une mission en cours
                    cout << endl << "[TERMINAISON]" << endl;
                    gestionnaire.terminerMission();
                    break;
                    
                case 5: // Afficher l'état du système
                    cout << endl << "[ÉTAT DU SYSTÈME]" << endl;
                    cout << gestionnaire.reqDescription() << endl;
                    break;
                    
                case 6: // Afficher les statistiques
                    cout << endl << "[STATISTIQUES]" << endl;
                    cout << gestionnaire.reqStatistiques() << endl;
                    break;
                    
                case 7: // Dernière notification
                    cout << endl << "[NOTIFICATION]" << endl;
                    gestionnaire.afficherDerniereNotification();
                    break;
                    
                case 0: // Quitter
                    cout << "Au revoir!\n";
                    break;
                    
                default:
                    cout << "Choix invalide. Veuillez réessayer.\n";
            }
        }
        catch (const exception& e) {
            cout << "Erreur : " << e.what() << endl;
        }
    }
    
    return 0;
}
