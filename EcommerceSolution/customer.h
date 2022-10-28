#pragma once
#include<iostream>
using namespace std;

class Customer {
private:
	string username;
public:

	Customer(); // Defualt constructor
	Customer(string username);// Parameterized Constructor

	//these are the helping functions for get the values from the file
	string getvalue(char* filename, string user);
	void setvalue(char* filename, char* tempfile, string proid, string updatevalue);

	//this function will display the login menu for the customer
	void loginMenu();

	//this function is used to login
	void login();

	//this function used to register 
	void registerCustomer();

	//this function will display the customer menu
	void customerMenu();

	//this function will display all the products present in the record
	void displayItems();

	//this function is used to add the product to the cart
	void addtocart(string proID, int quant);

	//this function is used to remove the product from the cart
	void removefromcart(string proId, int quant);

	//this function is used to view the cart
	void viewcart();

	//this function is used to place the order
	void placeorder();

};