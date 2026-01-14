#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <cctype>
#include <cstdlib>

struct Product {
    std::string name;
    int price;
};
struct node {
    Product data;
    node* next;
};
struct vending {
    node* slots[10][12] = {NULL};
    std::string position[10][12];
};

int notes[9] = { 500,200,100,50,20,10,5,2,1 };
int machineNotes[9];

void push(node* &n, Product p){
    node* newn = new node();
    newn->data = p;
    newn->next = n;
    n = newn;
}
node* pop(node* &n) {
    if (n == NULL) {
        return n;
    }
    else {
        node* temp = n;
        n = n->next;
        temp->next = NULL;
        return temp;
    }
}
Product peek(node* &n){
    if (n == NULL) {
        return Product{"",0};
    }
    return n->data;
}

void retrieveFromFiles(vending& a) {
    for (int i = 0; i < 10; i++) {
        char rowChar = 'A' + i;
        std::string fileName = std::string(1, rowChar) + ".txt";
        std::fstream fin;
        fin.open(fileName, std::ios::in);
        if (!fin.is_open()) {
            std::cout << "There was an error" << std::endl;
        }
        int slotNum, price;
        std::string name;
        while (fin >> slotNum >> std::quoted(name) >> price) {
            if (name.front() == '[' && name.back() == ']') {
                name = name.substr(1, name.size() - 2);
            }
            if (slotNum >= 1 && slotNum <= 12) {
                Product p{ name, price };
                push(a.slots[i][slotNum - 1], p);
            }
        }
        fin.close();
    }
}
void placement(vending& a) {
    for (int i = 0; i < 10; i++) {
        char row = 'A' + i;
        for (int j = 0; j < 12; j++) {
            int col = j + 1;
            a.position[i][j] = row + std::to_string(col);
            a.slots[i][j] = NULL;
        }
    }
    retrieveFromFiles(a);
}
void utf(vending& v, int i) {
    char rowchar = 'A' + i;
    std::string fileName = std::string(1,rowchar) + ".txt";
    std::fstream fout;
    fout.open(fileName, std::ios::out);
    if (!fout.is_open()) {
        fout.open(fileName, std::ios::out);
    }
    if (!fout.is_open()) {
        std::cout << "There was an error\n";
        return;
    }
    for (int j = 0; j < 12; j++) {
        node* temp = v.slots[i][j];
        while (temp != NULL) {
            fout << (j + 1)
                << " \"" << temp->data.name << "\" "
                << temp->data.price << "\n";
            temp = temp->next;
        }
    }
    fout.close();
}
void loadChangeFromFile() {
    std::fstream fin;
    fin.open("change.txt", std::ios::in);
    if (!fin.is_open()) {
        fin.open("change.txt", std::ios::in);
    }
    if (!fin.is_open()) {
        std::cout << "change.txt not found!\n";
        exit(0);
    }
    for (int i = 0; i < 9; i++) {
        fin >> machineNotes[i];
    }
    fin.close();
}
void saveChangeToFile() {
    std::fstream file;
    file.open("change.txt", std::ios::out);
    for (int i = 0; i < 9; i++) {
        file << notes[i] << " " << machineNotes[i] << "\n";
    }
    file.close();
}

