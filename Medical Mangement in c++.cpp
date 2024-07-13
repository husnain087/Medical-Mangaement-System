

//Here the my project named as Medical Managment system.
//I starte documentation because it helps me while coding ,to link one part oto other and under stand to code if error occurs during compilation
//I am Muhammad Husnain Haider
#include <iostream>//for input and output
#include <string>//for string data handling
#include <conio.h>//to convert passswrod into satric function is used so it is essential to use it
#include <iomanip>//for mainpulation of the output
#include <windows.h>//for sleep function
#include"HUSNAIN.h"//headerfile i maded and link with this
using namespace std;//namespace for output


void showMenu();//forwad declaration
void displayPatientData();//same as above
const int MAX_PATIENTS = 100;//global varibles for intiilizing array value
const int MAX_TESTS = 50;
const int MAX_MEDICINES = 50;
const int MAX_ITEMS = 100;

// now belw  the classsess start that tell how my program works.
class LabTest {
public:
    LabTest() {} // Default constructor
    LabTest(const string& testName, double price) : testName(testName), price(price) {}

    string getTestName() const { return testName; }
    double getPrice() const { return price; }

private:
    string testName;
    double price;
};

class LabResult {
public:
    LabResult() : patientId(-1) {} // Default constructor
    LabResult(int patientId, const string& testName, const string& result)
        : patientId(patientId), testName(testName), result(result) {}

    int getPatientId() const { return patientId; }
    string getTestName() const { return testName; }
    string getResult() const { return result; }

private:
    int patientId;
    string testName;
    string result;
};

class Patientt{
public:
    Patientt() : patientId(-1), age(-1) {} // Default constructor
    Patientt(int patientId, const string& name, int age, const string& gender)
        : patientId(patientId), name(name), age(age), gender(gender), selectedTestCount(0) {}

    int getPatientId() const { return patientId; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getGender() const { return gender; }
    void selectTest(const LabTest& test) { selectedTests[selectedTestCount++] = test; }
    int getSelectedTestCount() const { return selectedTestCount; }
    const LabTest* getSelectedTests() const { return selectedTests; }

private:
    int patientId;
    string name;
    int age;
    string gender;
    LabTest selectedTests[MAX_TESTS]; // Composition: Patient owns an array of LabTest objects
    int selectedTestCount;
};

class FinancialAnalysis {
public:
    void addMedicine(const string& name, double price) {
        if (medicineCount < MAX_MEDICINES) {
            medicines[medicineCount].name = name;
            medicines[medicineCount].price = price;
            ++medicineCount;
        } else {
            cerr << "Maximum medicine limit reached" << endl;
        }
    }

    double calculateTotal(const string* medicineList, int numMedicines) const {
        double total = 0;
        for (int i = 0; i < numMedicines; ++i) {
            for (int j = 0; j < medicineCount; ++j) {
                if (medicines[j].name == medicineList[i]) {
                    total += medicines[j].price;
                    break;
                }
            }
        }
        return total;
    }

    void displayBill(const string* medicineList, int numMedicines) const {
        double total = calculateTotal(medicineList, numMedicines);
        cout << "Medicine Bill:\n";
        for (int i = 0; i < numMedicines; ++i) {
            for (int j = 0; j < medicineCount; ++j) {
                if (medicines[j].name == medicineList[i]) {
                    cout << medicines[j].name << ": $" << medicines[j].price << "\n";
                    break;
                }
            }
        }
        cout << "Total: $" << total << "\n";
    }

    double getTotalRevenue() const { 
        double total = 0;
        for (int i = 0; i < medicineCount; ++i) {
            total += medicines[i].price;
        }
        return total;
    }

    void generateFinancialReport() const {
        cout << "Hospital Financial Report:\n";
        cout << "Total Revenue from Medicines: $" << getTotalRevenue() << "\n";
    }

private:
    struct Medicine {
        string name;
        double price;
    };

    Medicine medicines[MAX_MEDICINES];
    int medicineCount = 0;
};

class Inventory {
public:
    void addItem(const string& itemName, int quantity) {
        if (itemCount < MAX_ITEMS) {
            items[itemCount].name = itemName;
            items[itemCount].quantity = quantity;
            ++itemCount;
        } else {
            cerr << "Maximum item limit reached" << endl;
        }
    }

