#include<iostream>
#include"booking.h"
#include<fstream>
#include<sstream>
#include<string>
#include<limits>
#include<vector>
#include"user.h"
#include"utility.h"
using namespace std;

void User::registerUser() {
    string newUsername, newPassword;
    cout<<"\n--- New User Registration ---"<<endl;
    cin.ignore();
    cout<<"Enter Username: ";
    getline(cin, newUsername);
    cout<<"Set Password: ";
    getline(cin, newPassword);

    int newId = getNextId("user.txt");

    ofstream file("user.txt", ios::app);

    if(!file.is_open()) {
        cout<<"Error: Could not open file for registering."<<endl;
        return;
    }

    file<<newId<<"|"<<newUsername<<"|"<<newPassword<<"|User"<<endl;
    file.close();

    cout<<"\nRegisteration successful! Your UserId is "<<newId<<endl;

}

bool login(string & username, string & role,int &userId){
    string password, line;
    cin.ignore();

    cout << "Enter Username: ";
    getline(cin, username);
    cout << "Enter Password: ";
    getline(cin, password);
    

    ifstream file("user.txt");
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, uname, pass, r;
        getline(ss, idStr, '|');
        getline(ss, uname, '|');
        getline(ss, pass, '|');
        getline(ss, r, '|');

        if (uname == username && pass == password) {
            file.close();
            userId = stoi(idStr);
            role = r;
            return true;
        }
    }
    file.close();
    return false;
}




