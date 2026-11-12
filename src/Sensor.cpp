#include "Sensor.hpp"
#include "Server.hpp"

#include <iomanip>
#include <random>
#include <sstream>

unsigned Sensor::nextId_ = 1;

Sensor::Sensor(const std::string& type, Server* server, unsigned period)
    : id_(nextId_++), type_(type), server_(server), period_(period == 0 ? 1 : period) {}

Sensor::Sensor(const Sensor& other)
    : id_(nextId_++), type_(other.type_), server_(other.server_), period_(other.period_),
      counter_(other.counter_), lastTick_(other.lastTick_), count_(other.count_), value_(other.value_) {}

Sensor& Sensor::operator=(const Sensor& other) {
    if (this != &other) {
        type_ = other.type_;
        server_ = other.server_;
        period_ = other.period_;
        counter_ = other.counter_;
        lastTick_ = other.lastTick_;
        count_ = other.count_;
        value_ = other.value_;
    }
    return *this;
}

void Sensor::update(unsigned tick) {
    lastTick_ = tick;
    if (++counter_ >= period_) {
        counter_ = 0;
        execute();
    }
}

void Sensor::execute() {
    value_ = measure();
    ++count_;
    if (server_ != nullptr) server_->receive(*this);
}

std::string Sensor::valueText() const {
    std::ostringstream os;
    os << std::fixed << std::setprecision(1) << value_;
    return os.str();
}

double Sensor::random(double min, double max) {
    static std::mt19937 engine{std::random_device{}()};
    return std::uniform_real_distribution<double>(min, max)(engine);
}

std::ostream& operator<<(std::ostream& os, const Sensor& s) {
    os << s.type_ << " #" << s.id_ << " : " << s.valueText();
    if (!s.unit().empty()) os << " " << s.unit();
    return os;
}
