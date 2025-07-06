/**
 * \file Colis.cpp
 * \brief Implantation de la classe Colis.
 * \author Ladouceur Noah
 * \version 0.1
 * \date Mai 2025
 */
#include "Colis.h"
#include <sstream>
#include <stdexcept>
#include "ContratException.h"

using namespace std;

namespace microdrone
{

/**
* \brief classe du constructeur "Colis"
*/
Colis::Colis(int p_id, double p_poids, const string& p_destination):
    m_id(p_id), m_poids(p_poids), m_dest(p_destination)
{
    PRECONDITION(p_id>0);
    PRECONDITION(p_poids>0.0);
    PRECONDITION(!p_destination.empty());
    verifieInvariant();
}

/**
* \brief classe Invariant
*/
void Colis::verifieInvariant() const
{
    INVARIANT(m_id > 0);
    INVARIANT(m_poids > 0.0);
    INVARIANT(!m_dest.empty());
}

    /**
     * \brief Retourne l'identifiant du colis.
     * \return L'identifiant unique du colis.
     */
int Colis::reqId() const
{
    return m_id;
}

    /**
     * \brief Retourne la description complète du colis.
     * \return Une chaîne contenant l'ID, le poids et la destination du colis.
     */
string Colis::reqDescription() const
{
    ostringstream oss;
    oss << "Colis ID: " << m_id
    << ", Poids: " << m_poids << "kg "
    <<", destination: " << m_dest;
    return oss.str();
}

    /**
     * \brief Retourne le poids du colis.
     * \return Le poids du colis en kilogrammes.
     */
double Colis::reqPoids() const
{
    return m_poids;
}

    /**
     * \brief Retourne la destination du colis.
     * \return La destination sous forme de chaîne de caractères.
     */
string Colis::reqDestination() const
{
    return m_dest;
}


} // namespace microdrone