    void useItem(const string& itemName, int quantity) {
        for (int i = 0; i < itemCount; ++i) {
            if (items[i].name == itemName) {
                if (items[i].quantity >= quantity) {
                    items[i].quantity -= quantity;
                    cout << "Used " << quantity << " " << itemName << "(s)\n";
                } else {
                    cerr << "Insufficient stock for " << itemName << "\n";
                }
                return;
            }
        }
        cerr << "Item " << itemName << " not found in inventory\n";
    }

    void displayInventory() const {
        cout << "Inventory:\n";
        for (int i = 0; i < itemCount; ++i) {
            cout << items[i].name << ": " << items[i].quantity << "\n";
        }
    }

private:
    struct Item {
        string name;
        int quantity;
    };

    Item items[MAX_ITEMS];
    int itemCount = 0;
};

class Lab {
public:
    Lab() : patientCount(0), testCount(0), financialAnalysis(new FinancialAnalysis()), inventory(new Inventory()) {}
    ~Lab() {
        delete financialAnalysis;
        delete inventory;
    }

    void registerPatient(int patientId, const string& name, int age, const string& gender) {
        if (patientCount < MAX_PATIENTS) {
            patients[patientCount++] = Patientt(patientId, name, age, gender);
        } else {
            cerr << "Maximum patient limit reached" << endl;
        }
    }

    void addTest(const string& testName, double price) {
        if (testCount < MAX_TESTS) {
            tests[testCount++] = LabTest(testName, price);
        } else {
            cerr << "Maximum test limit reached" << endl;
        }
    }

    void listTests() const {
        cout << "Available tests:\n";
        for (int i = 0; i < testCount; ++i) {
            cout << i + 1 << ". " << tests[i].getTestName() << ": $" << tests[i].getPrice() << "\n";
        }
    }

    void selectTestsForPatient(int patientId) {
        Patientt* patient = getPatientById(patientId);
        if (patient) {
            int numTests;
            cout << "Enter number of tests to select: ";
            cin >> numTests;
            for (int i = 0; i < numTests; ++i) {
                int testIndex;
                cout << "Enter test number " << i + 1 << ": ";
                cin >> testIndex;
                if (testIndex > 0 && testIndex <= testCount) {
                    patient->selectTest(tests[testIndex - 1]);
                } else {
                    cerr << "Invalid test number" << endl;
                }
            }
        } else {
            cerr << "Patient not found" << endl;
        }
    }

    void displayBill(int patientId) const {
        const Patientt* patient = getPatientById(patientId);
        if (patient) {
            cout << "Bill for patient " << patient->getName() << ":\n";
            double totalBill = 0;
            for (int i = 0; i < patient->getSelectedTestCount(); ++i) {
                const LabTest& test = patient->getSelectedTests()[i];
                cout << test.getTestName() << ": $" << test.getPrice() << "\n";
                totalBill += test.getPrice();
            }
            cout << "Total: $" << totalBill << "\n";
        } else {
            cerr << "Patient not found" << endl;
        }
    }

    void addLabResult(int patientId, const string& testName, const string& result) {
        if (labResultCount < MAX_TESTS) {
            labResults[labResultCount++] = LabResult(patientId, testName, result);
        } else {
            cerr << "Maximum lab result limit reached" << endl;
        }
    }

    void displayLabResults(int patientId) const {
        cout << "Lab Results for patient " << patientId << ":\n";
        bool foundResults = false;
        for (int i = 0; i < labResultCount; ++i) {
            if (labResults[i].getPatientId() == patientId) {
                cout << labResults[i].getTestName() << ": " << labResults[i].getResult() << "\n";
                foundResults = true;
            }
        }
        if (!foundResults) {
            cerr << "No lab results found for patient " << patientId << endl;
        }
    }

    void showMenu() const {
        cout << "1. Register Patient\n";
        cout << "2. Add Test\n";
        cout << "3. List Tests\n";
        cout << "4. Select Tests for Patient\n";
        cout << "5. Display Bill\n";
        cout << "6. Add Lab Result\n";
        cout << "7. Display Lab Results\n";
        cout << "8. Inventory Management\n";
        cout << "9. Generate Financial Report\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
    }

    Inventory* getInventory() { return inventory; }
    FinancialAnalysis* getFinancialAnalysis() { return financialAnalysis; }

private:
    Patientt* getPatientById(int patientId) {
        for (int i = 0; i < patientCount; ++i) {
            if (patients[i].getPatientId() == patientId) {
                return &patients[i];
            }
        }
        return nullptr;
    }

    const Patientt* getPatientById(int patientId) const {
        for (int i = 0; i < patientCount; ++i) {
            if (patients[i].getPatientId() == patientId) {
                return &patients[i];
            }
        }
        return nullptr;
    }

