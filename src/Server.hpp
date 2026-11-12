#pragma once
#include <iostream>
#include <string>

class Sensor;

// Serveur : recoit les mesures, les affiche et les enregistre dans des logs.
class Server {
public:
    explicit Server(const std::string& logDir = "logs");
    Server(const Server& other);
    Server& operator=(const Server& other);
    ~Server();

    void receive(const Sensor& sensor);
    void consoleWrite(const Sensor& sensor, std::ostream& os = std::cout) const;
    void fileWrite(const Sensor& sensor) const;  // un fichier CSV par type de capteur

    friend std::ostream& operator<<(std::ostream& os, const Server& s);

private:
    std::string logDir_;
    unsigned long total_ = 0;
};
