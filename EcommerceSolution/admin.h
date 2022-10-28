#pragma once
#include<iostream>
using namespace std;

class Admin
{

private:
    string AdminuserName = "Admin@123";
    string AdminPassword = "1234567";
public:
    //this function if for displaying the admin menu
    void Adminmenu();

    //this function is for the admin login
    void login();

    //these functions are the helping functions to get the values from file
    string getvalue(char* filename, string user);
    void setvalue(char* filename, char* tempfile, string user, string updatevalue);
    
    //this function is used for adding the product to the file
    void AddProduct();

    //this is the helping function for the removing the product
    void removepro(char* filename, char* tempfile, string proid);

    //this function is used to delete the product from the record
    void RemoveProduct();

    //this function is used to apply discount for the products
    void Discount();

    //this function is used to modify the products which are present in the file
    void modify();

};