    Patientt patients[MAX_PATIENTS];
    int patientCount;
    LabTest tests[MAX_TESTS];
    int testCount;
    LabResult labResults[MAX_TESTS];
    int labResultCount = 0;
    FinancialAnalysis* financialAnalysis; // Aggregation: Lab has a FinancialAnalysis
    Inventory* inventory; // Aggregation: Lab has an Inventory
};
void aggregationmenu(){
	   Lab lab;
	    int choice;
	  do {
        lab.showMenu();

       
        cin >> choice;

        switch (choice) {
            case 1: {
            	system("cls");
                int patientId, age;
                string name, gender;
                cout << "Enter patient ID: ";
                cin >> patientId;
                cin.ignore(); // Ignore newline character
                cout << "Enter patient name: ";
                getline(cin, name);
                cout << "Enter patient age: ";
                cin >> age;
                cin.ignore(); // Ignore newline character
                cout << "Enter patient gender: ";
                getline(cin, gender);
                lab.registerPatient(patientId, name, age, gender);
                break;
            }
            case 2: {	system("cls");
                string testName;
                double price;
                cout << "Enter test name: ";
                cin.ignore(); // Ignore newline character
                getline(cin, testName);
                cout << "Enter test price: ";
                cin >> price;
                lab.addTest(testName, price);
                break;
            }
            case 3:	system("cls");
                lab.listTests();
                break;
            case 4: {	system("cls");
                int patientId;
                cout << "Enter patient ID: ";
                cin >> patientId;
                lab.selectTestsForPatient(patientId);
                break;
            }
            case 5: {	system("cls");
                int patientId;
                cout << "Enter patient ID: ";
                cin >> patientId;
                lab.displayBill(patientId);
                break;
            }
            case 6: {	system("cls");
                int patientId;
                string testName, result;
                cout << "Enter patient ID: ";
                cin >> patientId;
                cout << "Enter test name: ";
                cin.ignore(); // Ignore newline character
                getline(cin, testName);
                cout << "Enter test result: ";
                getline(cin, result);
                lab.addLabResult(patientId, testName, result);
                break;
            }
            case 7: {	system("cls");
                int patientId;
                cout << "Enter patient ID: ";
                cin >> patientId;
                lab.displayLabResults(patientId);
                break;
            }
            case 8: {	system("cls");
                Inventory* inventory = lab.getInventory();
                int inventoryChoice;
                do {
                    cout << "\nInventory Management Menu:\n";
                    cout << "1. Add Item\n";
                    cout << "2. Use Item\n";
                    cout << "3. Display Inventory\n";
                    cout << "4. Exit Inventory Management\n";
                    cout << "Enter your choice: ";
                    cin >> inventoryChoice;

                    switch (inventoryChoice) {
                        case 1: {
                            string itemName;
                            int quantity;
                            cout << "Enter item name: ";
                            cin.ignore(); // Ignore newline character
                            getline(cin, itemName);
                            cout << "Enter quantity: ";
                            cin >> quantity;
                            inventory->addItem(itemName, quantity);
                            break;
                        }
                        case 2: {
                            string itemName;
                            int quantity;
                            cout << "Enter item name: ";
                            cin.ignore(); // Ignore newline character
                            getline(cin, itemName);
                            cout << "Enter quantity to use: ";
                            cin >> quantity;
                            inventory->useItem(itemName, quantity);
                            break;
                        }
                        case 3:
                            inventory->displayInventory();
                            break;
                        case 4:
                            break;
                        default:
                            cout << "Invalid choice. Please enter again.\n";
                    }
                } while (inventoryChoice != 4);
                break;
            }
            case 9: {	system("cls");
                FinancialAnalysis* financialAnalysis = lab.getFinancialAnalysis();
                financialAnalysis->generateFinancialReport();
                break;
            }
            case 10:
                cout << "Exiting program...\n";
              
            default:
                cout << "Invalid choice. Please enter again.\n";
        }
    }while(choice!=10);
}

class Doctorss {
private:
    string name;
    string specialization;
    int fee;
public:
    // Default constructor
    Doctorss() : name(""), specialization(""), fee(0) {}

    // Parameterized constructor
    Doctorss(const string& name, const string& specialization, int fee) 
        : name(name), specialization(specialization), fee(fee) {}

    // Getter method for fee
    int getFee() const {
        return fee;
    }

