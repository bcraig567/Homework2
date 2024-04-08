#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int NUM_ROBOTS = 5;

int main() {
    queue<int> robots;
    vector<bool> tools(NUM_ROBOTS, false); // False means tool is available

    // Initialize the queue of robots
    for (int i = 0; i < NUM_ROBOTS; ++i) {
        robots.push(i);
    }

    int totalTime = 0;

    // Simulate until all tasks are completed
    while (!robots.empty()) {
        int currentRobot = robots.front();
        robots.pop();

        int nextRobot = robots.front();
        robots.push(currentRobot); // Move current robot to the end of the queue

        // Check if both tools are available
        if (!tools[currentRobot] && !tools[nextRobot]) {
            // Robot grabs both tools
            tools[currentRobot] = true;
            tools[nextRobot] = true;

            // Calculate time taken by the current robot
            int timeTaken = 1 + 5; // Time to grab tools and complete task
            totalTime += timeTaken;

            cout << "Robot " << currentRobot << " completed task in " << timeTaken << " seconds." << endl;
        }
    }

    cout << "Total time taken by all robots: " << totalTime << " seconds." << endl;

    return 0;
}
