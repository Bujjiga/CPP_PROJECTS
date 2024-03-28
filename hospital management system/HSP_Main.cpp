#include<bits/stdc++.h>
using namespace std;
class Doctor {
public:
    string name;
    string specialty;
    string shift;
    vector<string> unavailableDays;

    Doctor(string& n, string& s,  string& sh,const vector<string>& unav) : name(n), specialty(s), shift(sh), unavailableDays(unav) {}
};

class Patient {
public:
    string name;
    int age;
    string gender;
    bool admitted;
    int wardNumber;

    Patient( string& n, int a,  string& g) : name(n), age(a), gender(g), admitted(false) {}
};

class Ward {
public:
    int total;
    int reserved;

    Ward(int t) : total(t), reserved(0) {}

    // Function to update reserved wards when a patient is assigned
    void assignPatient() {
        reserved++;
    }

    // Function to update reserved wards when a patient is discharged
    void dischargePatient() {
        if (reserved > 0) {
            reserved--;
        }
    }

    // Function to get the number of free wards
    int getFreeWards()  {
        return total - reserved;
    }
};

class Appointment {
public:
    Patient patient;
    Doctor doctor;
    string date;

    Appointment( Patient& p,  Doctor& d,  string& dt) : patient(p), doctor(d), date(dt) {}
};

class Hospital {
public:
    vector<Doctor> doctors;
    vector<Patient> patients;
    vector<Appointment> appointments;
    vector<Ward> wards;

    Hospital() {
        // Initialize wards
        wards.push_back(Ward(10)); // Example: 10 total wards
    }
    void registerDoctor( Doctor& doctor) {
        doctors.push_back(doctor);
    }

    void registerPatient( Patient& patient) {
        patients.push_back(patient);
    }

    void scheduleAppointment( Patient& patient,  Doctor& doctor,  string& date) {
        Appointment appointment(patient, doctor, date);
        appointments.push_back(appointment);
    }

    void displayAppointments()  {
        cout << "Appointments:\n";
        for (auto it = appointments.begin(); it != appointments.end(); ++it) {
             Appointment& appointment = *it;
            cout << "Date: " << appointment.date << "\n";
            cout << "Patient: " << appointment.patient.name << "\n";
            cout << "Doctor: " << appointment.doctor.name << " (Specialty: " << appointment.doctor.specialty << ")\n";
            cout << "------------------------\n";
        }
    }

    int countAvailableWards()  {
        int totalWards = 0;
        int reservedWards = 0;

        for (auto it = wards.begin(); it != wards.end(); ++it) {
            totalWards += it->total;
            reservedWards += it->reserved;
        }

        return totalWards - reservedWards;
    }
    void assignWardToPatient(Patient& patient) {
    // Check if the patient is already admitted
    if (patient.admitted) {
        cout << "Patient " << patient.name << " is already admitted to Ward " << patient.wardNumber << ".\n";
        return;
    }

    // Find an available ward
    for (auto it = wards.begin(); it != wards.end(); ++it) {
        if (it->reserved < it->total) {
            // Assign the ward to the patient
            (*it).assignPatient();
            patient.admitted = true;
            patient.wardNumber = it->reserved;
            cout << "Patient " << patient.name << " assigned to Ward " << patient.wardNumber << ".\n";
            return;
        }

   else{
    cout << "No available wards. Cannot admit patient.\n";
}
}
}

// Helper function for case-insensitive string comparison
bool caseInsensitiveCharCompare(char c1, char c2) {
    return tolower(c1) == tolower(c2);
}


void dischargePatientFromWard(Patient& patient) {

        if (patient.admitted && patient.wardNumber > 0) {
            // Find the ward and discharge the patient
            for (auto it = wards.begin(); it != wards.end(); ++it) {
                if (it->reserved > 0) {
                    it->dischargePatient();
                    patient.admitted = false;
                    cout << "Patient " << patient.name << " discharged from Ward " << patient.wardNumber << ".\n";
                    patient.wardNumber = 0; // Reset the ward number
                    return;
                }
            }
        } else {
            cout << "Patient " << patient.name << " is not admitted to any ward.\n";
        }
    }


    void displayAvailableDoctors( string& shift,  string& day)  {
        cout << "Available Doctors:\n";
        for (auto it = doctors.begin(); it != doctors.end(); ++it) {
             Doctor& doctor = *it;
            if (doctor.shift == shift && find(doctor.unavailableDays.begin(), doctor.unavailableDays.end(), day) == doctor.unavailableDays.end()) {
                cout << "Doctor: " << doctor.name << " (Specialty: " << doctor.specialty << ")\n";
            }
        }
    }

    void prescribeMedicine( Patient& patient,  string& medicine) {
        cout << "Prescribing " << medicine << " to patient " << patient.name << ".\n";
    }

    // Function to get the number of total, reserved, and free wards
    void getWardInfo()  {
        for (auto it = wards.begin(); it != wards.end(); ++it) {
            cout << "Total Wards: " << it->total << "\n";
            cout << "Reserved Wards: " << it->reserved << "\n";
            cout << "Free Wards: " << it->getFreeWards() << "\n";
        }
    }
};

