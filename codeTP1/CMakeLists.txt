cmake_minimum_required(VERSION 3.10)
project(FlotteDrones)

# Définir le standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Inclure les fichiers d'en-tête
include_directories(src)

# Définir les fichiers sources
set(SOURCES
    src/Principal.cpp
    src/Drone.cpp
    src/Colis.cpp
    src/Mission.cpp
    src/Gestionnaire.cpp
    src/ContratException.cpp
)

# Créer l'exécutable
add_executable(FlotteDrones ${SOURCES})

# Copier les fichiers de données dans le répertoire de build
file(COPY ${CMAKE_SOURCE_DIR}/data/ DESTINATION ${CMAKE_BINARY_DIR}/data/)
