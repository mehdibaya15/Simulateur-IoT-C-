#include "Server.hpp"
#include "Sensor.hpp"

#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>

namespace fs = std::filesystem;

Server::Server(const std::string& logDir) : logDir_(logDir) {}

Server::Server(const Server& other) : logDir_(other.logDir_), total_(other.total_) {}

Server& Server::operator=(const Server& other) {
    if (this != &other) {
        logDir_ = other.logDir_;
        total_ = other.total_;
    }
    return *this;
}

Server::~Server() = default;

void Server::receive(const Sensor& sensor) {
    ++total_;
    consoleWrite(sensor);
    fileWrite(sensor);
}

void Server::consoleWrite(const Sensor& sensor, std::ostream& os) const {
    os << "[tick " << std::setw(2) << sensor.getLastTick() << "] " << sensor << std::endl;
}

// Format CSV avec ';' : s'ouvre directement dans Excel
void Server::fileWrite(const Sensor& sensor) const {
    fs::create_directories(logDir_);
    const fs::path path = fs::path(logDir_) / (sensor.getType() + ".csv");
    const bool newFile = !fs::exists(path);

    std::ofstream out(path, std::ios::app);
    if (!out) return;
    if (newFile) out << "tick;date;id;type;valeur;unite\n";

    const std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    out << sensor.getLastTick() << ';' << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << ';'
        << sensor.getId() << ';' << sensor.getType() << ';' << sensor.valueText() << ';' << sensor.unit() << '\n';
}

std::ostream& operator<<(std::ostream& os, const Server& s) {
    return os << "Serveur : " << s.total_ << " mesure(s) recue(s)";
}
