#include <iostream>
#include <vector>
#include <string>

// Abstract base class for Sensor
class Sensor {
public:
    // Virtual function to simulate data collection
    virtual void gatherData() = 0;

    // Virtual function for data processing
    virtual void processData() = 0;
};

// Altitude sensor class
class AltitudeSensor : public Sensor {
public:
    void gatherData() override {
        std::cout << "Gathering data from Altitude Sensor." << std::endl;
        // Simulate gathering altitude data
    }

    void processData() override {
        std::cout << "Processing data from Altitude Sensor." << std::endl;
        // Simulate processing altitude data
    }
};

// Airspeed sensor class
class AirspeedSensor : public Sensor {
public:
    void gatherData() override {
        std::cout << "Gathering data from Airspeed Sensor." << std::endl;
        // Simulate gathering airspeed data
    }

    void processData() override {
        std::cout << "Processing data from Airspeed Sensor." << std::endl;
        // Simulate processing airspeed data
    }
};

// Attitude sensor class
class AttitudeSensor : public Sensor {
public:
    void gatherData() override {
        std::cout << "Gathering data from Attitude Sensor." << std::endl;
        // Simulate gathering attitude data
    }

    void processData() override {
        std::cout << "Processing data from Attitude Sensor." << std::endl;
        // Simulate processing attitude data
    }
};

// Sensor factory class
class SensorFactory {
public:
    // Static function to create sensors based on input string
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

// Aerospace control system class
class AerospaceControlSystem {
private:
    std::vector<Sensor*> sensors; // Vector to store pointers to sensors
public:
    // Function to add a sensor to the control system
    void addSensor(Sensor* sensor) {
        sensors.push_back(sensor);
    }

    // Function to monitor sensors and adjust controls
    void monitorAndAdjust() {
        for (Sensor* sensor : sensors) {
            sensor->gatherData();
            sensor->processData();
            std::cout << "Adjusting controls based on sensor data." << std::endl;
        }
    }
};

int main() {
    // Create an instance of AerospaceControlSystem
    AerospaceControlSystem ctrlSys;

    // Add sensors to the control system using SensorFactory
    ctrlSys.addSensor(SensorFactory::createSensor("Altitude"));
    ctrlSys.addSensor(SensorFactory::createSensor("Airspeed"));
    ctrlSys.addSensor(SensorFactory::createSensor("Attitude"));

    // Monitor sensors and adjust controls
    ctrlSys.monitorAndAdjust();

    return 0;
}