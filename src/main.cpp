#include <fstream>
#include <iostream>

#include "Scheduler.hpp"
#include "Sensors.hpp"
#include "Server.hpp"

int main() {
    Server server("logs");

    // Les capteurs : (serveur, periode en secondes)
    TemperatureSensor temp1(&server, 2);
    TemperatureSensor temp2(&server, 5);
    HumiditySensor humidity(&server, 3);
    SoundSensor sound(&server, 1);
    LightSensor light(&server, 4);

    Scheduler scheduler;
    scheduler.addSensor(&temp1);
    scheduler.addSensor(&temp2);
    scheduler.addSensor(&humidity);
    scheduler.addSensor(&sound);
    scheduler.addSensor(&light);

    std::cout << "Ouvrez web/index.html dans votre navigateur.\n" << scheduler << "\n\n";
    scheduler.simulation(60);  // 60 ticks (1 tick = 1 seconde)

    // Operateur << : sortie console puis sortie fichier
    std::cout << "\n" << server << std::endl;
    std::ofstream log("logs/resume.log");
    log << server << std::endl;
    return 0;
}
