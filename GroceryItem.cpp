#include "GroceryItem.h"

//constructor for initializing the name of the item (default quantity of 1)
GroceryItem::GroceryItem(const std::string& name) : name(name), quantity(1) {}

//constructor for initializing the name and the specific quantity of the item
GroceryItem::GroceryItem(const std::string& name, int quantity) : name(name), quantity(quantity) {}

//Accessor for the name of the item
std::string GroceryItem::getName() const {
	return name;
}

//Accessor for the quantity of the item 
int GroceryItem::getQuantity() const {
	return quantity;
}

//Funcstion to increase the quantity of an item
void GroceryItem::addItem() {
	this->quantity++;
}

//Function to decrease the quantity of an item
void GroceryItem::removeItem() {
	if (this->quantity > 0) {
		this->quantity--;
	}
}

//Overloading the less than operator for comparison based on the name of the item (instead of map for object oriented approach)
bool GroceryItem::operator<(const GroceryItem& other) const
{
	return name.compare(other.getName()) < 0;
}