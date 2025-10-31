//View Available Movies 

#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
void viewMovies(){
    ifstream file("movies.txt");
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



// view movie booking details

#include<iostream>
#include<string>
using namespace std;
struct movie{
    int bookingId;
    string customerName;
    string movieName;
    string showTime;
    int seatNumber;
    float ticketPrice;
};
int main(){
    movie booking1;
    cout<<"enter booking Id:";
    cin>>booking1.bookingId;
    cout<<"enter customer name:";
    cin>>booking1.customerName;
    cout<<"enter movie name:";
    cin>>booking1.movieName;
    cout<<"enter show time:";
    cin>>booking1.showTime;
    cout<<"enter seat number:";
    cin>>booking1.seatNumber;
    cout<<"enter ticket price:";
    cin>>booking1.ticketPrice;
    
    cout<<"\nMovie booking details\n";
    cout<<"booking Id:"<<booking1.bookingId<<endl;
    cout<<"customer name:"<<booking1.customerName<<endl;
    cout<<"movie name:"<<booking1.movieName<<endl;
    cout<<"show time:"<<booking1.showTime<<endl;
    cout<<"seat number:"<<booking1.seatNumber<<endl;
    cout<<"ticket price:"<<booking1.ticketPrice<<endl;


    return 0;
}


//logout code

#include<iostream>
#include<string>
using namespace std;
int main(){
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
    return 0;
}