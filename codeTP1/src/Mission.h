/**
 * \file Mission.h
 * \brief Déclaration de la classe Mission.
 * \author Votre Nom
 * \version 0.1
 * \date Mai 2025
 */
#ifndef MISSION_H_DEJA_INCLU
#define MISSION_H_DEJA_INCLU

#include <string>

namespace microdrone
{

// L'état d'une mission est défini comme suit
enum class MissionEtat
{
    PLANIFIEE,   /*!< Mission planifiée */
    EN_COURS,    /*!< Mission en cours d'exécution */
    TERMINEE     /*!< Mission terminée */
};

/**
 * \brief Classe représentant une mission de livraison.
 */
class Mission
{
public:
    /**
     * \brief Constructeur d'une mission.
     */
    Mission(int p_droneId, int p_colisId);
    
    /**
     * \brief Surcharge de l'opérateur de comparaison.
     */
    bool operator==(const Mission& p_mission) const;

    /**
     * \brief Retourne la description de la mission.
     */
    std::string reqDescription() const;

    /**
     * \brief Retourne l'ID du drone assigné.
     */
    int reqDroneId() const;

    /**
     * \brief Retourne l'ID du colis à livrer.
     */
    int reqColisId() const;    /**
     * \brief Retourne l'état de la mission.
     */
    MissionEtat reqEtat() const;

    /**
     * \brief Met à jour l'état de la mission.
     */
    void definirEtat(MissionEtat p_etat);

    /**
     * \brief Vérifie les invariants de la classe.
     */
    void verifieInvariant() const;

private:
    int m_droneId;      //!< ID du drone assigné
    int m_colisId;      //!< ID du colis à livrer
    MissionEtat m_etat; //!< État de la mission
};

} // namespace microdrone

#endif // MISSION_H_DEJA_INCLU
