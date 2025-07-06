/**
 * \file Mission.cpp
 * \brief Implantation de la classe Mission.
 * \author Votre Nom
 * \version 0.1
 * \date Mai 2025
 */
#include "Mission.h"
#include <sstream>
#include "ContratException.h"

using namespace std;

namespace microdrone
{

    /**
     * \brief Constructeur de la classe Mission.
     *
     * \param[in] p_droneId Identifiant du drone affecté à la mission.
     * \param[in] p_colisId Identifiant du colis à livrer.
     *
     * \pre p_droneId > 0
     * \pre p_colisId > 0
     */
Mission::Mission(int p_droneId, int p_colisId):m_droneId(p_droneId), m_colisId(p_colisId), m_etat(MissionEtat::PLANIFIEE)
{
    PRECONDITION(p_droneId > 0);
    PRECONDITION(p_colisId > 0);
    verifieInvariant();
}


    /**
     * \brief Retourne une description textuelle de la mission.
     *
     * Affiche les identifiants du drone et du colis ainsi que l’état actuel
     * de la mission (PLANIFIÉE, EN COURS, ou TERMINÉE).
     *
     * \return Une chaîne contenant la description de la mission.
     */
string Mission::reqDescription() const
{
    ostringstream oss;
    oss << "[Drone #" << m_droneId << " → Colis #" << m_colisId << "] État: ";
    switch (m_etat) {
        case MissionEtat::PLANIFIEE: oss << "PLANIFIÉE"; break;
        case MissionEtat::EN_COURS: oss << "EN COURS"; break;
        case MissionEtat::TERMINEE: oss << "TERMINÉE"; break;
    }
    return oss.str();
}

    /**
     * \brief Opérateur de comparaison d’égalité.
     *
     * \param[in] p_mission La mission à comparer.
     * \return true si les deux missions ont les mêmes identifiants, false sinon.
     */
bool Mission::operator==(const Mission& p_mission) const
{
    return m_droneId == p_mission.m_droneId && m_colisId == p_mission.m_colisId;
}

    /**
     * \brief Retourne l’identifiant du drone associé à la mission.
     *
     * \return L’ID du drone.
     */
    int Mission::reqDroneId() const{
    return m_droneId;
}

    /**
     * \brief Retourne l’identifiant du colis associé à la mission.
     *
     * \return L’ID du colis.
     */
int Mission::reqColisId() const
{
    return m_colisId;
}

    /**
     * \brief Retourne l’état actuel de la mission.
     *
     * \return L’état de la mission (PLANIFIEE, EN_COURS, ou TERMINEE).
     */
MissionEtat Mission::reqEtat() const
{
    return m_etat;
}

    /**
     * \brief Définit un état pour la mission.
     *
     * \param[in] p_etat Le nouvel état à assigner à la mission.
     *
     * \post L’état de la mission est mis à jour.
     */
void Mission::definirEtat(MissionEtat p_etat)
{
    m_etat = p_etat;
    verifieInvariant();
}

    /**
     * \brief Vérifie les invariants de la classe Mission.
     */
void Mission::verifieInvariant() const
{
    INVARIANT(m_droneId > 0);
    INVARIANT(m_colisId > 0);
}

} // namespace microdrone
