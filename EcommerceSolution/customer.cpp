#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include"Customer.h"

using namespace std;

//defaultconstructore - customer
Customer::Customer() {}

//parametrized constructor - customer
Customer::Customer(string user) {
    username = user;
}
//getvalue - helping function for take values from the file
string Customer::getvalue(char* filename, string user) {

    int pos;
    string key;
    string val_str;

    ifstream f1(filename);
    string line;
    while (getline(f1, line)) {
        pos = line.find(" ");
        key = line.substr(0, pos);
        val_str = line.substr(pos + 1);
        if (key == user) {

            f1.close();
            return val_str;
        }

    }
    return "-1";

}

//helping function for set the values in file
void Customer::setvalue(char* filename, char* tempfile, string proid, string updatevalue) {

    int pos;
    string key;
    string val_str;
    int value;

    //open file in read mode
    ifstream f1(filename);
    string line;

    //Temporary file with .tmp extension to copy and modify content
    //from original file
    ofstream fout(tempfile);

    while (getline(f1, line)) {
        pos = line.find(" ");//finding space

        key = line.substr(0, pos);//get username

        val_str = line.substr(pos + 1);//get value


        if (key == proid) {
            val_str = updatevalue;//add value to deposit
        }
        fout << key << ' ' << val_str << endl;//write the same in temporary file

    }

    //closed the file
    f1.close();
    fout.close();

    //remove original file
    remove(filename);

    //rename temporary file to original 
    rename(tempfile, filename);

}

//inherited 
//displaying menu for login, register and back
void Customer::loginMenu() {
    cout << "Welcome to The Ecommerce App " << endl;
    cout << "Enter your Choice" << endl;
    cout << "1. Login " << endl;
    cout << "2. Register" << endl;
    cout << "3. Back" << endl;

    int choice;
    cin >> choice;
    if (choice == 1) {
        //called to login
        login();
    }
    else if (choice == 2) {
        //called to  register
        registerCustomer();

    }
    else if (choice == 3) {
        system("cls");
        return;
    }
    else {
        cout << "Invalid Choice" << endl;
    }
}

//login(): used to login first before entering on website.
void Customer::login() {

    //intially set to false
    bool count = false;
    string userid, userpass, id, password;

    //to cleared the screen
    system("cls");

    //ask usrname and password
    cout << "Please Enter Customer userId and password:" << endl;
    cout << "Username: ";
    cin >> userid;
    cout << "\nPassword: ";
    cin >> userpass;

    //declare ifstream variable to read file
    ifstream inp;

    //open file
    inp.open("userPass.txt");

    while (inp >> id >> password) {
        //chech that username and password exist in the file or not
        if (userid == id && userpass == password)
            count = true;
    }
    //check- if the count is true
    if (count) {
        //Sucess Message
        cout << userid << " Your login is successfull" << endl;
        cout << "Thanks for loging in" << endl;

        //closing file
        inp.close();

        //Create an object of Customer with the username
        Customer c(userid);

        //Call Menu With the user
        c.customerMenu();

        return;
    }
    else {

        //show the error message if the username and password are not matched
        cout << "Login Error" << endl;
        cout << "Please check user id or password" << endl;
        return;
    }
}

//registerCustomer(): used for if the customer is new, then he/she need to register himself/herself first before procced to menu
void Customer::registerCustomer() {
    system("cls");
    cout << "Enter username of the Customer" << endl;
    string username;
    cin >> username;

    ifstream check;
    //check & read from file 
    check.open("userPass.txt");
    string user;

    while (check >> user) {

        //check if the user is already exist in the file
        if (username == user) {
            cout << "username already exist" << endl;
            return;
        }
    }
    check.close();
    cout << "Set Password: " << endl;
    string pass;
    cin >> pass;
    ofstream newEmp;

    //open the file in append mode
    newEmp.open("userPass.txt", ios::app);

    newEmp << username << ' ' << pass << endl;

    newEmp.close();

    system("cls");
    cout << "Your Account is created succesfully" << endl;

    //called the loginMenu() function after register successfully
    loginMenu();
}
