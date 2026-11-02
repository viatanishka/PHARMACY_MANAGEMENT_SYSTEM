#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class Medicine {
public:
    int id;
    string name;
    int quantity;
    double price;
    int day, month, year;

    Medicine(int i, string n, int q, double p,
             int d, int m, int y) {
        id = i;
        name = n;
        quantity = q;
        price = p;
        day = d;
        month = m;
        year = y;
    }

    void display() {
        cout << "\nMedicine ID: " << id;
        cout << "\nName: " << name;
        cout << "\nQuantity: " << quantity;
        cout << "\nPrice: Rs. " << price;
        cout << "\nExpiry Date: "
             << day << "/" << month << "/" << year;
        cout << "\n--------------------------\n";
    }
};

class Pharmacy {
private:
    vector<Medicine> medicines;

    // Compare expiry date with current date
    bool isExpired(Medicine m) {
        time_t now = time(0);
        tm *current = localtime(&now);

        int cy = current->tm_year + 1900;
        int cm = current->tm_mon + 1;
        int cd = current->tm_mday;

        if (m.year < cy) return true;
        if (m.year == cy && m.month < cm) return true;
        if (m.year == cy && m.month == cm &&
            m.day < cd) return true;

        return false;
    }

public:

    void addMedicine() {
        int id, quantity, d, m, y;
        string name;
        double price;

        cout << "\nEnter Medicine ID: ";
        cin >> id;

        for (auto &med : medicines) {
            if (med.id == id) {
                cout << "Medicine ID already exists!\n";
                return;
            }
        }

        cin.ignore();

        cout << "Enter Medicine Name: ";
        getline(cin, name);

        cout << "Enter Quantity: ";
        cin >> quantity;

        cout << "Enter Price: ";
        cin >> price;

        cout << "Enter Expiry Date (DD MM YYYY): ";
        cin >> d >> m >> y;

        if (quantity < 0 || price < 0 ||
            m < 1 || m > 12 || d < 1 || d > 31) {
            cout << "Invalid input!\n";
            return;
        }

        medicines.emplace_back(id, name, quantity,
                               price, d, m, y);

        cout << "\nMedicine added successfully!\n";
    }

    void displayMedicines() {
        if (medicines.empty()) {
            cout << "\nInventory is empty!\n";
            return;
        }

        for (auto &med : medicines) {
            med.display();
        }
    }

    void searchMedicine() {
        int id;
        cout << "\nEnter Medicine ID: ";
        cin >> id;

        for (auto &med : medicines) {
            if (med.id == id) {
                med.display();
                return;
            }
        }

        cout << "Medicine not found!\n";
    }

    void sellMedicine() {
        int id, qty;

        cout << "\nEnter Medicine ID: ";
        cin >> id;

        for (auto &med : medicines) {
            if (med.id == id) {

                if (isExpired(med)) {
                    cout << "Cannot sell expired medicine!\n";
                    return;
                }

                cout << "Enter quantity to sell: ";
                cin >> qty;

                if (qty <= 0 || qty > med.quantity) {
                    cout << "Invalid quantity or insufficient stock!\n";
                    return;
                }

                med.quantity -= qty;

                cout << "Sale successful!\n";
                cout << "Total Bill: Rs. "
                     << qty * med.price << endl;
                cout << "Remaining Stock: "
                     << med.quantity << endl;
                return;
            }
        }

        cout << "Medicine not found!\n";
    }

    void checkExpiry() {
        bool found = false;

        cout << "\n--- Expiry Report ---\n";

        for (auto &med : medicines) {
            if (isExpired(med)) {
                cout << "\nEXPIRED MEDICINE:";
                med.display();
                found = true;
            }
        }

        if (!found) {
            cout << "No expired medicines found!\n";
        }
    }

    void updateQuantity() {
        int id, qty;

        cout << "\nEnter Medicine ID: ";
        cin >> id;

        for (auto &med : medicines) {
            if (med.id == id) {
                cout << "Enter new quantity: ";
                cin >> qty;

                if (qty < 0) {
                    cout << "Invalid quantity!\n";
                    return;
                }

                med.quantity = qty;
                cout << "Stock updated successfully!\n";
                return;
            }
        }

        cout << "Medicine not found!\n";
    }

    void deleteMedicine() {
        int id;

        cout << "\nEnter Medicine ID: ";
        cin >> id;

        for (int i = 0; i < medicines.size(); i++) {
            if (medicines[i].id == id) {
                medicines.erase(medicines.begin() + i);
                cout << "Medicine deleted successfully!\n";
                return;
            }
        }

        cout << "Medicine not found!\n";
    }
};

int main() {
    Pharmacy p;
    int choice;

    do {
        cout << "\n====== PHARMACY MANAGEMENT SYSTEM ======\n";
        cout << "1. Add Medicine\n";
        cout << "2. Display All Medicines\n";
        cout << "3. Search Medicine\n";
        cout << "4. Sell Medicine\n";
        cout << "5. Check Expired Medicines\n";
        cout << "6. Update Stock\n";
        cout << "7. Delete Medicine\n";
        cout << "8. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                p.addMedicine();
                break;

            case 2:
                p.displayMedicines();
                break;

            case 3:
                p.searchMedicine();
                break;

            case 4:
                p.sellMedicine();
                break;

            case 5:
                p.checkExpiry();
                break;

            case 6:
                p.updateQuantity();
                break;

            case 7:
                p.deleteMedicine();
                break;

            case 8:
                cout << "Thank you for using Pharmacy System!\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 8);

    return 0;
}
