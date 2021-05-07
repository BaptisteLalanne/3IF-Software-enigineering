cmake_minimum_required(VERSION 3.17)
project(ProjetCapteur)

set(CMAKE_CXX_STANDARD 14)

add_executable(ProjetCapteur main.cpp Capteur.cpp Capteur.h Mesure.cpp Mesure.h Utilisateur.cpp Utilisateur.h Service.cpp Service.h)