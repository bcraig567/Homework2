#include <iostream>
#include <vector>
#include <string>

class Sensor {
public:
    // simulate data collection
    virtual void gatherData() = 0;

    // data processing
    virtual void processData() = 0;
};

class AltitudeSensor : public Sensor {
public:
    void gatherData() override {
        std::cout << "Gathering data from Altitude Sensor." << std::endl;
        // gathering altitude data
    }

    void processData() override {
        std::cout << "Processing data from Altitude Sensor." << std::endl;
        // processing altitude data
    }
};

class AirspeedSensor : public Sensor {
public:
    void gatherData() override {
        std::cout << "Gathering data from Airspeed Sensor." << std::endl;
        // gathering airspeed data
    }

    void processData() override {
        std::cout << "Processing data from Airspeed Sensor." << std::endl;
        // processing airspeed data
    }
};

class AttitudeSensor : public Sensor {
public:
    void gatherData() override {
        std::cout << "Gathering data from Attitude Sensor." << std::endl;
        // gathering attitude data
    }

    void processData() override {
        std::cout << "Processing data from Attitude Sensor." << std::endl;
        // processing attitude data
    }
};

class SensorFactory {
public:
    // create sensors based on input string
    static Sensor* createSensor(const std::string& sensorType) {
        if (sensorType == "Altitude") {
            return new AltitudeSensor();
        }
        else if (sensorType == "Airspeed") {
            return new AirspeedSensor();
        }
        else if (sensorType == "Attitude") {
            return new AttitudeSensor();
        }
        else {
            std::cerr << "Unknown sensor type: " << sensorType << std::endl;
            return nullptr;
        }
    }
};

class AerospaceControlSystem {
private:
    std::vector<Sensor*> sensors; // store pointers to sensors
public:
    // add sensor to the control system
    void addSensor(Sensor* sensor) {
        sensors.push_back(sensor);
    }

    // monitor sensors and adjust controls
    void monitorAndAdjust() {
        for (Sensor* sensor : sensors) {
            sensor->gatherData();
            sensor->processData();
            std::cout << "Adjusting controls based on sensor data." << std::endl;
        }
    }
};

int main() {
    // create instance of AerospaceControlSystem
    AerospaceControlSystem ctrlSys;

    // add sensors to control system using SensorFactory
    ctrlSys.addSensor(SensorFactory::createSensor("Altitude"));
    ctrlSys.addSensor(SensorFactory::createSensor("Airspeed"));
    ctrlSys.addSensor(SensorFactory::createSensor("Attitude"));

    // monitor sensors and adjust controls
    ctrlSys.monitorAndAdjust();

    return 0;
}
