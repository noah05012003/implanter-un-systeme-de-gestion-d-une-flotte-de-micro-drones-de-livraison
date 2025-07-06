/**
 * \file Colis.h
 * \brief Déclaration de la classe Colis.
 * \author Ladouceur Noah
 * \version 0.1
 * \date Mai 2025
 */
#ifndef COLIS_H_DEJA_INCLU
#define COLIS_H_DEJA_INCLU

#include <string>
#include "ContratException.h"

namespace microdrone
{

/**
 * \class Colis
 * \brief Représente un colis à livrer.
 */
class Colis
{
public:
    /**
     * \brief Constructeur d'un colis.
     */
    Colis(int p_id,
          double p_poids,
          const std::string& p_destination);
    
          
    /**
     * \brief Vérifie l'invariant de la classe.
     */
    void verifieInvariant() const;

    /**
     * \brief Retourne l'identifiant du colis.
     */
    int reqId() const;

    /**
     * \brief Retourne la description complète du colis.
     */
    std::string reqDescription() const;

    /**
     * \brief Retourne le poids du colis.
     */
    double reqPoids() const;

    /**
     * \brief Retourne la destination du colis.
     */
    std::string reqDestination() const;

private:
    int m_id;                 //!< Identifiant du colis.
    double m_poids;           //!< Poids en kg.
    std::string m_dest;       //!< Adresse de destination.
};

} // namespace microdrone

#endif // COLIS_H_DEJA_INCLU
