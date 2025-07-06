/**
 * \file Gestionnaire.h
 * \brief Déclaration de la classe Gestionnaire.
 * \author Votre Nom
 * \version 0.1
 * \date Mai 2025
 */
#ifndef GESTIONNAIRE_H_DEJA_INCLU
#define GESTIONNAIRE_H_DEJA_INCLU

#include <queue>
#include <list>
#include <string>
#include <vector>
#include <stack>
#include "Drone.h"
#include "Colis.h"
#include "Mission.h"

namespace microdrone
{

/**
 * \brief Classe gérant les opérations de livraison par drone.
 */
class Gestionnaire
{
public:
    /**
     * \brief Constructeur du gestionnaire.
     */
    Gestionnaire();

    /**
     * \brief Charge un scénario de livraison.
     */
    void chargerScenario(const std::string& p_nomFichier);

    /**
     * \brief Planifie les missions pour les colis en attente.
     */
    void planifierMissions();

    /**
     * \brief Lance la prochaine mission planifiée.
     */
    void lancerMission();

    /**
     * \brief Termine la mission en cours.
     */
    void terminerMission();

    /**
     * \brief Retourne une description de l'état actuel.
     */
    std::string reqDescription() const;

    /**
     * \brief Retourne les statistiques de la flotte.
     */
    std::string reqStatistiques() const;

    /**
     * \brief Affiche puis retire la dernière notification système.
     */
    void afficherDerniereNotification();

private:
    /**
     * \brief Trouve un colis par son ID.
     */
    const Colis* trouverColisParId(int p_colisId) const;

    std::vector<Drone> m_flotte;                      //!< La flotte de drones.
    std::queue<Colis> m_colisEnAttente;               //!< File des colis à livrer.
    std::vector<Mission> m_missionsPlanifiees;        //!< Liste des missions planifiées.
    std::list<Mission> m_journalMissions;             //!< Journal des missions complétées.
    std::vector<Colis> m_tousLesColis;                //!< Tous les colis chargés du scénario.
    std::stack<std::string> m_notifications;          //!< Pile LIFO des notifications système.
};

} // namespace microdrone

#endif // GESTIONNAIRE_H_DEJA_INCLU
