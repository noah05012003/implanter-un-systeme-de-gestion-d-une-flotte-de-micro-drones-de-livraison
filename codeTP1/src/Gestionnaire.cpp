/**
 * \file Gestionnaire.cpp
 * \brief Implantation de la classe Gestionnaire.
 * \author Votre Nom
 * \version 0.1
 * \date Mai 2025
 */
#include "Gestionnaire.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <set>
#include <vector>
#include <memory>
#include "ContratException.h"

using namespace std;

namespace microdrone
{
    /**
     * \brief Constructeur par défaut de la classe Gestionnaire.
     */
Gestionnaire::Gestionnaire()
{
}

    /**
     * \brief Charge un scénario de drones et colis à partir d’un fichier texte.
     *
     * \param[in] p_nomFichier Le nom du fichier de scénario à charger.
     *
     * \pre p_nomFichier ne doit pas être vide.
     * \post m_flotte, m_colisEnAttente, m_missionsPlanifiees, m_journalMissions
     *       et m_tousLesColis sont initialisés à partir du fichier.
     *
     * \throw invalid_argument si le nom de fichier est vide.
     * \throw runtime_error si le fichier ne peut pas être ouvert.
     */
    void Gestionnaire::chargerScenario(const string& p_nomFichier){
    if (p_nomFichier.empty()) {
        throw invalid_argument("Le nom du fichier ne peut pas être vide");
    }
    
    ifstream fichier(p_nomFichier);
    if (!fichier) {
        throw runtime_error("Impossible d'ouvrir le fichier " + p_nomFichier);
    }

    // Réinitialiser les structures avant de charger le nouveau scénario
    m_flotte.clear();
    while (!m_colisEnAttente.empty()) {
        m_colisEnAttente.pop();
    }
    m_missionsPlanifiees.clear();
    m_journalMissions.clear();
    m_tousLesColis.clear();
    
    string ligne;
    int nbDrones = 0;
    int nbColis = 0;
    
    while (getline(fichier, ligne)) {
        if (ligne.empty() || ligne[0] == '#') {
            // Ligne vide ou commentaire
            continue;
        }
        
        istringstream iss(ligne);
        string type;
        iss >> type;
          if (type == "DRONE") {
            int id;
            string modele;
            double chargeMax;
            
            iss >> id >> modele >> chargeMax;
            
            Drone nouveauDrone(id, modele, chargeMax);
            m_flotte.push_back(nouveauDrone);
            nbDrones++;
        }
        else if (type == "COLIS") {
            int id;
            double poids;
            string destination;
            
            iss >> id >> poids;
            
            string reste;
            getline(iss, reste);
            size_t pos = reste.find_first_not_of(" \t");
            if (pos != string::npos) {
                destination = reste.substr(pos);
            }
            
            Colis nouveauColis(id, poids, destination);
            m_tousLesColis.push_back(nouveauColis);
            m_colisEnAttente.push(nouveauColis);
            nbColis++;
        }
    }
    
    cout << "Scénario chargé : " << nbDrones << " drones et " << nbColis << " colis" << endl;
}

    /**
     * \brief Planifie les missions pour les colis en attente.
     *
     * \post Les missions sont ajoutées à m_missionsPlanifiees si un drone est disponible.
     * \post Les colis trop lourds ou sans drone disponible sont ignorés et génèrent une notification.
     */
    void Gestionnaire::planifierMissions()
{
    int nbColisAvant = m_colisEnAttente.size();
    int nbMissionsPlanifiees = 0;

    while (!m_colisEnAttente.empty())
    {
        Colis colis = m_colisEnAttente.front();
        if (colis.reqPoids() > 2.0)
        {
            m_notifications.push("Colis #" + to_string(colis.reqId()) + " trop lourd (> 2.0 kg)");
            m_colisEnAttente.pop();
            continue;
        }
        bool missionPlanifiee = false;
        for (Drone& drone : m_flotte)
        {
            if (drone.estDisponible() && colis.reqPoids() <= drone.reqChargeMax())
            {
                drone.emporter(std::make_shared<Colis>(colis));
                Mission mission(drone.reqId(), colis.reqId());
                m_missionsPlanifiees.push_back(mission);
                m_colisEnAttente.pop();
                m_notifications.push("Mission planifiée pour colis #" + to_string(colis.reqId()));
                nbMissionsPlanifiees++;
                missionPlanifiee = true;
                break;
            }
        }

        if (!missionPlanifiee)
        {
            m_notifications.push("Aucun drone disponible pour le colis #" + to_string(colis.reqId()));
            break;
        }
    }

    int nbColisRestants = m_colisEnAttente.size();

    cout << nbColisAvant << " colis en attente\n";
    cout << nbMissionsPlanifiees << " missions planifiées avec succès\n";
    cout << nbColisRestants << " colis restent en attente\n";
}