    // Method to display doctor's information
    string getInfo() const {
        return "Doctor Name: " + name + "\nSpecialization: " + specialization + "\nFee: " + to_string(fee) + " PKR";
    }
};

class Patientss {
private:
    string name;
    int budget;
public:
    Patientss(const string& name, int budget) : name(name), budget(budget) {}

    // Getter method for budget
    int getBudget() const {
        return budget;
    }

    // Method to display patient's information
    string getInfo() const {
        return "Patient Name: " + name + "\nBudget: " + to_string(budget) + " PKR";
    }
};

// Hospital class for aggregation
class hHospital {
private:
    Doctorss doctors[10];
    int size;
public:
    hHospital() : size(0) {
        initializeDoctors();
    }

    void initializeDoctors() {
        size = 10;
        doctors[0] = Doctorss("Dr. Smith", "Cardiologist", 25000);
        doctors[1] = Doctorss("Dr. Johnson", "Dermatologist", 15000);
        doctors[2] = Doctorss("Dr. Lee", "Psychiatrist", 30000);
        doctors[3] = Doctorss("Dr. Kim", "Orthopedic Surgeon", 45000);
        doctors[4] = Doctorss("Dr. White", "Neurologist", 35000);
        doctors[5] = Doctorss("Dr. Brown", "Ophthalmologist", 20000);
        doctors[6] = Doctorss("Dr. Clark", "Gynecologist", 40000);
        doctors[7] = Doctorss("Dr. Wilson", "Pediatrician", 30000);
        doctors[8] = Doctorss("Dr. Hall", "Urologist", 28000);
        doctors[9] = Doctorss("Dr. Miller", "Endocrinologist", 38000);
    }

    void displayAndBookAppointment(const Patientss& patient) const {
        cout << "Doctors within your budget:" << endl;
        for (int i = 0; i < size; ++i) {
            if (doctors[i].getFee() <= patient.getBudget()) {
                cout << i + 1 << ". " << doctors[i].getInfo() << endl;
            }
        }

        // Patient chooses a doctor
        int choice;
        cout << "Choose a doctor (enter the corresponding number): ";
        cin >> choice;

        if (choice > 0 && choice <= size && doctors[choice - 1].getFee() <= patient.getBudget()) {
            cout << "Appointment booked with the following doctor:" << endl;
            cout << doctors[choice - 1].getInfo() << endl;
            cout << patient.getInfo() << endl;
        } else {
            cout << "Invalid choice or insufficient budget." << endl;
        }
    }
};

// Function to take patient's input
Patientss getPatientInput() {
    string patientName;
    int patientBudget;
    cout << "Enter patient's name: ";
    cin >> patientName;
    cout << "Enter patient's budget (PKR)/only int: ";
    cin >> patientBudget;
    return Patientss(patientName, patientBudget);
}


class Patient {
protected:
    string name;
    int age;
    string gender;
    string cnic;
    string bloodGroup;
    string emergencyContact;

public:
    void inputBasicDetails() {
        cout << "Enter patient's name: ";
        getline(cin, name);
        cout << "Enter patient's age /only int: ";
        cin >> age;
        cin.ignore();  // Ignore the newline character left in the input buffer
        cout << "Enter patient's gender: ";
        getline(cin, gender);
        cout << "Enter patient's CNIC: ";
        getline(cin, cnic);
        cout << "Enter patient's blood group: ";
        getline(cin, bloodGroup);
        cout << "Enter patient's emergency contact: ";
        getline(cin, emergencyContact);
    }

    virtual void display() {
        cout << "Name: " << name << "\nAge: " << age << "\nGender: " << gender
             << "\nCNIC: " << cnic << "\nBlood Group: " << bloodGroup
             << "\nEmergency Contact: " << emergencyContact << endl;
    }
};



class MedicalHistory : public Patient {
protected:
    string medicalConditions;
    string medications;

public:
    void inputMedicalHistory() {
        cout << "Enter patient's medical conditions: ";
        getline(cin, medicalConditions);
        cout << "Enter patient's medications: ";
        getline(cin, medications);
    }

    void display() override {
        Patient::display();
        cout << "Medical Conditions: " << medicalConditions << "\nMedications: " << medications << endl;
    }
};

class Prescription:public Patient {
private:
    string* medicines;  // Composition: Prescription class owns the medicines array
    int numMedicines;

public:
    Prescription() : medicines(nullptr), numMedicines(0) {}

    ~Prescription() {
        delete[] medicines;  // Clean up allocated memory
    }

