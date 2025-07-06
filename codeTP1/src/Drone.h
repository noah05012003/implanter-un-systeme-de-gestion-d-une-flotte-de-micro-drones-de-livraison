/**
 * \file Drone.h
 * \brief Déclaration de la classe Drone représentant un micro-drone de livraison.
 * \author Ladouceur Noah
 * \version 0.1
 * \date Mai 2025
 */
#ifndef DRONE_H_DEJA_INCLU
#define DRONE_H_DEJA_INCLU

#include <string>
#include <vector>
#include "ContratException.h"
#include <memory>

namespace microdrone
{

class Colis; //!< Déclaration anticipée pour éviter l'inclusion circulaire.

//! États possibles d'un drone.
enum class DroneEtat
{
    LIBRE,       /*!< Drone disponible */
    EN_VOL       /*!< Drone en mission */
};

/**
 * \class Drone
 * \brief Représente un drone dans la flotte.
 */
class Drone
{
public:    /**
     * \brief Constructeur d'un drone.
     */
    Drone(int p_id,
          const std::string& p_modele,
          double p_chargeMax);

    /**
     * \brief Fait emporter un colis par le drone.
     */
    void emporter(const std::shared_ptr<Colis>& p_colis);

    /**
     * \brief Fait livrer le colis actuel.
     */
    void livrer();
    
    /**
     * \brief Vérifie l'invariant de la classe.
     */
    void verifieInvariant() const;

    /**
     * \brief Retourne l'identifiant du drone.
     */
    int reqId() const;

    /**
     * \brief Retourne la description complète du drone.
     */
    std::string reqDescription() const;

    /**
     * \brief Retourne la charge utile maximale du drone.
     */
    double reqChargeMax() const;

    /**
     * \brief Vérifie si le drone est disponible.
     */
    bool estDisponible() const;    /**
     * \brief Retourne l'état actuel du drone.
     */
    DroneEtat reqEtat() const;

    /**
     * \brief Retourne le colis actuellement transporté.
     */
    const Colis* reqColisActuel() const;

private:
    int m_id;                                 //!< Identifiant unique.
    std::string m_modele;                     //!< Modèle du drone.
    double m_chargeMax;                       //!< Charge utile maximale (max=2.0kg).
    DroneEtat m_etat;                         //!< État actuel du drone.
    std::shared_ptr<Colis> m_colisActuel;     //!< Colis actuellement transporté (partagé).
};

} // namespace microdrone

#endif // DRONE_H_DEJA_INCLU
