#include <iostream>
#include <string>
#include <limits>
using namespace std;

bool readInteger(int &value)
{
    if (!(cin >> value))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

class EmergencySystem
{
private:

    static const int MAX_SIZE = 100;

    // Patient information
    struct Patient
    {
        int patientID;
        string name;
        int priority;
    };

    Patient patients[MAX_SIZE];

    int count;
    int nextPatientID;

    // Find the patient with the highest priority
    int highestPriorityIndex()
    {
        if (count == 0)
            return -1;

        int highest = 0;

        for (int i = 1; i < count; i++)
        {
            if (patients[i].priority >
                patients[highest].priority)
            {
                highest = i;
            }
        }

        return highest;
    }

    // Find patient using ID
    int findPatient(int id)
    {
        for (int i = 0; i < count; i++)
        {
            if (patients[i].patientID == id)
                return i;
        }

        return -1;
    }

public:

    // Constructor
    EmergencySystem()
    {
        count = 0;
        nextPatientID = 1;
    }

    // Check if system is empty
    bool isEmpty()
    {
        return count == 0;
    }

    // Check if system is full
    bool isFull()
    {
        return count == MAX_SIZE;
    }

    // Display priority categories
    void showPriorities()
    {
        cout << "\n===== PRIORITY LEVELS =====\n";
        cout << "1. Routine\n";
        cout << "2. Serious\n";
        cout << "3. Critical\n";
        cout << "4. Emergency\n";
        cout << "5. Life-threatening\n";
    }

    // 1. Register patient
    void registerPatient()
    {
        if (isFull())
        {
            cout << "\nPatient list is full!\n";
            return;
        }

        Patient newPatient;

        newPatient.patientID = nextPatientID++;

        cout << "\nEnter patient name: ";
        getline(cin, newPatient.name);

        newPatient.priority = 1;

        patients[count] = newPatient;

        count++;

        cout << "\nPatient registered successfully!\n";
        cout << "Patient ID: "
             << newPatient.patientID << endl;

        cout << "Default Priority: Routine\n";
    }

    // 2. Assign or update priority
    void assignPriority()
    {
        if (isEmpty())
        {
            cout << "\nNo patients registered.\n";
            return;
        }

        int id;
        int priority;

        cout << "\nEnter Patient ID: ";
        if (!readInteger(id))
        {
            cout << "\nInvalid patient ID!\n";
            return;
        }

        int index = findPatient(id);

        if (index == -1)
        {
            cout << "\nPatient not found!\n";
            return;
        }

        showPriorities();

        cout << "\nEnter new priority (1-5): ";
        if (!readInteger(priority))
        {
            cout << "\nInvalid priority!\n";
            return;
        }

        if (priority < 1 || priority > 5)
        {
            cout << "\nInvalid priority!\n";
            return;
        }

        patients[index].priority = priority;

        cout << "\nPriority assigned successfully!\n";
    }

    // 3. View highest-priority patient
    void viewHighestPriority()
    {
        if (isEmpty())
        {
            cout << "\nNo patients waiting.\n";
            return;
        }

        int index = highestPriorityIndex();

        cout << "\n===== HIGHEST PRIORITY PATIENT =====\n";

        cout << "Patient ID: "
             << patients[index].patientID << endl;

        cout << "Name: "
             << patients[index].name << endl;

        cout << "Priority: "
             << patients[index].priority << endl;
    }

    // 4. Serve patient
    void servePatient()
    {
        if (isEmpty())
        {
            cout << "\nNo patients available to serve.\n";
            return;
        }

        int index = highestPriorityIndex();

        cout << "\nServing Patient:\n";

        cout << "Patient ID: "
             << patients[index].patientID << endl;

        cout << "Name: "
             << patients[index].name << endl;

        cout << "Priority: "
             << patients[index].priority << endl;

        // Remove served patient
        for (int i = index; i < count - 1; i++)
        {
            patients[i] = patients[i + 1];
        }

        count--;

        cout << "\nPatient served successfully!\n";
    }

    // 5. Display all waiting patients
    void displayPatients()
    {
        if (isEmpty())
        {
            cout << "\nNo patients waiting.\n";
            return;
        }

        cout << "\n===== WAITING PATIENTS =====\n";

        for (int i = 0; i < count; i++)
        {
            cout << "\nPatient ID: "
                 << patients[i].patientID;

            cout << "\nName: "
                 << patients[i].name;

            cout << "\nPriority: "
                 << patients[i].priority;

            cout << endl;
        }
    }

    // Show total patients
    void showPatientCount()
    {
        cout << "\nTotal waiting patients: "
             << count << endl;
    }
};


// MAIN FUNCTION
int main()
{
    EmergencySystem hospital;

    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "   EMERGENCY RESPONSE PRIORITY SYSTEM\n";
        cout << "====================================\n";

        cout << "1. Register Patient\n";
        cout << "2. Assign Priority\n";
        cout << "3. View Highest-Priority Patient\n";
        cout << "4. Serve Patient\n";
        cout << "5. Display Waiting Patients\n";
        cout << "6. Show Number of Patients\n";
        cout << "7. Exit\n";

        cout << "\nEnter your choice: ";

        if (!readInteger(choice))
        {
            cout << "\nInvalid choice. Enter a number from 1 to 7.\n";
            continue;
        }

        switch (choice)
        {
            case 1:
                hospital.registerPatient();
                break;

            case 2:
                hospital.assignPriority();
                break;

            case 3:
                hospital.viewHighestPriority();
                break;

            case 4:
                hospital.servePatient();
                break;

            case 5:
                hospital.displayPatients();
                break;

            case 6:
                hospital.showPatientCount();
                break;

            case 7:
                cout << "\nThank you for using the system!\n";
                break;

            default:
                cout << "\nInvalid choice. Try again.\n";
        }

    } while (choice != 7);
    return 0;
}