int main() {
    Hospital hospital;

    int choice;

    do {
        cout << "\n +++++++++ Hospital Management System +++++++++\n";
        cout << "1. Register Doctor\n";
        cout << "2. Register Patient\n";
        cout << "3. Schedule Appointment\n";
        cout << "4. View Appointments\n";
        cout << "5. Number of Wards\n";
        cout << "6. Available Doctors\n";
        cout << "7. Prescribe Medicine\n";
        cout << "8. Admit Patient & Assign Ward to Patient\n";
        cout << "9. Discharge Patient & Discharge Patient from Ward\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, specialty, shift;
                vector<string> unavailableDays;

                cout << "Enter Doctor's Name: ";
                cin >> name;
                cout << "Enter Doctor's Specialty: ";
                cin >> specialty;
                cout << "Enter Doctor's Shift (morning/night): ";
                cin >> shift;

                int dayCount;
                cout << "Enter the number of days the doctor is unavailable: ";
                cin >> dayCount;

                cout << "Enter the unavailable days (e.g., Monday Tuesday): ";
                for (int i = 0; i < dayCount; ++i) {
                    string day;
                    cin >> day;
                    unavailableDays.push_back(day);
                }

                Doctor doctor(name, specialty, shift, unavailableDays);
                hospital.registerDoctor(doctor);
                cout << "Doctor registered successfully!\n";
                break;
            }
            case 2: {
                string name, gender;
                int age;
                cout << "Enter Patient's Name: ";
                cin >> name;
                cout << "Enter Patient's Age: ";
                cin >> age;
                cout << "Enter Patient's Gender: ";
                cin >> gender;
                Patient patient(name, age, gender);
                hospital.registerPatient(patient);
                cout << "Patient registered successfully!\n";
                break;
            }
            case 3: {
                string patientName, doctorName, date;
                cout << "Enter Patient's Name: ";
                cin >> patientName;
                cout << "Enter Doctor's Name: ";
                cin >> doctorName;
                cout << "Enter Appointment Date (YYYY-MM-DD): ";
                cin >> date;

                // Find doctor and patient
                string s="";
              Doctor selectedDoctor(s, s, s, vector<string>());
                for (auto it = hospital.doctors.begin(); it != hospital.doctors.end(); ++it) {
                    if (it->name == doctorName) {
                        selectedDoctor = *it;
                        break;
                    }
                }

                Patient selectedPatient(s, 0, s);
                for (auto it = hospital.patients.begin(); it != hospital.patients.end(); ++it) {
                    if (it->name == patientName) {
                        selectedPatient = *it;
                        break;
                    }
                }

                if (selectedDoctor.name != s && selectedPatient.name != s) {
                    hospital.scheduleAppointment(selectedPatient, selectedDoctor, date);
                    cout << "Appointment scheduled successfully!\n";
                } else {
                    cout << "Doctor or patient not found. Please check the names and try again.\n";
                }
                break;
            }
            case 4: {
                hospital.displayAppointments();
                break;
            }
            case 5: {
                int totalWards = 0;
                int reservedWards = 0;

                for (auto it = hospital.wards.begin(); it != hospital.wards.end(); ++it) {
                    totalWards += it->total;
                    reservedWards += it->reserved;
                }

                cout << "Total Wards: " << totalWards << "\n";
                cout << "Reserved Wards: " << reservedWards << "\n";
                cout << "Free Wards: " << totalWards - reservedWards << "\n";
                break;
            }
            case 6: {
                string shift, day;
                cout << "Enter Shift (morning/night): ";
                cin >> shift;
                cout << "Enter Day (if applicable): ";
                cin >> day;
                hospital.displayAvailableDoctors(shift, day);
                break;
            }
            case 7: {
                string patientName, medicine;
                cout << "Enter Patient's Name: ";
                cin >> patientName;
                cout << "Enter Prescribed Medicine: ";
                cin >> medicine;

                // Find patient
                for (auto it = hospital.patients.begin(); it != hospital.patients.end(); ++it) {
                    if (it->name == patientName) {
                        hospital.prescribeMedicine(*it, medicine);
                        break;
                    }
                }
                break;
            }
            case 8: {
                 // Assign Ward to Patient
                string patientName;
                cout << "Enter Patient's Name: ";
                cin >> patientName;

                // Find patient
                for (auto   it = hospital.patients.begin(); it != hospital.patients.end(); ++it) {
                    if (it->name == patientName) {
                        hospital.assignWardToPatient(*it);
                        break;
                    }
                }
                hospital.getWardInfo(); // Display updated ward information
                break;

            }
            case 9: {
                // Discharge Patient from Ward
                string patientName;
                cout << "Enter Patient's Name: ";
                cin >> patientName;

                // Find patient
                for (auto it = hospital.patients.begin(); it != hospital.patients.end(); ++it) {
                    if (it->name == patientName) {
                        hospital.dischargePatientFromWard(*it);
                        break;
                    }
                }
                break;
            }
            case 0: {
                cout << "Exiting Hospital Management System.\n";
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

