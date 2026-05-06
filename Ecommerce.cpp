#include <iostream>
#include <string>

using namespace std;

// Constants
const int MAX_PRODUCTS = 5;
const int MAX_CART = 3;

// 1. ABSTRACTION
class Product {
private:
    // 2. ENCAPSULATION
    int id;
    string name;
    double price;
    int stock;

public:
    Product(int i, string n, double p, int s) : id(i), name(n), price(p), stock(s) {}

    int getId()      { return id; }
    string getName() { return name; }
    double getPrice(){ return price; }
    int getStock()   { return stock; }
    void reduceStock(int q) { stock -= q; }

    virtual void display() = 0;
    virtual void checkout() = 0;
    virtual ~Product() {}
};

// 3. INHERITANCE - Physical
class PhysicalProduct : public Product {
    double weight;
public:
    PhysicalProduct(int i, string n, double p, int s, double w) : Product(i, n, p, s), weight(w) {}

    // 4. POLYMORPHISM
    void display() override {
        cout << "| #" << getId() << " | " << getName() << " (Phys) | $" << getPrice() << " | Stock: " << getStock() << endl;
    }
    void checkout() override {
        cout << " >> Shipping " << getName() << " [" << weight << "kg] to your address." << endl;
    }
};

// 3. INHERITANCE - Digital
class DigitalProduct : public Product {
    string url;
public:
    DigitalProduct(int i, string n, double p, int s, string u) : Product(i, n, p, s), url(u) {}

    void display() override {
        cout << "| #" << getId() << " | " << getName() << " (Digi) | $" << getPrice() << " | Stock: " << getStock() << endl;
    }
    void checkout() override {
        cout << " >> Access granted for " << getName() << ". Link: " << url << endl;
    }
};

class Cart {
    Product* items[MAX_CART];
    int qty[MAX_CART];
    int count = 0;

public:
    bool add(Product* p, int q) {
        if (count >= MAX_CART) { cout << "\n [!] CART FULL (Limit 3 items)\n"; return false; }
        if (p->getStock() < q) { cout << "\n [!] INSUFFICIENT STOCK\n"; return false; }
        
        items[count] = p;
        qty[count] = q;
        count++;
        cout << "\n [+] Added " << q << " unit(s) of " << p->getName() << endl;
        return true;
    }

    void view() {
        if (count == 0) { cout << "\n --- Your cart is empty ---\n"; return; }
        double total = 0;
        cout << "\n----------------------------------------\n";
        cout << "             CURRENT CART               \n";
        cout << "----------------------------------------\n";
        for (int i = 0; i < count; i++) {
            double sub = items[i]->getPrice() * qty[i];
            cout << " - " << items[i]->getName() << " (x" << qty[i] << "): $" << sub << endl;
            total += sub;
        }
        cout << "----------------------------------------\n";
        cout << " TOTAL AMOUNT: $" << total << endl;
        cout << "----------------------------------------\n";
    }

    void process() {
        if (count == 0) return;
        cout << "\n========================================\n";
        cout << "          ORDER CONFIRMATION            \n";
        cout << "========================================\n";
        for (int i = 0; i < count; i++) {
            items[i]->checkout();
            items[i]->reduceStock(qty[i]);
        }
        count = 0;
        cout << "\n Transaction Successful. Thank you!\n";
        cout << "========================================\n";
    }
};

int main() {
    Product* list[MAX_PRODUCTS];
    list[0] = new PhysicalProduct(1, "Keyboard", 45.0, 100, 1.5);
    list[1] = new DigitalProduct(2, "Game Key", 20.0, 50, "steam.com/redeem");
    list[2] = new PhysicalProduct(3, "Monitor", 150.0, 85, 4.2);
    list[3] = new DigitalProduct(4, "Software", 30.0, 20, "example.com/download");
    list[4] = new PhysicalProduct(5, "Headphones", 80.0, 65, 0.5);
    int totalP = 5;

    Cart myCart;
    int choice = 0;

    cout << "----------------------------------------\n";
    cout << "       WELCOME TO THE MINI-SHOP         \n";
    cout << "----------------------------------------\n";

    while (choice != 5) {
        cout << "\n-----MAIN MENU----\n";
        cout << "1. View Products\n";
        cout << "2. Add to Cart\n";
        cout << "3. View Cart\n";
        cout << "4. Checkout\n";
        cout << "5. Exit\n";
        cout << "Selection: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\nAVAILABLE PRODUCTS\n";
            cout << "----------------------------------------\n";
            for (int i = 0; i < totalP; i++) list[i]->display();
            cout << "----------------------------------------\n";
        } 
        else if (choice == 2) {
            int id, q;
            cout << "Enter Product ID: "; cin >> id;
            cout << "Enter Quantity: "; cin >> q;
            bool found = false;
            for (int i = 0; i < totalP; i++) {
                if (list[i]->getId() == id) {
                    myCart.add(list[i], q);
                    found = true;
                    break;
                }
            }
            if (!found) cout << " [!] Product ID not found.\n";
        } 
        else if (choice == 3) {
            myCart.view();
        } 
        else if (choice == 4) {
            myCart.process();
        }
    }

    for (int i = 0; i < totalP; i++) delete list[i];
    cout << "\n---------------Program Executed-----------------\n";
    return 0;
}