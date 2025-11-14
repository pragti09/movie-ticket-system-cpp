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
//Register As new user 
void User::registerUser() {
    string newUsername, newPassword;
    cout<<"\n--- New User Registration ---"<<endl;
    cin.ignore();
    cout<<"Enter Username: "<<endl;
    getline(cin, newUsername);
    cout<<"Enter newPassword"<<endl;
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




void viewMovies();
void bookTicket(int userId, const string& username);
void viewMyBookings();
void cancelTicket();
void printTicket(string username);
void logout();
void userpanel(int userId, const string& username){
    int choice;
    do {
        cout<<"\n===== User Panel (" << username << ") =====" <<endl;
        cout<< "1. View Available Movies " <<endl;
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
                viewMyBookings();
                break;
            case 4:
                cancelTicket();
                break;
            case 5:
                printTicket(username);
                break;
            case 6:
                cout<<"\nLogging out of User Panel. Returning to Main Menu."<<endl;
                logout();
                break;
            default:
                cout<<"Invalid choice. Please try again (1-6)."<<endl;
        
        }
    }
    while (choice != 6);
}

//View Available Movies 
void viewMovies(){
    ifstream file("movie.txt");
    if (!file. is_open()){
        cout<<"Unable to open the file!"<<endl;
        return;
    }
    string line;
    cout<<"--------------AVAILABLE MOVIES-----------------------"<<endl;
    cout<<"ID \t TITLE \t TIME \t SEATS \t PRICE \t"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    while(getline(file, line)){
        stringstream ss(line);
        string id, title, time, seats, price;
        getline(ss, id, '|');
        getline(ss, title, '|');
        getline(ss, time, '|');
        getline(ss, seats, '|');
        getline(ss, price, '|');
        cout<<id<<"\t"<<title<<"\t"<<time<<"\t"<<seats<<"\t"<<price<<endl;
    }
    file.close();

}

// Cancel Ticket

struct Ticket{
    string movieName;
    string userName;
    int seatNumber;
    bool isBooked;
};

Ticket tickets[20];
int ticketCount=0;
void cancelTicket() {
    ifstream fin("booking.txt");
    if (!fin) {
        cout << "\nError: booking.txt not found.\n";
        return;
    }

    vector<string> lines;
    string line;
    bool found = false;

    string name, movie;
    cin.ignore();
    cout << "\nEnter your name: ";
    getline(cin, name);
    cout << "Enter movie name: ";
    getline(cin, movie);

    // Read file line-by-line
    while (getline(fin, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string bookingId, userId, username, moviename, seats, amount;

        getline(ss, bookingId, '|');
        getline(ss, userId, '|');
        getline(ss, username, '|');
        getline(ss, moviename, '|');
        getline(ss, seats, '|');
        getline(ss, amount, '|');

        // Check match
        if (username == name && moviename == movie) {
            found = true;
            continue; // DO NOT add this line back -> DELETED
        }

        lines.push_back(line); // keep other bookings
    }
    fin.close();

    if (!found) {
        cout << "\nNo booking found for given name + movie.\n";
        return;
    }

    // Rewrite updated file
    ofstream fout("booking.txt");
    for (string &l : lines)
        fout << l << "\n";
    fout.close();

    cout << "\nTicket cancelled successfully!\n";
}
//print ticket
void printTicket(string username){
        ifstream file("booking.txt");
        string line;
        bool found = false;
        while(getline(file,line)){
            stringstream ss(line);
            string booking_id, user_id, uname, movie, seats, amount;
            getline(ss, booking_id, '|');
            getline(ss,user_id,'|' );
            getline(ss,uname,'|' );
            getline(ss,movie,'|' );
            getline(ss,seats,'|' );
            getline(ss,amount,'|');

            if(uname == username){
                found=true;
                cout<<"-----TICKET-----"<<endl;
                cout<<"---------------------"<<endl;
                cout<<"Booking Id:- "<<booking_id<<endl;
                cout<<"User Id:- "<<user_id<<endl;
                cout<<"Name:- "<<uname<<endl;
                cout<<"Movie:- "<<movie<<endl;
                cout<<"Seat Number:- "<<seats<<endl;
                cout<<"Amount Paid:- "<<amount<<endl;
            }
        }
        if(!found){
            cout<<"No tickets found!"<<endl;

        }
        file.close();
     }
//View My Bookings 
struct movie{
    int bookingId;
    string customerName;
    string movieName;
    string showTime;
    int seatNumber;
    float ticketPrice;
};
void viewMyBookings(){
    vector<movie> bookings;
    ifstream file("booking.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string part;
        movie m;

        getline(ss, part, '|'); m.bookingId = stoi(part);
        getline(ss, part, '|');
        getline(ss, part, '|'); m.customerName = part;
        getline(ss, part, '|'); m.movieName = part;
        getline(ss, part, '|'); m.seatNumber = stoi(part);
        getline(ss, part, '|'); m.ticketPrice = stof(part);
        bookings.push_back(m);
    }
    file.close();
    int choice;
    cout<<"view your booking details\n";
    cout<<"1. search by booking id\n";
    cout<<"2. search by customer name\n";
    cin>> choice;

    int searchId;
    string searchName;
    bool found =false;
    if(choice==1){
        cout<<"enter your booking id:";
        cin>>searchId;
    }
    else{
        cout<<"enter your name:";
        cin>>searchName;
    } 
    cout<< "\n===your booing details===\n";
    for (const movie& m: bookings){
        if((choice==1 && m.bookingId==searchId)||
         (choice==2 && m.customerName==searchName))
        {
            found=true;
            
            cout<<"booking Id:"<<m.bookingId<<endl;
            cout<<"Name:"<<m.customerName<<endl;
            cout<<"Movie:"<<m.movieName<<endl;
            cout<<"show time:"<<m.showTime<<endl;
            cout<<"seat number:"<<m.seatNumber<<endl;
            cout<<"Price:"<<m.ticketPrice<<endl;
        }
    }
    if(!found){
        cout<<" no booking found.\n";
    }
}



//logout code
void logout(){
    string users[2]={"user","admin"};
    bool loggedin[2]={true,true};
    int choice;
    cout<<"======logout page======"<<endl;
    cout<<"1. logout user"<<endl;
    cout<<"2. logout admin"<<endl;
    cout<<"enter your choice:";
    cin>>choice;
     
    if (choice==1) {
        loggedin[0]=false;
        cout<<users[0]<<"logged out successfully"<<endl;
    } 
    else if(choice==2){
        loggedin[1]=false;
        cout<<users[1]<<"logged out successfully"<<endl;
    }                               
    else{
        cout<<"invalid choice"<<endl;
    }
}
