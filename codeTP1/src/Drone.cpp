/**
 * \file Drone.cpp
 * \brief Implantation de la classe Drone.
 * \author Ladouceur Noah
 * \version 0.1
 * \date Mai 2025
 */
#include "Drone.h"
#include "Colis.h"
#include <sstream>
#include <stdexcept>
#include "ContratException.h"

using namespace std;

namespace microdrone
{

    /**
     * \brief Constructeur de la classe Drone.
     *
     * \param[in] p_id Identifiant unique du drone (> 0).
     * \param[in] p_modele Nom du modèle du drone (peu pas etre vide).
     * \param[in] p_chargeMax Charge maximale que le drone peut emporter (> 0.0 kg).
     *
     * \pre p_id > 0
     * \pre !p_modele.empty()
     * \pre p_chargeMax > 0.0
     */
    Drone::Drone(int p_id, const string& p_modele, double p_chargeMax):m_id(p_id), m_modele(p_modele), m_chargeMax(p_chargeMax),m_etat(DroneEtat::LIBRE), m_colisActuel(nullptr)
{
    PRECONDITION(p_id > 0);
    PRECONDITION(!p_modele.empty());
    PRECONDITION(p_chargeMax > 0.0);
    verifieInvariant();
}

    /**
    * \brief Fait emporter un colis par le drone et change l’état du drone.
    *
    * \pre estDisponible() == true
    * \pre p_colis != nullptr
    * \pre p_colis->reqPoids() <= m_chargeMax
    *
    * \post m_etat == EN_VOL
    */

void Drone::emporter(const std::shared_ptr<Colis>& p_colis)
{
    PRECONDITION(estDisponible());
    PRECONDITION(p_colis != nullptr);
    PRECONDITION(p_colis->reqPoids() <= m_chargeMax);
    m_colisActuel = p_colis;
    m_etat = DroneEtat::EN_VOL;
    verifieInvariant();
}

    /**
     * \brief Réinitialise le colis transporté et rend le drone disponible.
     *
     * \pre m_etat == DroneEtat::EN_VOL
     * \pre m_colisActuel != nullptr
     *
     * \post m_etat == LIBRE
     * \post m_colisActuel == nullptr
     */
    void Drone::livrer(){
    PRECONDITION(m_etat == DroneEtat::EN_VOL);
    PRECONDITION(m_colisActuel != nullptr);
    m_colisActuel = nullptr;
    m_etat = DroneEtat::LIBRE;
    verifieInvariant();
}

    /**
 * \brief Retourne l’identifiant du drone.
 *
 * \return L’identifiant unique du drone.
 */
int Drone::reqId() const
{
    return m_id;
}

    /**
     * \brief Retourne une description complète du drone.
     *
     * \return Une chaîne de caractères décrivant l’état du drone.
     */
string Drone::reqDescription() const
{
    ostringstream oss;
    oss << "le drone " << m_id
    << ", modèle " << m_modele
    << ", charge MAX = " << m_chargeMax << " kg"
    << ", état " << (m_etat == DroneEtat::LIBRE ? "LIBRE" : "EN_VOL");
    if (m_colisActuel != nullptr)
        oss << ", Colis: " << m_colisActuel->reqDescription();
    return oss.str();
}

    /**
 * \brief Retourne la charge utile maximale du drone.
 *
 * \return La charge maximale (en kg) que le drone peut transporter.
 */
double Drone::reqChargeMax() const
{
    return m_chargeMax;
}

    /**
 * \brief Vérifie si le drone est actuellement disponible.
 *
 * \return true si le drone est LIBRE, false s’il est EN_VOL.
 */
bool Drone::estDisponible() const
{
    return m_etat == DroneEtat::LIBRE;
}

    /**
 * \brief Retourne l’état actuel du drone.
 *
 * \return L’état du drone (LIBRE ou EN_VOL).
 */
DroneEtat Drone::reqEtat() const
{
    return m_etat;
}

    /**
     * \brief Retourne un pointeur constant vers le colis transporté.
     *
     * \return Le pointeur vers le colis actuel, ou nullptr si aucun colis n’est transporté.
     */
    const Colis* Drone::reqColisActuel() const{
    return m_colisActuel.get();
}


    /**
 * \brief Vérifie les invariants de la classe Drone.
 */
    void Drone::verifieInvariant() const{
    INVARIANT(m_id > 0);
    INVARIANT(!m_modele.empty());
    INVARIANT(m_chargeMax > 0.0);



    if (m_etat == DroneEtat::EN_VOL)
    {
        INVARIANT(m_colisActuel != nullptr);
        INVARIANT(m_colisActuel->reqPoids() <= m_chargeMax);
    }
    else
    {
        INVARIANT(m_colisActuel == nullptr);
    }
}

} // namespace microdrone
