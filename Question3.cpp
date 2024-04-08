#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex mtx;

class AirTrafficController {
private:
    int trafficPatternCount = 0;
    bool asleep = true;

public:
    void wakeUp() {
        asleep = false;
    }

    void sleep() {
        asleep = true;
    }

    bool isAsleep() {
        return asleep;
    }

    int getTrafficPatternCount() {
        return trafficPatternCount;
    }

    void incrementTrafficPatternCount() {
        trafficPatternCount++;
    }

    void decrementTrafficPatternCount() {
        trafficPatternCount--;
    }
};

class Aircraft {
private:
    int id;
    AirTrafficController& atc;

public:
    Aircraft(int _id, AirTrafficController& _atc) : id(_id), atc(_atc) {}

    void enterTrafficPattern() {
        mtx.lock();
        if (atc.isAsleep()) {
            atc.wakeUp();
            cout << "Aircraft " << id << " wakes up ATC and enters the traffic pattern.\n";
        }
        else if (atc.getTrafficPatternCount() < 3) {
            atc.incrementTrafficPatternCount();
            cout << "Aircraft " << id << " enters the traffic pattern.\n";
        }
        else {
            cout << "Aircraft " << id << " traffic pattern is full. Diverting to other airports.\n";
        }
        mtx.unlock();
    }

    void exitTrafficPattern() {
        mtx.lock();
        atc.decrementTrafficPatternCount();
        if (atc.getTrafficPatternCount() == 0) {
            atc.sleep();
            cout << "ATC falls asleep.\n";
        }
        mtx.unlock();
    }
};

int main() {
    AirTrafficController atc;

    // Create ten aircraft
    Aircraft aircraft[10] = { Aircraft(1, atc), Aircraft(2, atc), Aircraft(3, atc), Aircraft(4, atc), Aircraft(5, atc),
                              Aircraft(6, atc), Aircraft(7, atc), Aircraft(8, atc), Aircraft(9, atc), Aircraft(10, atc) };

    // Simulate incoming aircraft
    for (int i = 0; i < 10; ++i) {
        // Let's simulate the landing process (1 second)
        this_thread::sleep_for(chrono::seconds(1));
        thread t(&Aircraft::enterTrafficPattern, &aircraft[i]);
        t.join();
    }

    // Simulate exiting aircraft
    for (int i = 0; i < 10; ++i) {
        // Let's simulate the exiting process (1 second)
        this_thread::sleep_for(chrono::seconds(1));
        thread t(&Aircraft::exitTrafficPattern, &aircraft[i]);
        t.join();
    }

    return 0;
}
