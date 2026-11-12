#pragma once
#include <ostream>
#include <vector>
#include "Sensor.hpp"

// Ordonnanceur : donne un "tick" d'activation a chaque capteur.
// Il ne possede pas les capteurs : ils sont crees dans main().
class Scheduler {
public:
    Scheduler() = default;

    void addSensor(Sensor* sensor);
    void simulation(unsigned steps, unsigned delayMs = 1000);

    friend std::ostream& operator<<(std::ostream& os, const Scheduler& s);

private:
    void writeWebData(unsigned total) const;  // ecrit web/data.js pour la page web

    std::vector<Sensor*> sensors_;
    unsigned tick_ = 0;
};