void displaymachinelayout(vending &a) {
    std::cout << "\n========= VENDING MACHINE =========\n\n";

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 12; j++) {
            std::cout << "+--------------";
        }
        std::cout << "+\n| ";
        for (int j = 0; j < 12; j++) {
            std::cout << std::left << std::setw(12) << a.position[i][j] << " | ";
        }
        std::cout << "\n| ";

        for (int j = 0; j < 12; j++) {
            if (a.slots[i][j] != NULL)
                std::cout << std::left << std::setw(12) << a.slots[i][j]->data.name << " | ";
            else {
                std::cout << std::left << std::setw(12) << "Empty";
                std::cout << " | ";
            }
        }
        std::cout << "\n| ";
        for (int j = 0; j < 12; j++) {
            if (a.slots[i][j] != NULL) {
                std::cout << std::left << std::setw(12) << ("Rs." + std::to_string(a.slots[i][j]->data.price)) << " | ";
            }
            else {
                std::cout << std::left << std::setw(12) << "-----";
                std::cout << " | ";
            }
        }
        std::cout << std::endl;
    }
    for (int j = 0; j < 12; j++) {
        std::cout << "+--------------";
    }
    std::cout << "+";
}
void mainmenu() {
    std::cout << "\nWELCOME TO GONGIN VENDING MACHINE"
        << "\nPLEASE ENTER MODE TO ACCESS"
        << "\n1. Customer"
        << "\n2. Stock Manager"
        << "\n3. Admin"
        << "\n4. Exit"
        << "\nEnter your option: ";
}
void Adminmenu() {
    std::cout << "Admin menu"
        << "\n1. refill vending machine"
        << "\n2. update existing products"
        << "\n3. Remove item"
        << "\n4. view machine"
        << "\n5. Manage Money"
        << "\n6. Exit"
        << "\n7. Back"
        << "\nEnter your option: ";
}
void customermenu() {
    std::cout << "\nCustomer Menu"
        << "\n1. View machine"
        << "\n2. Buy something"
        << "\n3. Add amount"
        << "\n4. Exit"
        << "\n5. Back"
        << "\nEnter your option: ";
}
void StockManagermenu() {
    std::cout << "\nStock Manager Menu:\n"
        << "1. Refill a slot\n"
        << "2. Update a product\n"
        << "3. Remove a product\n"
        << "4. Refill entire machine\n"
        << "5. View machine\n"
        << "6. Back\n"
        << "Enter your option: ";
}

void refillVendingMachine(vending& v) {
    char rowChar;
    int col;
    std::string name;
    int price;
    std::cout << "Enter row (A-J) to refill: ";
    std::cin >> rowChar;
    std::cout << "Enter column (1-12) to refill: ";
    std::cin >> col;
    int row = toupper(rowChar) - 'A';
    int column = col - 1;
    std::cout << "Enter product name: ";
    std::cin.ignore();
    getline(std::cin, name);
    std::cout << "Enter product price: ";
    std::cin >> price;
    push(v.slots[row][column], Product{ name, price });
    std::cout << "Refilled " << name << " at " << rowChar << col << "\n";
    utf(v, row);
}
void updateProduct(vending& v) {
    char rowChar;
    int col;
    std::cout << "Enter row (A-J) to update: ";
    std::cin >> rowChar;
    std::cout << "Enter column (1-12) to update: ";
    std::cin >> col;
    int row = toupper(rowChar) - 'A';
    col--;
    if (v.slots[row][col] == NULL) {
        std::cout << "Slot empty!\n";
        return;
    }
    std::cout << "Current: " << v.slots[row][col]->data.name
        << " Rs." << v.slots[row][col]->data.price << "\n";
    std::cin.ignore();
    std::cout << "New name: ";
    getline(std::cin, v.slots[row][col]->data.name);
    std::cout << "New price: ";
    std::cin >> v.slots[row][col]->data.price;
    std::cout << "Updated slot " << rowChar << (col + 1) << "\n";
    utf(v, row);
}
void removeItem(vending& v) {
    char rowchar;
    int col;
    std::cout << "Enter row (A-J) to remove item: ";
    std::cin >> rowchar;
    std::cout << "Enter column (1-12) to remove item: ";
    std::cin >> col;
    int row = toupper(rowchar) - 'A';
    int column = col - 1;
    if (v.slots[row][column] == NULL) {
        std::cout << "Slot already empty!\n";
        return;
    }
    node* temp = pop(v.slots[row][column]);
    Product p = temp->data;
    delete temp;
    std::cout << "Removed " << p.name << " from " << rowchar << col << "\n";
    utf(v, row);
}
bool verifyadmin() {
    std::cout << "\nEnter passkey: ";
    std::string s;
    std::cin >> s;
    if (s == "Vendee") {
        return true;
    }
    return false;
}
bool verifyStockManager() {
    std::cout << "Enter Stock Manager passkey: ";
    std::string key;
    std::cin >> key;
    return key == "Stockee";
}
void buyProduct(vending& v, int& balance, bool check[], int nNotes[]) {
    char rowChar;
    int col;
    while (true) {
        std::cout << "Enter row (A-J) or 0 to stop buying: ";
        std::cin >> rowChar;
        if (rowChar == '0') break;
        std::cout << "Enter column (1-12): ";
        std::cin >> col;
        int row = toupper(rowChar) - 'A';
        int column = col - 1;
        if (row < 0 || row >= 10 || column < 0 || column >= 12) {
            std::cout << "Invalid row or column!\n";
            continue;
        }
        if (v.slots[row][column] == NULL) {
            std::cout << "Slot empty!\n";
            continue;
        }
        Product p = peek(v.slots[row][column]);
        if (p.price > balance) {
            std::cout << "Insufficient balance!\n";
            continue;
        }
        node* temp = pop(v.slots[row][column]);
        delete temp;
        balance -= p.price;
        std::cout << "Bought " << p.name << " for Rs." << p.price
            << ". Remaining balance: Rs." << balance << "\n";
        check[row] = true;
    }
}

