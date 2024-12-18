#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <functional>

using namespace std;

// Patient structure to hold patient data
struct Patient {
    string name;
    int id;
    int severity; // Used for priority queue

    Patient(string n, int i, int s) : name(n), id(i), severity(s) {}
};

// Function to display patient information
void displayPatient(const Patient& patient) {
    cout << "Patient Name: " << patient.name
         << ", ID: " << patient.id
         << ", Severity: " << patient.severity << endl;
}

int main() {
    // Stack for last patient to be treated (LIFO)
    stack<Patient> treatmentStack;

    // Queue for patients waiting for treatment (FIFO)
    queue<Patient> waitingQueue;

    // Priority Queue for emergency patients (highest severity treated first)
    priority_queue<Patient, vector<Patient>,
        function<bool(const Patient&, const Patient&)>> emergencyQueue(
        [](const Patient& a, const Patient& b) { return a.severity < b.severity; });

    int numPatients;
    cout << "Enter the number of patients to register: ";
    cin >> numPatients;

    for (int i = 0; i < numPatients; ++i) {
        string name;
        int id, severity;
        char type;

        cout << "Enter patient name: ";
        cin >> name;
        cout << "Enter patient ID: ";
        cin >> id;
        cout << "Enter severity (1-5): ";
        cin >> severity;
        cout << "Is this an emergency patient? (y/n): ";
        cin >> type;

        Patient patient(name, id, severity);

        if (type == 'y' || type == 'Y') {
            emergencyQueue.push(patient); // Add to emergency queue
        } else {
            waitingQueue.push(patient); // Add to waiting queue
        }
    }

    // Simulate treatment from the emergency queue
    cout << "\nTreating emergency patients in order of severity:\n";
    while (!emergencyQueue.empty()) {
        Patient patient = emergencyQueue.top();
        emergencyQueue.pop();
        displayPatient(patient);
        treatmentStack.push(patient); // Push treated patient to stack
    }

    // Simulate treating regular patients from the waiting queue
    cout << "\nTreating regular patients in order of arrival:\n";
    while (!waitingQueue.empty()) {
        Patient patient = waitingQueue.front();
        waitingQueue.pop();
        displayPatient(patient);
        treatmentStack.push(patient); // Push treated patient to stack
    }

    // Display all treated patients (in reverse order of treatment)
    cout << "\nAll treated patients (most recent first):\n";
    while (!treatmentStack.empty()) {
        displayPatient(treatmentStack.top());
        treatmentStack.pop();
    }

    return 0;
}
