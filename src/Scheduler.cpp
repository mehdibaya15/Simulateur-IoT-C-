#include "Scheduler.hpp"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <thread>

void Scheduler::addSensor(Sensor* sensor) {
    sensors_.push_back(sensor);
}

void Scheduler::simulation(unsigned steps, unsigned delayMs) {
    writeWebData(steps);
    for (unsigned i = 0; i < steps; ++i) {
        ++tick_;
        for (Sensor* s : sensors_) s->update(tick_);
        writeWebData(steps);
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}

// Ecrit l'etat des capteurs dans web/data.js : c'est le fichier lu par la page web.
void Scheduler::writeWebData(unsigned total) const {
    std::filesystem::create_directories("web");
    {
        std::ofstream out("web/data.js.tmp");
        out << "window.DATA = {\"tick\": " << tick_ << ", \"total\": " << total << ", \"sensors\": [";
        for (std::size_t i = 0; i < sensors_.size(); ++i) {
            const Sensor* s = sensors_[i];
            if (i > 0) out << ", ";
            out << "{\"id\": " << s->getId() << ", \"type\": \"" << s->getType() << "\""
                << ", \"period\": " << s->getPeriod() << ", \"count\": " << s->getCount()
                << ", \"value\": \"" << (s->getCount() ? s->valueText() : "--") << "\""
                << ", \"unit\": \"" << s->unit() << "\"}";
        }
        out << "]};\n";
    }
    std::filesystem::rename("web/data.js.tmp", "web/data.js");
}

std::ostream& operator<<(std::ostream& os, const Scheduler& s) {
    os << "Scheduler : " << s.sensors_.size() << " capteur(s)";
    for (const Sensor* p : s.sensors_)
        os << "\n  - " << p->getType() << " #" << p->getId() << " (toutes les " << p->getPeriod() << " s)";
    return os;
}
