#include<iostream>
using namespace std;
class movie{
    public:
    string title;
    string timings;
    int seats;
    int price;
};
class Deletemovie{
    movie movies[100];
    int c=5;
    public:
    void dummy(){
       movies[0] = {"interstella","10:00 AM",150,20};
       movies[1] = {"nutella","2:00 PM",200,40};
       movies[2] = {"shell","10:00 AM",159,50};
       movies[3] = {"beautiful","4:00 PM",300,10};
       movies[4] = {"nun","5:00PM",250,50};

    }
    void delMovie(string name){
        for(int i=0;i<c;i++){
            if(movies[i].title==name)
            {
                for(int j=i;j<c-1;j++){
                    movies[j].title=movies[j+1].title;
                }
                c--;
                cout<<"Deleted Successfully"<<endl;
                return;
            }
        }
        cout<<"Movie not found"<<name<<endl;
    }
    void show()
        {
            for(int i=0;i<c;i++){
                cout<<"Movies: "<< movies[i].title<<" "<<movies[i].timings<<" "<<movies[i].seats<<" "<<movies[i].price<<endl;
            }
        }



    };
int main(){
    Deletemovie movie;
    movie.dummy();
    string input;
    cout<<"Enter the movie you want to delete:"<<endl;
    getline(cin, input);
    movie.delMovie(input);
    movie.show();
    return 0;


}






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
    