void manageNotes() {
    int choice;
    int denom, count;
    bool valid;
    do {
        std::cout << "\nNote Management Menu:\n"
            << "1. View notes\n"
            << "2. Insert notes\n"
            << "3. Remove notes\n"
            << "4. Back\n"
            << "Enter your option: ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            std::cout << "\nCurrent notes in machine:\n";
            for (int i = 0; i < 9; i++) {
                std::cout << notes[i] << " Rs.: " << machineNotes[i] << "\n";
            }
            break;
        case 2:
            std::cout << "Enter denomination (500,200,100,50,20,10,5,2,1): ";
            std::cin >> denom;
            valid = false;
            for (int i = 0; i < 9; i++) {
                if (notes[i] == denom) {
                    std::cout << "Enter count to insert: ";
                    std::cin >> count;
                    machineNotes[i] += count;
                    std::cout << "Inserted " << count << " x " << denom << " Rs. notes.\n";
                    valid = true;
                    break;
                }
            }
            if (!valid) std::cout << "Invalid denomination!\n";
            saveChangeToFile();  // Save after insert
            break;
        case 3:  // Remove notes
            std::cout << "Enter denomination (500,200,100,50,20,10,5,2,1): ";
            std::cin >> denom;
            valid = false;
            for (int i = 0; i < 9; i++) {
                if (notes[i] == denom) {
                    std::cout << "Enter count to remove (current: " << machineNotes[i] << "): ";
                    std::cin >> count;
                    if (count > machineNotes[i]) {
                        std::cout << "Not enough notes to remove!\n";
                    }
                    else {
                        machineNotes[i] -= count;
                        std::cout << "Removed " << count << " x " << denom << " Rs. notes.\n";
                    }
                    valid = true;
                    break;
                }
            }
            if (!valid) std::cout << "Invalid denomination!\n";
            saveChangeToFile();
            break;
        case 4:
            return;
        default:
            std::cout << "Invalid option.\n";
        }
    } while (choice != 4);
}
void noteadd(int value, int nNotes[]) {
    for (int i = 0; i < 9; i++) {
        if (notes[i] == value) {
            nNotes[i]++;
            break;
        }
    }
}
void returnChange(int& balance, int sessionNotes[]) {
    if (balance == 0) {
        std::cout << "No change to return.\n";
        return;
    }
    std::cout << "Returning change: ";
    for (int i = 0; i < 9; i++) {
        while (balance >= notes[i] && sessionNotes[i] > 0) {
            balance -= notes[i];
            sessionNotes[i]--;
            std::cout << notes[i] << " ";
        }
    }
    std::cout << "\n";
    if (balance > 0) {
        std::cout << "Could not return " << balance << " Rs. in change. Please contact admin.\n";
    }
}
int enterbalance(int nNotes[]) {
    int notesArr[11] = { 1,2,5,10,20,50,100,200,500,1000,5000 };
    std::cout << "What amount do you want to enter\n";
    for (int i = 0; i < 11; i++) {
        std::cout << i + 1 << ". Rs." << notesArr[i] << std::endl;
    }
    int a;
    std::cout << "Enter the choice (1-11): ";
    std::cin >> a;
    while (a < 1 || a > 11) {
        std::cout << "Please enter a number between 1-11: ";
        std::cin >> a;
    }
    noteadd(notesArr[a - 1], nNotes);  // <-- add entered note to session
    return notesArr[a - 1];
}
void refillEntireMachine(vending& v) {
    std::string name;
    int price, col;
    char rowChar;
    std::fstream fin("defp.txt", std::ios::in);
    if (!fin.is_open()) {
        std::cout << "Cannot open default_products.txt\n";
        return;
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 12; j++) {
            while (v.slots[i][j] != NULL) {
                node* temp = pop(v.slots[i][j]);
                delete temp;
            }
        }
    }
    while (fin >> rowChar >> col >> std::quoted(name) >> price) {
        int row = toupper(rowChar) - 'A';
        int column = col - 1;
        push(v.slots[row][column], Product{ name, price });
    }
    fin.close();
    for (int i = 0; i < 10; i++) {
        utf(v, i);
    }
    std::cout << "Machine successfully refilled from master file!\n";
}
void finalizeCustomerSession(int balance, int sessionNotes[]) {
    returnChange(balance, sessionNotes);
    for (int i = 0; i < 9; i++) {
        machineNotes[i] = sessionNotes[i];
    }
    saveChangeToFile();
}

