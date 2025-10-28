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