    /**
 * \brief Lance la prochaine mission planifiée.
 *
 * Change l’état de la première mission planifiée (PLANIFIEE) à EN_COURS et affiche
 * les détails du lancement, incluant le drone et le colis.
 *
 * \post Une mission est marquée comme en cours.
 * \post Une notification est ajoutée à m_notifications.
 */

// Lance la prochaine mission planifiée
void Gestionnaire::lancerMission()
{

    for (Mission& mission : m_missionsPlanifiees)
    {
        if (mission.reqEtat() == MissionEtat::PLANIFIEE)
        {
            mission.definirEtat(MissionEtat::EN_COURS);

            int droneId = mission.reqDroneId();
            int colisId = mission.reqColisId();
            const Colis* colisPtr = trouverColisParId(colisId);
            if (colisPtr != nullptr){
                std::cout << "Mission lancée : Drone D" << droneId
                          << " affecté au colis C" << colisId
                          << " (" << fixed << setprecision(1)
                          << colisPtr->reqPoids() << " kg)" << endl;
            }
            else
            {
                cout << "Mission lancée : Drone D" << droneId << " affecté au colis C" << colisId << endl;
            }
            m_notifications.push("Mission lancée : " + mission.reqDescription());
            return;
        }
    }
    cout << "Aucune mission planifiée à lancer." << endl;
    m_notifications.push("Aucune mission planifiée à lancer.");
}


    /**
     * \brief Termine la mission actuellement en cours.
     *
     * Met à jour l’état de la première mission EN_COURS à TERMINEE, libère le drone correspondant
     * et envoie un message de terminaison.
     */
    void Gestionnaire::terminerMission(){
    for (auto it = m_missionsPlanifiees.begin(); it != m_missionsPlanifiees.end(); ++it) {
        if (it->reqEtat() == MissionEtat::EN_COURS)
        {
            it->definirEtat(MissionEtat::TERMINEE);
            int idDrone = it->reqDroneId();

            for (Drone& drone : m_flotte)
            {
                if (drone.reqId() == idDrone && !drone.estDisponible())
                {
                    drone.livrer();
                    break;
                }
            }

            m_journalMissions.push_back(*it);
            string message = " Mission terminée par le drone D" + to_string(idDrone);
            cout << message << endl;
            m_notifications.push(message);
            m_missionsPlanifiees.erase(it);
            return;
        }
    }
    string message = "Aucune mission en cours à terminer";
    cout << message << endl;
    m_notifications.push(message);
}


    /**
     * \brief Retourne une description textuelle de l’état actuel du système.
     *
     * Affiche les drones avec leur état, le nombre de colis en attente,
     * de missions planifiées et de missions terminées.
     */
string Gestionnaire::reqDescription() const
{
    ostringstream oss;
    oss << "État actuel du système :\n";

    for (const Drone& drone : m_flotte)
        oss << drone.reqDescription() << "\n";

    oss << "\nColis en attente : " << m_colisEnAttente.size() << "\n";
    oss << "Missions planifiées : " << m_missionsPlanifiees.size() << "\n";
    oss << "Missions terminées : " << m_journalMissions.size() << "\n";

    return oss.str();
}

    /**
     * \brief Retourne les statistiques de la flotte et des missions.
     *
     * Donne un résumé du nombre total de drones, ceux disponibles et en mission,
     * le nombre de missions planifiées et terminées, ainsi que le nombre de colis en attente.
     */
    string Gestionnaire::reqStatistiques() const{
    ostringstream oss;
    oss << endl;

    int dronesDisponibles = 0;
    int dronesEnMission = 0;

    for (const Drone& drone : m_flotte)
    {
        if (drone.estDisponible())
            dronesDisponibles++;
        else
            dronesEnMission++;
    }

    oss << "Nombre de drones : " << m_flotte.size() << endl;
    oss << "Drones disponibles : " << dronesDisponibles << endl;
    oss << "Drones en mission : " << dronesEnMission << endl;
    oss << endl;
    oss << "Missions planifiées : " << m_missionsPlanifiees.size() << endl;
    oss << "Missions terminées : " << m_journalMissions.size() << endl;
    oss << "Colis en attente : " << m_colisEnAttente.size() << endl;

    return oss.str();
}

    /**
     * \brief Cherche un colis à partir de son identifiant.
     *
     * \param[in] p_colisId L’identifiant du colis recherché.
     * \return Un pointeur constant vers le colis si trouvé, nullptr sinon.
     */
    const Colis* Gestionnaire::trouverColisParId(int p_colisId) const{
    for (const Colis& c : m_tousLesColis)
    {
        if (c.reqId() == p_colisId)
            return &c;
    }
    return nullptr;
}

    /**
    * \brief Affiche la dernière notification du système.
    *
    * Retire la notification du dessus de la pile m_notifications et l’affiche.
    * Si aucune notification n’est présente, affiche un message par défaut.
    */
void Gestionnaire::afficherDerniereNotification()
{
    cout << endl;

    if (!m_notifications.empty())
    {
        cout << m_notifications.top() << endl;
        m_notifications.pop();
    }
    else
    {
        cout << "Aucune notification à afficher." << endl;
    }
}

} // namespace microdrone
