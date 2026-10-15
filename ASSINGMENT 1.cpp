#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Abstract class for farming advice
class Advisory {
public:
    virtual void giveAdvice() const = 0;
    virtual ~Advisory() {}
};

// Base class
class Crop {
protected:
    string name;
    double area;
    string season;
    double yieldPerAcre;

    static int cropCount;

public:
    // Default constructor
    Crop() {
        name = "Unknown";
        area = 1;
        season = "Summer";
        yieldPerAcre = 1;
        cropCount++;
    }

    // Parameterized constructor
    Crop(string n, double a, string s, double y) {
        name = n;
        area = a;
        season = s;
        yieldPerAcre = y;
        cropCount++;
    }

    // Virtual destructor
    virtual ~Crop() {}

    // Calculate total yield
    virtual double calculateYield() const {
        return area * yieldPerAcre;
    }

    // Display crop details
    virtual void display() const {
        cout << "\nCrop Name: " << name;
        cout << "\nArea: " << area << " acres";
        cout << "\nSeason: " << season;
        cout << "\nYield per Acre: "
             << yieldPerAcre << " quintals";
        cout << "\nTotal Yield: "
             << calculateYield() << " quintals\n";
    }

    // Operator overloading
    bool operator>(const Crop& other) const {
        return calculateYield() > other.calculateYield();
    }

    // Save crop details
    virtual void saveData(ofstream& file) const {
        file << "Crop Name: " << name
             << ", Area: " << area
             << ", Season: " << season
             << ", Total Yield: " << calculateYield();
    }

    // Static member function
    static int getCropCount() {
        return cropCount;
    }
};

int Crop::cropCount = 0;

// Cereal crop class
class CerealCrop : public Crop, public Advisory {
private:
    string fertilizer;

public:
    CerealCrop(string n, double a, string s,
               double y, string f)
        : Crop(n, a, s, y) {
        fertilizer = f;
    }

    void display() const override {
        cout << "\n--- Cereal Crop ---";
        Crop::display();
        cout << "Fertilizer Type: "
             << fertilizer << "\n";
    }

    void giveAdvice() const override {
        cout << name
             << ": Use suitable fertilizer and "
             << "check soil moisture regularly.\n";
    }

    void saveData(ofstream& file) const override {
        Crop::saveData(file);
        file << ", Fertilizer: " << fertilizer << "\n";
    }
};

// Vegetable crop class
class VegetableCrop : public Crop, public Advisory {
private:
    int irrigation;

public:
    VegetableCrop(string n, double a, string s,
                  double y, int i)
        : Crop(n, a, s, y) {
        irrigation = i;
    }

    void display() const override {
        cout << "\n--- Vegetable Crop ---";
        Crop::display();
        cout << "Irrigation Frequency: "
             << irrigation << " times per week\n";
    }

    void giveAdvice() const override {
        cout << name
             << ": Maintain proper irrigation and "
             << "check plants for pests.\n";
    }

    void saveData(ofstream& file) const override {
        Crop::saveData(file);
        file << ", Irrigation: "
             << irrigation << " times per week\n";
    }
};

int main() {
    string name, season, fertilizer;
    double area, yield;
    int irrigation;

    cout << "=================================\n";
    cout << "   SMART FARM MANAGEMENT SYSTEM\n";
    cout << "=================================\n";

    // Enter cereal crop information
    cout << "\nEnter cereal crop name: ";
    if (!(cin >> name)) return 0;

    cout << "Enter area in acres: ";
    if (!(cin >> area) || area <= 0) {
        cout << "Please enter a positive area.\n";
        return 0;
    }

    cout << "Enter season: ";
    if (!(cin >> season)) return 0;

    cout << "Enter yield per acre: ";
    if (!(cin >> yield) || yield <= 0) {
        cout << "Please enter a positive yield.\n";
        return 0;
    }

    cout << "Enter fertilizer type: ";
    if (!(cin >> fertilizer)) return 0;

    CerealCrop cereal(name, area, season, yield, fertilizer);

    // Enter vegetable crop information
    cout << "\nEnter vegetable crop name: ";
    if (!(cin >> name)) return 0;

    cout << "Enter area in acres: ";
    if (!(cin >> area) || area <= 0) {
        cout << "Please enter a positive area.\n";
        return 0;
    }

    cout << "Enter season: ";
    if (!(cin >> season)) return 0;

    cout << "Enter yield per acre: ";
    if (!(cin >> yield) || yield <= 0) {
        cout << "Please enter a positive yield.\n";
        return 0;
    }

    cout << "Enter irrigation times per week: ";
    if (!(cin >> irrigation) || irrigation <= 0) {
        cout << "Please enter a positive number.\n";
        return 0;
    }

    VegetableCrop vegetable(name, area, season, yield, irrigation);

    // Runtime polymorphism
    Crop* crop1 = &cereal;
    Crop* crop2 = &vegetable;

    cout << "\n========== CROP DETAILS ==========\n";
    crop1->display();
    crop2->display();

    // Calculate combined yield
    double totalYield = crop1->calculateYield()
                      + crop2->calculateYield();

    cout << "\nCombined Total Yield: "
         << totalYield << " quintals\n";

    // Compare crop yields
    cout << "\n========== YIELD COMPARISON ==========\n";

    if (*crop1 > *crop2) {
        cout << "The cereal crop has a higher yield.\n";
    }
    else if (*crop2 > *crop1) {
        cout << "The vegetable crop has a higher yield.\n";
    }
    else {
        cout << "Both crops have equal yields.\n";
    }

    // Display farming advice
    cout << "\n========== FARMING ADVICE ==========\n";
    cereal.giveAdvice();
    vegetable.giveAdvice();

    // Attempt to save crop data
    ofstream outFile("crop_data.txt");

    if (outFile.is_open()) {
        crop1->saveData(outFile);
        crop2->saveData(outFile);
        outFile.close();

        cout << "\nCrop data saved successfully.\n";

        // Read the saved information
        ifstream inFile("crop_data.txt");

        if (inFile.is_open()) {
            cout << "\n========== SAVED CROP DATA ==========\n";

            string line;
            while (getline(inFile, line)) {
                cout << line << "\n";
            }

            inFile.close();
        }
        else {
            cout << "Saved data could not be read.\n";
        }
    }
    else {
        cout << "\nFile storage is unavailable in this compiler.\n";
        cout << "Crop calculations are complete.\n";
    }

    // Display crop count
    cout << "\nTotal Crops Created: "
         << Crop::getCropCount() << "\n";

    cout << "\nProgram completed successfully.\n";

    return 0;
}
