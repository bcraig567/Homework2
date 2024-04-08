#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

using namespace std;

mutex mtx;

class AirTrafficController {
private:
    int trafficPatternCount = 0;
    bool asleep = true;
    mutex sleepMutex;

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

    void lockSleepMutex() {
        sleepMutex.lock();
    }

    void unlockSleepMutex() {
        sleepMutex.unlock();
    }
};

class Aircraft {
private:
    int id;
    AirTrafficController& atc;

public:
    Aircraft(int _id, AirTrafficController& _atc) : id(_id), atc(_atc) {}

    void enterTrafficPattern() {
        atc.lockSleepMutex();
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
        atc.unlockSleepMutex();
    }

    void exitTrafficPattern() {
        atc.lockSleepMutex();
        atc.decrementTrafficPatternCount();
        if (atc.getTrafficPatternCount() == 0) {
            atc.sleep();
            cout << "ATC falls asleep.\n";
        }
        atc.unlockSleepMutex();
    }
};

int main() {
    AirTrafficController atc;

    vector<thread> threads;

    // Create ten aircraft
    vector<Aircraft> aircrafts;
    for (int i = 1; i <= 10; ++i) {
        aircrafts.emplace_back(i, atc);
    }

    // Simulate incoming aircraft
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(&Aircraft::enterTrafficPattern, &aircrafts[i]);
        // Let's simulate the landing process (1 second)
        this_thread::sleep_for(chrono::seconds(1));
    }

    for (auto& t : threads) {
        t.join();
    }

    threads.clear();

    // Simulate exiting aircraft
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(&Aircraft::exitTrafficPattern, &aircrafts[i]);
        // Let's simulate the exiting process (1 second)
        this_thread::sleep_for(chrono::seconds(1));
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