    void addMedicines(int num) {
        numMedicines = num;
        medicines = new string[numMedicines];
        for (int i = 0; i < numMedicines; ++i) {
            cout << "Enter name of Medicine " << i + 1 << ": ";
            getline(cin, medicines[i]);
        }
    }

    void display() const {
        cout << "Prescription Details:\n";
        for (int i = 0; i < numMedicines; ++i) {
            cout << "Medicine " << i + 1 << ": " << medicines[i] << "\n";
        }
    }
};

class Billing {
private:
    string* medicines;  // Composition: Billing class owns the medicines array
    double* prices;  // Composition: Billing class owns the prices array
    int numMedicines;
    double totalCost;

public:
    Billing() : medicines(nullptr), prices(nullptr), numMedicines(0), totalCost(0) {}

    ~Billing() {
        delete[] medicines;  // Clean up allocated memory
        delete[] prices;  // Clean up allocated memory
    }

    void buyMedicines(int num) {
        numMedicines = num;
        medicines = new string[numMedicines];
        prices = new double[numMedicines];
        for (int i = 0; i < numMedicines; ++i) {
            cout << "Enter name of Medicine " << i + 1 << ": ";
            getline(cin, medicines[i]);
            cout << "Enter price of Medicine /only int " << i + 1 << ": $";
            cin >> prices[i];
            cin.ignore(); // Clear newline character from input buffer
            totalCost += prices[i];
        }
    }

    void display() const {
        cout << "\nBilling Details:\n";
        for (int i = 0; i < numMedicines; ++i) {
            cout << "Medicine " << i + 1 << ": " << medicines[i] << " ($" << prices[i] << ")\n";
        }
        cout << "Total Bill: $" << totalCost << endl;
    }
};

    Billing billing;

void runHospitalManagementSystem() {
    int numPrescribed, numPurchased;

    // Input for Prescription
    cout << "Enter number of prescribed medicines /only int: ";
    cin >> numPrescribed;
    cin.ignore(); // Clear newline character from input buffer

    Prescription prescription;
    prescription.addMedicines(numPrescribed);  // Aggregation: Prescription object is part of the main function

    // Input for Billing
    cout << "\nEnter number of purchased medicines /only int: ";
    cin >> numPurchased;
    cin.ignore(); // Clear newline character from input buffer

    billing.buyMedicines(numPurchased);  // Aggregation: Billing object is part of the main function

    // Display Prescription and Billing details
  
    prescription.display();
 
}


class CheckInInfo : public MedicalHistory {
protected:
    string checkInDate;
    string department;

public:
    void inputCheckInInfo() {
        cout << "Enter check-in date: ";
        getline(cin, checkInDate);
        cout << "Enter department: ";
        getline(cin, department);
    }

    void display() override {
        MedicalHistory::display();
        cout << "Check-In Date: " << checkInDate << "\nDepartment: " << department << endl;
    }
};

class DemographicData : public CheckInInfo {
protected:
    string address;
    string phoneNumber;
    string language;

public:
    void inputDemographicData() {
        cout << "Enter patient's address: ";
        getline(cin, address);
        cout << "Enter patient's phone number/only int: ";
        getline(cin, phoneNumber);
        cout<<"Enter Patient's language";
        cin>>language;
    }

    void display() override {
        CheckInInfo::display();
        cout << "Address: " << address << "\nPhone Number: " << phoneNumber << "\nPatient language is :"<<language;
    }
    
    string getCNIC() const {
        return cnic;
    }
};

// Abstract class Receptionist
class Receptionist {
protected:
    string name;

public:
    Receptionist(string name) : name(name) {}

    virtual void registerPatient() = 0;
    virtual void scheduleAppointment() = 0;
    virtual void handleBilling() = 0;
    virtual void answerPhoneCalls() = 0;
    virtual void managePatientRecords() = 0;
    virtual void assistVisitors() = 0;

    virtual ~Receptionist() {}
};

class HospitalReceptionist : public Receptionist {
public:
    HospitalReceptionist(string name) : Receptionist(name) {}

    void registerPatient() override {
        cout << name << " is registering a patient." << endl;
    }

    void scheduleAppointment() override {
        cout << name << " is scheduling an appointment." << endl;
    }

    void handleBilling() override {
        cout << name << " is handling billing." << endl;
    }

    void answerPhoneCalls() override {
        cout << name << " is answering phone calls." << endl;
    }

    void managePatientRecords() override {
        cout << name << " is managing patient records." << endl;
    }

