#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include "user.h"
#include "adminpanel.h"
#include "movie.h"
#include "booking.h"
#include"utility.h"
using namespace std;
bool login(string & username, string & role,int &userId){
    string password, line, idstr;
    cout<<"Enter your Id: "<<endl;
    cin>>idstr;
    cin.ignore();
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
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
            userId = stoi(idStr);
            role = r;
            return true;
        }
    }
    return false;
}
void adminpanel(string username);
void userpanel(int userId, const string& username);
int main(){
    User newUser;
    int choice;
    int userId;
    string username, role;
    while(true){
    cout<<"----MOVIE TICKET BOOKING SYSTEM----"<<endl;
    cout<<"1. Login As Admin"<<endl;
    cout<<"2. Login As User"<<endl;
    cout<<"3. Register As New User"<<endl;
    cout<<"4. Exit"<<endl;
    cout<<"Enter your choice"<<endl;
    cin>>choice;

    switch (choice)
    {
    case 1:  { // Admin login
        if (login(username,role, userId)) {
            if (role == "Admin") {
                adminpanel(username);
            } else {
                cout << "Access denied: You are not an admin.\n";
            }
        } else {
            cout << "Admin login failed.\n";
        }
        break;
    }

    case 2: { // User login
        if (login(username,role, userId)) {
            if (role == "User") {
                userpanel(userId, username);
            } else {
                cout << "Access denied: You are not a customer.\n";
            }
        } else {
            cout << "User login failed.\n";
        }
        break;
    }

    

    case 3: 
    newUser.registerUser();
    break;
    case 4:
    cout<<"Thank for using the system"<<endl;
    break;
    default:
    cout<<"Invalid Choice. Try again"<<endl;
        break;
    }
    return 0;
}
}

 