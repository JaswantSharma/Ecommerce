#include <iostream>
#include "customer.h"
#include"admin.h"
#include<string>




using namespace std;


int main() {
	do {
		cout << "################################################################" << endl;
		cout << "########################   Welcome to the Ecommerce ############" << endl;
		cout << "################################################################" << endl;
		cout << "\n\n";
		cout << "Select Menu" << endl;
		cout << "1. Admin " << endl;
		cout << "2. Customer " << endl;
		cout << "3. Exit" << endl;
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			Admin a;
			a.login();
		}
		else if (choice == 2) {

			Customer c;
			c.loginMenu();

		}
		else if (choice == 3) {
			exit(0);
		}
		else {
			cout << "Enter a valid choice" << endl << endl;
		}
	} while (1);


}
