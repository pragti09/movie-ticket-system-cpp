#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;
bool loginuser(string & username, string & role);
void registerUser();
void adminpanel();
void userpanel();
int main(){
    int choice;
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
    case 1:
    if(loginuser(username,role)){
        if(role=="Admin"){
        adminpanel(username);
     }
     else{
        cout<<"Access denied! you are not the admin"<<endl;
     }
    }
    else{
        cout<<"Login Failed! Try again later"<<endl;
    }
        break;
    case 2: 
    if(loginuser(username,role)){
        if(role=="User"){
            userpanel(username);
        }
        else{
            cout<<"Access denied! you are not the user"<<endl;
        }
    }
    else{
        cout<<"Login Failed! Try again later"<<endl;
    }
    break;
    case 3: 
    registerUser();
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
