#include<iostream>
#include<string>
using namespace std;
struct Ticket{
    string movieName;
    string userName;
    int seatNumber;
    bool isBooked;
};

Ticket tickets[20];
int ticketCount=0;

void cancelTicket(){
    if(ticketCount==0){
        cout<<"\nNo tickets booked yet. \n";
        return;
    }

    string name;
    int seat;
    cin.ignore();
    cout<<"\nEnter your name: ";
    getline(cin,name);
    cout<<"Enter your seat number: ";
    cin>>seat;
    bool found=false;
    for(int i=0;i<ticketCount;i++){
        if(tickets[i].userName==name && tickets[i].seatNumber==seat && tickets[i].isBooked){
            tickets[i].isBooked=false;
            cout<<"\nTicket cancelled successfully!\n";
            found=true;
            break;
        }
    }   
    if(!found){
        cout<<"\nNo matching ticket.\n";
    }
}

//print ticket


#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

class booking{
    public:
    static void printTicket(const string & username){
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

};