    void assistVisitors() override {
        cout << name << " is assisting visitors." << endl;
    }
};

class CleaningStaff {
private:
    string name;
    string area;

public:
    CleaningStaff(string name, string area) : name(name), area(area) {}

    void cleanArea() {
        cout << name << " is cleaning the " << area << "." << endl;
    }

    void disposeWaste() {
        cout << name << " is disposing of waste in the " << area << "." << endl;
    }
};

class Guard {
private:
    string name;
    string area;

public:
    Guard(string name, string area) : name(name), area(area) {}

    void monitorEntrance() {
        cout << name << " is monitoring the entrance of the " << area << "." << endl;
    }

    void checkIDs() {
        cout << name << " is checking IDs in the " << area << "." << endl;
    }
};

class Hospital {
private:
    Receptionist* receptionist; // Abstract class pointer
    CleaningStaff* cleaningStaff[10]; // Aggregation
    Guard* guards[10]; // Aggregation
    int cleaningStaffCount;
    int guardCount;

public:
    Hospital(string receptionistName) : cleaningStaffCount(0), guardCount(0) {
        receptionist = new HospitalReceptionist(receptionistName); // Initialize the receptionist
    }

    void addCleaningStaff(CleaningStaff* staff) {
        if (cleaningStaffCount < 10) {
            cleaningStaff[cleaningStaffCount++] = staff;
        }
    }

    void addGuard(Guard* guard) {
        if (guardCount < 10) {
            guards[guardCount++] = guard;
        }
    }

    void hospitalDuties() {
        receptionist->registerPatient();
        receptionist->scheduleAppointment();
        receptionist->handleBilling();
        receptionist->answerPhoneCalls();
        receptionist->managePatientRecords();
        receptionist->assistVisitors();

        for (int i = 0; i < cleaningStaffCount; ++i) {
            cleaningStaff[i]->cleanArea();
            cleaningStaff[i]->disposeWaste();
        }

        for (int i = 0; i < guardCount; ++i) {
            guards[i]->monitorEntrance();
            guards[i]->checkIDs();
        }
    }

    ~Hospital() {
        delete receptionist;
        for (int i = 0; i < cleaningStaffCount; ++i) {
            delete cleaningStaff[i];
        }
        for (int i = 0; i < guardCount; ++i) {
            delete guards[i];
        }
    }
};

// Function to perform all setup tasks
Hospital* setupHospital() {

    string receptionistName;
    cout << "Enter the receptionist's name: ";
    cin>>receptionistName;

    Hospital* hospital = new Hospital(receptionistName);

    int numCleaningStaff, numGuards;
    cout << "Enter the number of cleaning staff//only integers: ";
    cin >> numCleaningStaff;
    cin.ignore(); // to ignore the newline character left in the buffer

    for (int i = 0; i < numCleaningStaff; ++i) {
        string name, area;
        cout << "Enter the name of cleaning staff " << i + 1 << ": ";
        getline(cin, name);
        cout << "Enter the area of responsibility for cleaning staff " << i + 1 << ": ";
        getline(cin, area);
        CleaningStaff* cleaner = new CleaningStaff(name, area);
        hospital->addCleaningStaff(cleaner);
    }

    cout << "Enter the number of guards// only integers: ";
    cin >> numGuards;
    cin.ignore(); // to ignore the newline character left in the buffer

    for (int i = 0; i < numGuards; ++i) {
        string name, area;
        cout << "Enter the name of guard " << i + 1 << ": ";
        getline(cin, name);
        cout << "Enter the area of responsibility for guard " << i + 1 << ": ";
        getline(cin, area);
        Guard* guard = new Guard(name, area);
        hospital->addGuard(guard);
    }

    return hospital;
}






class User {
private:
    string username;
    string password;

public:
    User() {}

    User(string& username, string& password) : username(username), password(password) {}

    void createID() {
        cout << "\n\t*Create your user id*" << endl;
        cout << "\tEnter User Name: ";
        cin >> username;
        
       char ch;
    password.clear();
    cout << "Enter password: ";
    while ((ch = _getch()) != '\r') { 
        if (ch == '\b') { 
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; 
            }
        } else {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
        system("cls");
        cout << "\n\tYour ID is creating..........." << endl;
        for (int i = 0; i < 5; ++i) {
            cout << ".";
            Sleep(500); 
        }
        system("cls");
    }

    bool validate(string& inputUsername, string& inputPassword) {
        return (username == inputUsername && password == inputPassword);
    }

    string getUsername() {
        return username;
    }

    string getPassword() {
        return password;
    }

    void setPassword(const string& newPassword) {
        password = newPassword;
    }
};

class LoginSystem :public MedicalManagementSystem{



private:
    User highLevelUser;
    User localUser;

public:
    LoginSystem() {}