void runCustomerMode(vending& v) {
    int nNotes[9];
    for (int i = 0; i < 9; i++) { 
        nNotes[i] = machineNotes[i]; 
    }
    bool check[10] = { false };
    int balance = enterbalance(nNotes);
    int choice, a;
    do {
        customermenu();
        std::cin >> choice;
        switch (choice) {
        case 1:
            displaymachinelayout(v);
            break;
        case 2:
            buyProduct(v, balance, check, nNotes);
            break;
        case 3:
            a = enterbalance(nNotes);
            balance += a;
            break;
        case 4:
            for (int i = 0; i < 10; i++) {
                if (check[i] == true) {
                    utf(v, i);
                }
            }
            std::cout << "\nExiting program...\n";
            finalizeCustomerSession(balance, nNotes);
            exit(0);
        case 5:
            for (int i = 0; i < 10; i++) {
                utf(v, i);
            }
            finalizeCustomerSession(balance, nNotes);
            return;
        default:
            std::cout << "Invalid option.\n";
        }
    } while (true);
}
void runAdminMode(vending& v) {
    if (!verifyadmin()) {
        std::cout << "Incorrect passkey!\n";
        return;
    }
    int choice;
    do {
        Adminmenu();
        std::cin >> choice;
        switch (choice) {
        case 1:
            refillVendingMachine(v);
            break;
        case 2:
            updateProduct(v);
            break;
        case 3:
            removeItem(v);
            break;
        case 4:
            displaymachinelayout(v);
            break;
        case 5:
            manageNotes();
            break;
        case 6:
            for (int i = 0; i < 10; i++) {
                utf(v, i);
            }
            std::cout << "Exiting program...\n";
            exit(0);
        case 7:
            return;
        default:
            std::cout << "Invalid option.\n";
        }
    } while (choice != 6);
}
void runStockManager(vending& v) {
    if (!verifyStockManager()) {
        std::cout << "Incorrect passkey!\n";
        return;
    }
    int c;
    do {
        StockManagermenu();
        std::cin >> c;
        switch (c) {
        case 1:
            refillVendingMachine(v);
            break;
        case 2:
            updateProduct(v);
            break;
        case 3:
            removeItem(v);
            break;
        case 4:
            refillEntireMachine(v);
            break;
        case 5:
            displaymachinelayout(v);
            break;
        case 6:
            return;
        default:
            std::cout << "Please enter a valid option";;
            break;
        }
    } while (true);
}
void runMainMenu(vending& v) {
    int choice;
    while (true) {
        mainmenu();
        std::cin >> choice;
        switch (choice) {
        case 1:
            runCustomerMode(v);
            break;
        case 2:
            runStockManager(v);
            break;
        case 3:
            runAdminMode(v);
            break;
        case 4:
            std::cout << "Exiting program...\n";
            exit(0);
        default:
            std::cout << "Invalid option.\n";
        }
    }
}

int main() {
    vending a;
    loadChangeFromFile();
    placement(a);
    runMainMenu(a);
    return 0;
}