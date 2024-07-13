#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <windows.h>



using namespace std;






void countdown(){ 
cout<<setw(40)<<setfill(' ')<<"This tab will  Open in 10 Seconds...\n\n";
	        for(int i = 1 ; i<=10 ; i++){
        	cout<<i<<"\t";
        	Sleep(300);
		}
        system("cls");

}
void displayMenuH() {
    int consoleWidth = 120; // Adjust this according to your console width
    int artWidth = 65; // Adjust this based on the width of your ASCII art

    // Calculate padding to center the ASCII art and menu
    int padding = (consoleWidth - artWidth) / 2;

    // Print newline characters to center the output vertically
    for (int i = 0; i < 10; ++i) {
        cout << endl;
    }




    cout << setw(padding + (artWidth - 27) / 2) << "" << "_    _  ____  __  __  ________ "<< endl;
    cout << setw(padding + (artWidth - 27) / 2) << "" << "| |  | |/ __ \\|  \\/  |/ ____|" << endl;
    cout << setw(padding + (artWidth - 27) / 2) << "" << "| |__| | |  | | \\  / | |  __  " << endl;
    cout << setw(padding + (artWidth - 27) / 2) << "" << "|  __  | |  | | |\\/| | | |_   " << endl;
    cout << setw(padding + (artWidth - 27) / 2) << "" << "| |  | | |__| | |  | | |__|    "<< endl;
    cout << setw(padding + (artWidth - 27) / 2) << "" << "|_|  |_|\\____/|_|  |_|\\_____|" << endl;
    cout << setw(padding + (artWidth - 27) / 2) << "" << "                               "<< endl;
   
    cout<<endl<<endl<<endl;

    // Print the menu options centered
    cout << setw(padding) << "" << "**********************************************************************" << endl;
    cout << setw(padding) << "" << "*                                                                    *" << endl;
    cout << setw(padding) << "" << "*                      *Choose Your Level*                           *" << endl;
    cout << setw(padding) << "" << "*                                                                    *" << endl;
    cout << setw(padding) << "" << "*                      1. High Level                                 *" << endl;
    cout << setw(padding) << "" << "*                      2. Local System                               *" << endl;
    cout << setw(padding) << "" << "*                     3. Exit  System                                *" << endl;
    cout << setw(padding) << "" << "*                       Enter Your Choice:                           *" << endl;
    cout << setw(padding) << "" << "*                                                                    *" << endl;
    cout << setw(padding) << "" << "*                                                                    *" << endl;
    cout << setw(padding) << "" << "**********************************************************************" << endl;

    // Print newline characters to center the output vertically
    for (int i = 0; i < 10; ++i) {
        cout << endl;
    }
}


class Notification {
public:
    string message;
    string alertTime; // Time in HH:MM format

    Notification() {}

    Notification(const string &msg, const string &time) : message(msg), alertTime(time) {}

    void display() const {
        cout << "Notification: " << message << " at " << alertTime << endl;
    }
};

class Patientees {
public:
    string name;
    string email;
    Notification notifications[10]; // Array to store up to 10 notifications
    int notificationCount;

    Patientees() : notificationCount(0) {}

    void addNotification(const string &message, const string &alertTime) {
        if (notificationCount < 10) {
            notifications[notificationCount++] = Notification(message, alertTime);
        } else {
            cout << "Cannot add more notifications, limit reached." << endl;
        }
    }

    void displayNotifications() const {
        for (int i = 0; i < notificationCount; ++i) {
            notifications[i].display();
        }
    }
};

class MedicalManagementSystem {
public:
    Patientees patients[10]; // Array to store up to 10 patients
    int patientCount;

    MedicalManagementSystem() : patientCount(0) {}

    void addPatient(const Patientees &patient) {
        if (patientCount < 10) {
            patients[patientCount++] = patient;
        } else {
            cout << "Cannot add more patients, limit reached." << endl;
        }
    }

    void displayAllNotifications() const {
        for (int i = 0; i < patientCount; ++i) {
            cout << "Notifications for " << patients[i].name << ":\n";
            patients[i].displayNotifications();
            cout << endl;
        }
    }

    void displayMenu() const {
        cout << "Medical Management System Menu\n";
        cout << "1. Add Patient and Notifications\n";
        cout << "2. Display All Notifications\n";
        cout << "3. Exit\n";
        cout << "Enter Your Choice: ";
    }

    void runSystem() {
        int choice;
        do {
            displayMenu();
            cin >> choice;
            cin.ignore(); // Clear the newline character from the input buffer

            switch (choice) {
                case 1: {system("cls");
                    int numPatients;
                    cout << "Enter the number of patients: ";
                    cin >> numPatients;
                    cin.ignore(); // Clear the newline character from the input buffer

                    for (int i = 0; i < numPatients; ++i) {
                        Patientees patient;
                        cout << "Enter patient name: ";
                        getline(cin, patient.name);
                        cout << "Enter patient email: ";
                        getline(cin, patient.email);

                        int numNotifications;
                        cout << "Enter the number of notifications for " << patient.name << ": ";
                        cin >> numNotifications;
                        cin.ignore(); // Clear the newline character from the input buffer

                        for (int j = 0; j < numNotifications; ++j) {
                            string message, alertTime;
                            cout << "Enter notification message: ";
                            getline(cin, message);
                            cout << "Enter alert time (HH:MM): ";
                            getline(cin, alertTime);

                            patient.addNotification(message, alertTime);
                        }

                        addPatient(patient);
                         system("cls");
                      
                    }
                    break;
                }
                case 2:
                	 system("cls");
                    displayAllNotifications();
                   
                    break;
                case 3:
                    cout << "Exiting...\n";
           
                   
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 3);
    }
};
