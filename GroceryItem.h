#pragma once
#include <string>

class GroceryItem {
public:
	GroceryItem(const std::string& name);
	GroceryItem(const std::string& name, int quantity);

	std::string getName() const;
	int getQuantity() const;

	void addItem();
	void removeItem();

	bool operator<(const GroceryItem& other) const;

private:
	std::string name; 
	int quantity;
};