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

//customerMenu():To show the cutomer menu
void Customer::customerMenu() {

    cout << "Welcome " << this->username << " to Customer Menu" << endl;
    do {
        cout << "Please Enter your choice" << endl;
        cout << "\n1.Display Items. \n2.View Cart \n3.Place Order \n4.Exit\n" << endl;

        //ask to the customer 
        //that please select the menu following option which he/she wants
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:displayItems();
            break;
        case 2:viewcart();
            break;
        case 3:placeorder();
            break;
        case 4:return;
            break;
        default:
            cout << "Enter valid choice " << endl;
            break;
        }
    } while (1);
}

//displayItems(): displaying the products information which are avaialble in the store
void Customer::displayItems() {

    char filename[30] = "proName.txt";//proName - product name

    char filename2[30] = "proPrice.txt";//proPrice - Product price

    char filename3[30] = "proQuant.txt";//proQuant- product quantity

    //creating object for ifstream
    ifstream display;

    //open the file or read from file
    display.open(filename);
    cout << "\n\n";
    cout << endl << "----------------------------------------------------------------------" << endl;
    cout << left << setw(20) << "Product Id";
    cout << left << setw(30) << "Product Name";
    cout << left << setw(40) << "Price";
    cout << endl << "----------------------------------------------------------------------" << endl;
    cout << endl;
    string proId, proName;
    while (display >> proId >> proName) {
        string price = getvalue(filename2, proId);

        cout << left << setw(20) << proId;
        cout << left << setw(30) << proName;
        cout << left << setw(40) << price;
        cout << endl;

    }



    display.close();

    cout << "\n\n Enter product Id of the Product you want to Add to Cart" << endl;

    string productID;
    cin >> productID;

    ifstream check;
    string key;
    //check & read from product name file
    check.open("proName.txt");
    bool flag = false;

    while (check >> key) {
        if (productID == key) {
            flag = true;
        }
    }
    check.close();


    if (!flag) {
        cout << "Invalid product ID" << endl;
        return;
    }
    else {
        cout << "Enter the quantity of the product" << endl;
        int quant;
        cin >> quant;
        char filename[30] = "proQuant.txt";

        string proCount = getvalue(filename, productID);

        //here the stoi() function is used to  converts a string to an integer value.
        int proCountInt = stoi(proCount);

        //check the product count int is graeter then to quantity or not
        if (proCountInt >= quant) {
            //call to addcart function
            addtocart(productID, quant);
        }
        else {
            cout << "Not enough Pieces of this product " << endl;
            return;
        }

    }









}

//addtocart:-cutomer can add the product which he\she want to buy
void Customer::addtocart(string proId, int quant) {


    int pos;
    int pos2;
    string key;
    string proIdinFile;
    string count;
    string val_str;
    int value;


    bool flag = true;

    //read from file
    ifstream check;
    check.open("cart.txt");
    string line;

    //write from file
    ofstream fout("cart.tmp");

    while (getline(check, line)) {
        pos = line.find(" ");//finding space

        key = line.substr(0, pos);//get username

        val_str = line.substr(pos + 1);//get value

        pos2 = val_str.find(" ");

        proIdinFile = val_str.substr(0, pos2);

        count = val_str.substr(pos2 + 1);


        if (key == this->username && proIdinFile == proId) {
            int intofCount = stoi(count);
            quant += intofCount;
            string stringofQuant = to_string(quant);
            count = stringofQuant;
            flag = false;
        }
        fout << key << ' ' << proIdinFile << ' ' << count << endl;

    }

    if (flag) {
        fout << this->username << ' ' << proId << ' ' << quant << endl;
    }

    check.close();
    fout.close();

    //removing original cart file
    remove("cart.txt");

    //copying the updated date in temporary file and renamed it  to cart.tmp
    rename("cart.tmp", "cart.txt");

    cout << "Product added to cart successfully" << endl;
}



//removefromcart- it is used to remove the product from cart ,
//if the customer not intrested for buy a product.
void Customer::removefromcart(string proId, int quant) {

    int pos;
    int pos2;
    string key;
    string proIdinFile;
    string count;
    string val_str;
    int value;


    bool flag = true;
    //creating object for ifstream
    ifstream check;
    check.open("cart.txt");
    string line;

    ofstream fout("cart.tmp");


    while (getline(check, line)) {
        pos = line.find(" ");//finding space

        key = line.substr(0, pos);//get username

        val_str = line.substr(pos + 1);//get value

        pos2 = val_str.find(" ");

        proIdinFile = val_str.substr(0, pos2);

        count = val_str.substr(pos2 + 1);

        if (key == this->username && proIdinFile == proId) {

            //the stoi() function converts a string to an integer value
            int intofCount = stoi(count);
            intofCount -= quant;

            string stringofQuant = to_string(intofCount);
            count = stringofQuant;

        }

        if (count != "0") {

            fout << key << ' ' << proIdinFile << ' ' << count << endl;
        }
    }

    check.close();
    fout.close();

    //deleted the original file or old file
    remove("cart.txt");

    //rename old file to temporary file
    rename("cart.tmp", "cart.txt");

    cout << "Product remvoed from cart successfully" << endl;
}

