#pragma once
#include <ostream>
#include <string>

class Server;

// Classe abstraite : un capteur est un "processus" anime par le Scheduler.
class Sensor {
public:
    Sensor(const std::string& type, Server* server, unsigned period);
    Sensor(const Sensor& other);
    Sensor& operator=(const Sensor& other);
    virtual ~Sensor() = default;

    void update(unsigned tick);  // appelee par le Scheduler a chaque tick
    void execute();              // mesure, puis envoi au serveur

    virtual double measure() = 0;                 // simule la lecture (aleatoire)
    virtual std::string valueText() const;        // valeur formatee
    virtual std::string unit() const { return ""; }

    unsigned getId() const { return id_; }
    const std::string& getType() const { return type_; }
    unsigned getPeriod() const { return period_; }
    unsigned getLastTick() const { return lastTick_; }
    unsigned getCount() const { return count_; }  // nombre de mesures faites
    double getValue() const { return value_; }

    friend std::ostream& operator<<(std::ostream& os, const Sensor& s);

protected:
    static double random(double min, double max);

private:
    static unsigned nextId_;  // identifiants uniques
    unsigned id_;
    std::string type_;
    Server* server_;          // non proprietaire
    unsigned period_;         // base de temps propre au capteur
    unsigned counter_ = 0;
    unsigned lastTick_ = 0;
    unsigned count_ = 0;
    double value_ = 0;
};