    void createIDsForLevel(int levelChoice) {
        if (levelChoice == 1) {
            highLevelUser.createID();
        } else if (levelChoice == 2) {
            localUser.createID();
        } else {
            cout << "\n\t\tInvalid choice. Please choose either 1 or 2.\n";
        }
    }

    void startLogin(int levelChoice) {
        bool loginSuccess = false;

        do {
        	       		cout<<"\n\n";
cout<<setw(20)<<setfill(' ')<<""<<"   _____                _   _                                                 _   \n";
cout<<setw(20)<<setfill(' ')<<""<<"  / ____|              | | (_)                 /\\                            | |  \n";
cout<<setw(20)<<setfill(' ')<<""<<" | |     _ __ ___  __ _| |_ _ _ __   __ _     /  \\   ___ ___ ___  _   _ _ __ | |_ \n";
cout<<setw(20)<<setfill(' ')<<""<<" | |    | '__/ _ \\/ _` | __| | '_ \\ / _` |   / /\\ \\ / __/ __/ _ \\| | | | '_ \\| __|\n";
cout<<setw(20)<<setfill(' ')<<""<<" | |____| | |  __/ (_| | |_| | | | | (_| |  / ____ \\ (_| (_| (_) | |_| | | | | |_ \n";
cout<<setw(20)<<setfill(' ')<<""<<"  \\_____|_|  \\___|\\__,_|\\__|_|_| |_|\\__, | /_/    \\_\\___\\___\\___/ \\__,_|_| |_|\\__|\n";
cout<<setw(20)<<setfill(' ')<<""<<"                                     __/ |                                        \n";
cout<<setw(20)<<setfill(' ')<<"";   
        
        	cout << "\n\tID created successfully\n";
        	cout<<endl<<endl<<endl;
           
            string username, password;
            cout << "\n\tEnter User Name: ";
            cin >> username;
            
          char ch;
    password.clear();
    cout << "Enter password: ";
    while ((ch = _getch()) != '\r') { 
        if (ch == '\b') { 
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; 
            }
        } else {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
            system("cls");

            if (levelChoice == 1 && highLevelUser.validate(username, password)) {
                cout << "\n\t\tHigh-Level Login Successful\n";
                loginSuccess = true;
            } else if (levelChoice == 2 && localUser.validate(username, password)) {
                cout << "\n\t\tLocal System Login Successful\n";
                loginSuccess = true;
            } else {
                cout << "\n\t\tIncorrect Username or Password\n";
            }

            if (!loginSuccess) {
                cout << "\n\t\tPress any key to try again or press 'F' to reset password...\n";
                char choice = getch();
                if (choice == 'F' || choice == 'f') {
                    resetPassword(levelChoice);
                }
            }
        } while (!loginSuccess);

        if (levelChoice == 1) {
            highLevelFunctionality();
        } else if (levelChoice == 2) {
            localSystemFunctionality();
        }
    }
    DemographicData patient;

    void resetPassword(int levelChoice) {
        string newPass;
        cout << "\n\tEnter new password: ";
        cin >> newPass;
        if (levelChoice == 1) {
            highLevelUser.setPassword(newPass);
        } else if (levelChoice == 2) {
            localUser.setPassword(newPass);
        }
        cout << "\n\tPassword reset successfully!\n";
    }
    void check(){
    	   string cnicToCheck;
                bool found = false;
                cout << "Enter CNIC to check availability: ";        cin >> cnicToCheck;
                
                // Check availability directly on the patient instance
                if (patient.getCNIC() == cnicToCheck) {
                    found = true;
                    cout << "Patient with CNIC " << cnicToCheck << " is available.\n";
                    // Optionally display patient details
                    patient.display();
                }
                
                if (!found) {
                    cout << "Patient with CNIC " << cnicToCheck << " is not available.\n";
                }
	}

    void highLevelFunctionality() {countdown();    	
       
         bool exit = false;

    while (!exit)
{
	 cout << "\n\n\t\t\tWelcome, High-Level User!\n";
        cout << "\n\t\t\tHigh-Level User Menu\n";
        cout << "\t1. Appointement of Doctor\n";
        cout << "\t2. Switch to Local System Login\n";
        cout << "\t3. For gaving reminders to the patient\n";
        cout << "\t4. For check avaiable of patient by cnic\n";
        cout << "\t5. For Proceed TO Reciopnist System\n";
        cout << "\tEnter Your Choice: ";

        int choice;
        cin >> choice;
     

        if (choice==1) {
        	 system("cls");
            
                cout << "\n\t\tHigh-Level Functionality Selected\n";
   		  hHospital hospital;
    Patientss patient = getPatientInput();
 hospital.displayAndBookAppointment(patient);
               
        }
        else if(choice==2)
        {
        system("cls");
                cout << "\n\t\tRedirecting to Local System Login...\n";
                redirectLocal();
                localUser.createID();
                startLogin(2);  
			}
			else if(choice==3){system("cls");
				 MedicalManagementSystem system;
    system.runSystem();
 
                       
			}
			else if(choice==4){  
			  check();				 
				 
				
			}
			else if(choice==5){system("cls");
				 Hospital* hospital = setupHospital();
				 	hospital->hospitalDuties();
			}
			else if(choice==6){
			
			}
			else{
				cout<<"ajg";
			}
		}
	}
		
     
    void redirectLocal() {
        const int numDots = 5;
        const int delaySeconds = 1;

        cout << "\n\t\t\tRedirecting to Local System Login...\n";

        for (int i = 0; i < numDots; ++i) {
            cout << ".";
            Sleep(delaySeconds * 1000); // Changed to milliseconds
        }

        cout << " Complete!\n";
        system("cls");
    }
    public:



 void localSystemFunctionality() {countdown();  
    cout << "\n\n\t\t\tWelcome, Local System User!\n";
    cout << "Add functions as you want\n"<<endl;
    int choice;
    bool exit = false;

    while (!exit) { 
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;
      
        cin.ignore(); 
		  system("cls"); // Ignore the newline character left in the input buffer

        if(choice==1) {
           
            
                patient.inputBasicDetails();
                system("cls");
          }
            else if(choice==2){
			
                patient.inputMedicalHistory();
                system("cls");
                
            }
           else if(choice==3)
           {
		   
                patient.inputCheckInInfo();
                system("cls");
              }
         else if(choice==4)
         {
		 
                patient.inputDemographicData();
                system("cls");
              }
            else if(choice==5)
            {
			
                patient.display();
             }
            else if(choice==6){
              check();
              cout<<"Furthur proceddedd"<<endl;
                aggregationmenu();
            }
          else if(choice==7){
		  
            
            	  highLevelFunctionality();
				              	}
        
		   else if(choice==8)
		   {
		   	 runHospitalManagementSystem();
		  
          }
          else if(choice==9){
          	   billing.display();
		  }
           else{
		   
                cout << "Invalid choice, please try again.\n";
        }
    }
}
};



    

void loadingBar() {
    char a = 177, b = 219;
    cout << "\n\n\t\t\t\t\t\t Loading...\n\n";
    cout << "\t\t\t\t\t";

    for (int i = 0; i < 26; i++) {
        cout << a;
    }
    cout << "\r\t\t\t\t\t";

    for (int i = 0; i < 26; i++) {
        cout << b;
        Sleep(50);
    }
    system("cls");
}

void showMenu() {
	
    cout << "Menu:\n";
    cout << "1. Enter Basic Details\n";
    cout << "2. Enter Medical History\n";
    cout << "3. Enter Check-In Information\n";
    cout << "4. Enter Demographic Data\n";
    cout << "5. Display Patient Data\n";
    cout << "6.Check avalibility by cnic to To Go for lab for tests\n";
     cout << "7.To Get into High level\n";
      cout << "8.For Buying Medicine\n";
    
    
}





int main() {
	          


    LoginSystem loginSystem;
    int levelChoice;

    do {
    	    cout << " __          __  _                            " << endl;
    cout<<"\t\t\t\t  "  << " \\ \\        / / | |                           " << endl;
    cout<<"\t\t\t\t  "  << "  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___   " << endl;
    cout<<"\t\t\t\t  "  << "   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\  " << endl;
    cout<<"\t\t\t\t  " << "    \\  /\\  /  __/ | (_| (_) | | | | | |  __/  " << endl;
   	cout<<"\t\t\t\t " << "     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  " << endl;
        loadingBar();
cout<<endl<<endl;
 displayMenuH();

        
        cin >> levelChoice;
        system("cls");
    } while (levelChoice != 1 && levelChoice != 2);

    loginSystem.createIDsForLevel(levelChoice);
    loginSystem.startLogin(levelChoice);
	}   

    