//used to give the confirmation to the user that your order is placed 
void Customer::placeorder() {

    int pos;
    int pos2;
    string key;
    string proIdinFile;
    string count;
    string val_str;
    int value;


    bool flag = true;

    ifstream check;

    //read from file
    check.open("cart.txt");
    string line;

    //write to file
    ofstream fout("cart.tmp");

    //proQuant - product quantity 
    char filename[30] = "proQuant.txt";
    char tempfile[30] = "proQuant.tmp";

    while (getline(check, line)) {
        pos = line.find(" ");//finding space

        key = line.substr(0, pos);//get username

        val_str = line.substr(pos + 1);//get value

        pos2 = val_str.find(" ");

        proIdinFile = val_str.substr(0, pos2);

        count = val_str.substr(pos2 + 1);


        if (this->username == key) {
            string proQuant = getvalue(filename, proIdinFile);
            int proQuantint = stoi(proQuant);
            int countInt = stoi(count);
            proQuantint -= countInt;
            proQuant = to_string(proQuantint);
            setvalue(filename, tempfile, proIdinFile, proQuant);
        }
        else {
            fout << key << ' ' << proIdinFile << ' ' << count << endl;
        }

    }



    check.close();
    fout.close();

    //remove the original cart file before deleting the product 
    remove("cart.txt");

    //rename old file to updated file(temporary file- cart.tmp)
    rename("cart.tmp", "cart.txt");

    cout << this->username << "Your Order was placed successfully" << endl;




}


//view cart:- displaying the product list or information which have brought by the customer
void Customer::viewcart() {

    int pos;
    int pos2;
    string key;
    string proIdinFile;
    string count;
    string val_str;
    int value;


    bool flag = true;

    ifstream check;
    check.open("cart.txt");
    string line;

    //initially total price is assigned to zero
    int totalprice = 0;

    //initially discount assigned to zero
    int discountPrice = 0;

    //show the particular -user view cart(which are avialable in the username password file)
    cout << this->username << " your cart has the following items" << endl;
    cout << "\n\n";
    cout << endl << "----------------------------------------------------------------------" << endl;

    //setw(length): used to set the filed
    cout << left << setw(20) << "Product Id";
    cout << left << setw(30) << "Product Name";
    cout << left << setw(40) << "Quantity";
    cout << endl << "----------------------------------------------------------------------" << endl;
    cout << endl;
    while (getline(check, line)) {
        pos = line.find(" ");//finding space

        key = line.substr(0, pos);//get username

        val_str = line.substr(pos + 1);//get value

        pos2 = val_str.find(" ");

        proIdinFile = val_str.substr(0, pos2);

        count = val_str.substr(pos2 + 1);

        //take file which are already exist in our system
        char filename[30] = "proPrice.txt";
        char filename2[30] = "proName.txt";
        char filename3[30] = "proDiscount.txt";

        if (key == this->username) {

            string price = getvalue(filename, proIdinFile);
            string proName = getvalue(filename2, proIdinFile);
            string discount = getvalue(filename3, proIdinFile);
            int intforCount = stoi(count);

            cout << left << setw(20) << proIdinFile;
            cout << left << setw(30) << proName;
            cout << left << setw(40) << count;
            cout << endl;

            //the stoi() function converts a string to an integer value
            int priceInt = stoi(price);

            if (discount != "-1") {
                int intDiscount = stoi(discount);

            }
            totalprice = totalprice + intforCount * priceInt;
        }

    }



    //displaying the total cost of the products
    cout << "Total Cost is " << totalprice << endl;
    check.close();

    //the customer can remove only the product only when total price will be greater then zero
    if (totalprice > 0) {
        cout << "\n\nDo you want to remove anything" << endl;
        cout << "\n\nPress y for YES and N for NO. " << endl;
        char choice;
        cin >> choice;

        //y  - yes and n- no
        if (choice == 'y' || choice == 'Y') {
            cout << "Enter product id of the product you want to remove" << endl;
            string productid;
            cin >> productid;

            //ask to customer that how much quantity the customer want to remove from cart
            cout << "Enter Quantity of the product you want to remove" << endl;
            int quant;
            cin >> quant;

            //called removefromcart function
            removefromcart(productid, quant);
        }
    }


}