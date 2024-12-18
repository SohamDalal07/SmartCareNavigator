#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Structure to hold hospital data
struct Hospital {
    string name;
    double bedCharge;       // Cost per night for a bed
    double pathologyCharge;  // Cost for pathology services
    double operationCost;    // Base cost for the operation

    Hospital(string n, double bed, double pathology, double operation)
        : name(n), bedCharge(bed), pathologyCharge(pathology), operationCost(operation) {}

    double totalCost() const {
        return bedCharge + pathologyCharge + operationCost; // Total cost without nights
    }
};

// Function to display hospital options based on budget
void suggestHospitals(const vector<Hospital>& hospitals, double budget) {
    cout << "\nHospitals within your budget:\n";
    bool found = false;

    for (const auto& hospital : hospitals) {
        double total = hospital.totalCost();
        if (total <= budget) {
            cout << "Hospital: " << hospital.name
                 << ", Total Cost: $" << total << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No hospitals found within your budget." << endl;
    }
}

// Function to calculate operation cost based on disease
double calculateOperationCost(const string& disease) {
    // Mapping of diseases to their operation costs
    unordered_map<string, double> diseaseCosts = {
        {"appendicitis", 1500},
        {"fracture", 2000},
        {"hernia", 1200},
        {"gallbladder", 1800},
        {"heart surgery", 5000}
    };

    auto it = diseaseCosts.find(disease);
    if (it != diseaseCosts.end()) {
        return it->second; // Return the cost for the disease
    } else {
        cout << "Disease not recognized. Defaulting to $1000." << endl;
        return 1000; // Default cost for unrecognized diseases
    }
}

int main() {
    // Sample hospitals with their charges
    vector<Hospital> hospitals;
    int numHospitals;

    cout << "Enter the number of hospitals: ";
    cin >> numHospitals;

    // Input hospital data
    for (int i = 0; i < numHospitals; ++i) {
        string name;
        double bedCharge, pathologyCharge;

        cout << "\nEnter details for Hospital " << (i + 1) << ":\n";
        cout << "Hospital Name: ";
        cin >> name;
        cout << "Bed Charge: $";
        cin >> bedCharge;
        cout << "Pathology Charge: $";
        cin >> pathologyCharge;

        // Default operation cost, will be updated based on patient condition
        hospitals.emplace_back(name, bedCharge, pathologyCharge, 0);
    }

    // Patient input
    string disease;
    double budget;

    cout << "\nEnter your disease condition: ";
    cin >> disease;

    // Calculate operation cost based on disease
    double operationCost = calculateOperationCost(disease);

    cout << "Enter your budget: $";
    cin >> budget;

    // Update hospitals with the calculated operation cost
    for (auto& hospital : hospitals) {
        hospital.operationCost = operationCost; // Set operation cost based on disease
    }

    // Suggest hospitals based on budget
    suggestHospitals(hospitals, budget);

    return 0;
}
