#include <matplotlibcpp.h>
#include <cmath>

namespace plt = matplotlibcpp;

// Function to calculate pressure using Bernoulli's equation
double calculatePressure(double velocity) {
    // Constants
    double rho = 1.2; // Density of air (kg/m^3)
    double g = 9.81;  // Acceleration due to gravity (m/s^2)
    double h = 0.0;   // Height (m), assuming no change in height

    // Calculate pressure using Bernoulli's equation
    double pressure = 0.5 * rho * velocity * velocity + rho * g * h;
    return pressure;
}

int main() {
    // Data arrays
    std::vector<double> velocities;
    std::vector<double> pressures;

    // Generate data points
    for (double v = 0.0; v <= 100.0; v += 1.0) { // Vary velocity from 0 to 100 m/s
        velocities.push_back(v);
        pressures.push_back(calculatePressure(v));
    }

    // Plot
    plt::plot(velocities, pressures);
    plt::xlabel("Velocity (m/s)");
    plt::ylabel("Pressure (Pa)");
    plt::title("Pressure vs Velocity (Bernoulli's Equation)");
    plt::show();

    return 0;
}
