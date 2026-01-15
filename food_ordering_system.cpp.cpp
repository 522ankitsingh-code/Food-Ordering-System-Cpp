#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class FoodItem {
public:
    int id;
    string name;
    double price;

    FoodItem(int i, string n, double p) {
        id = i;
        name = n;
        price = p;
    }
};

class Order {
public:
    vector<FoodItem> orderedItems;

    void addItem(FoodItem item) {
        orderedItems.push_back(item);
    }

    double calculateBill() {
        double total = 0;
        for (auto &item : orderedItems)
            total += item.price;
        return total;
    }

    void displayOrder() {
        cout << "\nYour Order Summary:\n";
        for (auto &item : orderedItems)
            cout << item.name << " - Rs." << item.price << endl;
        cout << "---------------------------\n";
        cout << "Total Bill: Rs." << calculateBill() << endl;
    }

    void saveToFile() {
        ofstream file("orders.txt", ios::app);
        file << "----- New Order -----\n";
        for (auto &item : orderedItems)
            file << item.name << " - Rs." << item.price << "\n";
        file << "Total Bill: Rs." << calculateBill() << "\n\n";
        file.close();
    }
};

class Restaurant {
public:
    vector<FoodItem> menu;

    Restaurant() {
        menu.push_back(FoodItem(1, "Burger", 99));
        menu.push_back(FoodItem(2, "Pizza", 149));
        menu.push_back(FoodItem(3, "Pasta", 129));
        menu.push_back(FoodItem(4, "Fries", 79));
        menu.push_back(FoodItem(5, "Coke", 49));
    }

    void displayMenu() {
        cout << "\n===== FOOD MENU =====\n";
        for (auto &item : menu)
            cout << item.id << ". " << item.name << " - Rs." << item.price << endl;
        cout << "=====================\n";
    }

    FoodItem* getItemById(int id) {
        for (auto &item : menu)
            if (item.id == id) return &item;
        return nullptr;
    }
};

int main() {
    Restaurant r;
    Order o;
    int choice;

    cout << "🍔 Welcome to Ankit's Cafe! 🍕\n";

    while (true) {
        r.displayMenu();
        cout << "Enter item ID to order (0 to finish): ";
        cin >> choice;

        if (choice == 0) break;

        FoodItem* item = r.getItemById(choice);
        if (item) {
            o.addItem(*item);
            cout << item->name << " added to your order.\n";
        } else {
            cout << "Invalid choice!\n";
        }
    }

    o.displayOrder();
    o.saveToFile();
    cout << "\nYour order has been saved successfully. Thank you for visiting! 😊\n";

    return 0;
}
