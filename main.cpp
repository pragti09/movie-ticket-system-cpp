#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;
bool loginuser(string & username, string & role);
void registerUser();
void adminpanel(string username);
void userpanel(string username);
void viewMovies();
void bookTicket(int userId, const string& username);
void viewMyBookings(int userId);
void cancelTicket(int userId);
void printTicket(int userId);
void userpanel(int userId, const string& username) {
    int choice;

    do {
        cout<<"\n===== User Panel (" << username << ") =====" <<endl;
        cout << "2. Book Ticket" << endl;
        cout << "3. View My Bookings" <<endl;
        cout << "4. Cancel Ticket" << endl;
        cout << "5. Print Ticket" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter your choice: ";
        if(!(cin>>choice)) {
            cout<<"Invalid input. Please enter a number."<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
            continue;     
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(choice) {
            case 1:
                viewMovies();
                break;
            case 2:
                bookTicket(userId, username);
                break;
            case 3:
                viewMyBookings(userId);
                break;
            case 4:
                cancelTicket(userId);
                break;
            case 5:
                printTicket(userId);
                break;
            case 6:
                cout<<"\nLogging out of User Panel. Returning to Main Menu."<<endl;
                break;
            default:
                cout<<"Invalid choice. Please try again (1-6)."<<endl;
        
        }
    }
    while (choice != 6);
}
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
