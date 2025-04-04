#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Inventory
{
    int itemID;
    char itemName[30]; // name is char[] (array) bcz. read() and write() don't work on string!
    float price;
    int quantity;

    static int no_of_items;

    void headerTXT(ofstream &file)
    {
        file << endl;
        file << left << setw(10) << "ID"
             << setw(30) << "Name"
             << setw(10) << "Price"
             << setw(10) << "Quantity" << endl;
        file << string(60, '-') << endl;
    }

    // modify in stock.txt (by reuploading):
    void copyToTXT()
    {

        ofstream fileTXT;
        fileTXT.open("stock.txt");

        fstream file;
        file.open("STOCK.DAT", ios::binary | ios::in);

        Inventory temp;

        /* adding header: */
        headerTXT(fileTXT);

        // adding data to txt file
        while (file.read((char *)&temp, sizeof(temp)))
        {
            fileTXT << left << setw(10) << temp.itemID
                    << setw(30) << temp.itemName
                    << setw(10) << temp.price
                    << setw(10) << temp.quantity << endl;
        }

        fileTXT.close();
        file.close();
    }

protected:
    void getData()
    {
        no_of_items++;

        cout << "\nEnter Item ID: ";
        cin >> itemID;

        bool duplicateItem = false;

        fstream file;
        file.open("STOCK.DAT", ios::binary | ios::in); // open in both "binary" and "in"

        Inventory temp; // temporary object for checking duplicate item!

        while (file.read((char *)&temp, sizeof(temp)))
        {
            if (temp.itemID == itemID)
            {
                duplicateItem = true;
                cout << "Same ID already exists";
                break;
            }
        }

        if (duplicateItem)
        {
            cout << "\n\nEnter details again\n";

            file.close(); // closing file before recursion or calling another function is necessary!
            getData();

            return;
        }

        cout << "Enter Item Name: ";
        cin.ignore();
        cin.getline(itemName, 30);
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Quantity: ";
        cin >> quantity;
    }

    void showData() const
    {
        cout << left << setw(10) << itemID
             << setw(30) << itemName
             << setw(10) << price
             << setw(10) << quantity << endl;
    }

    void modifyData()
    {
        cout << "Modify Item Name: ";
        cin.ignore();
        cin.getline(itemName, 30);
        cout << "Modify Price: ";
        cin >> price;
        cout << "Modify Quantity: ";
        cin >> quantity;
    }

public:
    void addItem();
    void displayStock();
    void modifyItem(int);
    void clearFile();
};

// Function to add a new item
void Inventory::addItem()
{

    // adding to stock.dat
    ofstream file("STOCK.DAT", ios::binary | ios::app);
    getData();
    file.write((char *)this, sizeof(*this));
    file.close();

    copyToTXT(); // this adds a header and copy latest data of .dat file to .txt file!

    cout << "Item added successfully.\n";
}

// Function to display all items
void Inventory::displayStock()
{
    ifstream file("STOCK.DAT", ios::binary);
    if (!file)
    {
        cout << "No records found!\n";
        return;
    }

    cout << left << setw(10) << "ID"
         << setw(30) << "Name"
         << setw(10) << "Price"
         << setw(10) << "Quantity" << endl;
    cout << string(60, '-') << endl;

    while (file.read((char *)this, sizeof(*this)))
    {
        showData();
    }
    file.close();
}

// Function to modify an item
void Inventory::modifyItem(int id)
{
    fstream file("STOCK.DAT", ios::binary | ios::in | ios::out);
    if (!file)
    {
        cout << "File not found!\n";
        return;
    }

    bool found = false;
    while (file.read((char *)this, sizeof(*this)))
    {
        if (itemID == id)
        {
            cout << "Current details:\n";
            showData();

            // modify in stock.dat:
            cout << "\nEnter new details:\n";
            modifyData();

            // int pos = -static_cast<int> (sizeof(*this));
            file.seekp(-static_cast<int>(sizeof(*this)) /*pos*/, ios::cur);
            file.write((char *)this, sizeof(*this));
            found = true;
            file.close();

            cout << "Item updated successfully.\n";
            break;
        }
    }

    // modify in .txt
    copyToTXT();

    if (!found)
    {
        cout << "Item not found!\n";
    }
}

void Inventory::clearFile()
{
    fstream file;

    // for earsing also it is necessary to open file in ios::out mode bcz. erasing is also a type of writing(i.e. output/ios::out).
    file.open("stock.txt", ios::out | ios::trunc);
    file.close();

    file.open("STOCK.DAT", ios::binary | ios::out | ios::trunc);
    file.close();

    no_of_items = 0;
}

int Inventory::no_of_items = 0;

// Main function
int main()
{
    Inventory inv;
    int choice, id;

    cout << "\n!!!Inventory Management!!!\n";
    do
    {
        cout << "\n1. Add Item\n";
        cout << "2. Display Stock\n";
        cout << "3. Modify Item\n";
        cout << "4. Clear Stock\n";
        cout << "5. Exit\n";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            inv.addItem();
            break;
        case 2:
            inv.displayStock();
            break;
        case 3:
            cout << "\nEnter Item ID to modify: ";
            cin >> id;
            inv.modifyItem(id);
            break;
        case 4:
            cout << "Clearing the Data...\n";
            inv.clearFile();
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    ofstream out;
    // // clears file data added to .dat file after closing the program!
    // out.open("STOCK.DAT", ios::trunc);
    // out.close();

    // separates data added to .txt file on different runs of program
    // out.open("stock.txt", ios::app);
    // out << string(14, '-') << 'X' << string(14, '-') << 'X' << string(14, '-') << 'X' << string(14, '-') << '-' << endl;
    // out.close();

    return 0;
}
