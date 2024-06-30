#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "GroceryItem.h"

using namespace std;

//function to read the inventory from Inventory.txt and return a set
set<GroceryItem> readInventory(const string& filename) {
	set<GroceryItem> items;
	ifstream file(filename);
	string itemName;

	if (!file.is_open()) {
		throw runtime_error("Could not open file: " + filename);
	}

	while (file >> itemName) {
		auto existingItem = items.find(GroceryItem(itemName));

		if (existingItem != items.end()) {
			GroceryItem updatedItem = *existingItem;
			items.erase(existingItem);
			updatedItem.addItem();
			items.insert(updatedItem);
		}
		else {
			items.insert(GroceryItem(itemName));
		}
	}

	file.close();
	return items;
}

//Function to back up data to Frequency.dat
void backupData(const set<GroceryItem>& items, const string& filename) {
	ofstream file(filename);
	if (!file.is_open()) {
		throw runtime_error("Could not open file: " + filename);
	}

	for (const auto& item : items) {
		file << item.getName() << " " << item.getQuantity() << endl;
	}
	file.close();
}

//Function to display frequency of the item
void displayFrequencies(const set<GroceryItem>& items) {
	for (const auto& item : items) {
		cout << item.getName() << " " << item.getQuantity() << endl;
	}
}

//Function for displaying the histogram of the item frequency
void displayHistogram(const set<GroceryItem>& items) {
	for (const auto& item : items) {
		cout << item.getName() << " ";
		for (int i = 0; i < item.getQuantity(); ++i) {
			cout << "*";
		}
		cout << endl;
	}
}

//Function for searching for an item
void searchItem(const set<GroceryItem>& items, const string& itemName) {
	auto it = items.find(GroceryItem(itemName));
	if (it != items.end()) {
		cout << itemName << " frequency: " << it->getQuantity() << endl;
	}
	else {
		cout << itemName << " not found." << endl;
	}
}

//Main Function
int main() {
	set<GroceryItem> items; 
	string filename = "Inventory.txt"; 
	string backupFilename = "Frequency.dat";
	bool exit = false;

	try {
		items = readInventory(filename);
		backupData(items, backupFilename);
	}
	catch (const runtime_error& e) {
		cerr << e.what() << endl; 
		return 1;
	}

	while (!exit) {
		cout << "Menu Options: " << endl; 
		cout << "1. Search for an item" << endl; 
		cout << "2. Display frequency of all items" << endl; 
		cout << "3. Display histogram of item frequencies" << endl; 
		cout << "4. Exit" << endl; 
		cout << "Enter your choice: ";

		int choice; 
		cin >> choice; 

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a number between 1 and 4." << endl; 
			continue;
		}

		switch (choice) {
			case 1: {
				cout << "Enter item name: ";
				string itemName;
				cin >> itemName;
				searchItem(items, itemName);
				break;
			}
			case 2:
				displayFrequencies(items);
				break;
			case 3: 
				displayHistogram(items);
				break;
			case 4:
				exit = true;
				break; 
			default:
				cout << "Invalid choice. Please enter a number between 1 and 4." << endl; 

		}
	}
	return 0; 
}