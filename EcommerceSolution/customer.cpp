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
