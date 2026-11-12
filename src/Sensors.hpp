#pragma once
#include <cmath>
#include "Sensor.hpp"

// Temperature : valeur decimale
class TemperatureSensor : public Sensor {
public:
    TemperatureSensor(Server* s, unsigned period) : Sensor("Temperature", s, period) {}
    double measure() override { return random(18.0, 30.0); }
    std::string unit() const override { return "C"; }
};

// Humidite : valeur decimale
class HumiditySensor : public Sensor {
public:
    HumiditySensor(Server* s, unsigned period) : Sensor("Humidity", s, period) {}
    double measure() override { return random(30.0, 70.0); }
    std::string unit() const override { return "%"; }
};

// Son : valeur entiere
class SoundSensor : public Sensor {
public:
    SoundSensor(Server* s, unsigned period) : Sensor("Sound", s, period) {}
    double measure() override { return std::round(random(30.0, 90.0)); }
    std::string valueText() const override { return std::to_string(static_cast<int>(getValue())); }
    std::string unit() const override { return "dB"; }
};

// Lumiere : valeur booleenne
class LightSensor : public Sensor {
public:
    LightSensor(Server* s, unsigned period) : Sensor("Light", s, period) {}
    double measure() override { return random(0.0, 1.0) < 0.7 ? 1.0 : 0.0; }
    std::string valueText() const override { return getValue() > 0.5 ? "ON" : "OFF"; }
};
