// admin panel code 

#include<string>
#include<iostream>
using namespace std;
void adminpanel(string username){
    int choice;
    do{
        cout<<"----Admin Panel-----"<<endl;
        cout<<"Welcome"<<username<<"Admin"<<endl;
        cout<<"1. Add Movie"<<endl;
        cout<<"2. Update Movie"<<endl;
        cout<<"3. Delete Movie"<<endl;
        cout<<"4. View Movie"<<endl;
        cout<<"5. View All Bookings"<<endl;
        cout<<"6. Logout"<<endl;
        cout<<"Enter your Choice"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
            addmovie();
            break;
            case 2:
            updatemovie();
            break;
            case 3:
            Deletemovie();
            break;
            case 4:
            viewmovie();
            break;
            case 5:
            viewallbookings();
            break;
            case 6:
            cout<<"logging out"<<endl;
            break;
            default:
            cout<<"Invalid choice"<<endl;
            break;
        } 
    } while(choice!=6);
}

// Delete movie code 


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
    return 
}



//<Add movies>

#include<iostream>
#include<string>
using namespace std;

struct Movie{
       string title;
       string genre;
       string timings;
       int duration;
       float price;
};

Movie movies[10];  //global array to store movies
int movieCount=0;
void addMovie(){
    if(movieCount<10){
        cin.ignore();
        cout<<"\nEnter movie title: ";
    getline(cin,movies[movieCount].title);
    cout<<"Enter genre: ";
    getline(cin,movies[movieCount].genre);
    cout<<"Enter Timings: ";
    cin>>movies[movieCount].timings;
    cout<<"Enter duration(in minutes): ";
    cin>>movies[movieCount].duration;
    cout<<"Enter ticket price: ";
    cin>>movies[movieCount].price;
    
    movieCount++;
    cout<<"\nMovie added successfully!\n";
}
else{
    cout<<"Movie list is full!\n";
}
}

void showMovies(){
    if(movieCount==0){
        cout<<"\nNo movies available.\n";
        return;
    }
    cout<<"\nList of Movies :\n";
    for(int i=0;i<movieCount;i++){
        cout<<"Movie "<<i+1<<endl;
        cout<<"Title: "<<movies[i].title<<endl;
        cout<<"Timings: "<<movies[i].timings<<endl;
        cout<<"Genre: "<<movies[i].genre<<endl;
        cout<<"Duration: "<<movies[i].duration<<" minutes"<<endl;
        cout<<"Price: Rs."<<movies[i].price<<endl;
    }
}



// update movie


#include<iostream>
#include<string>
using namespace std;
class movie {
public:
      int id;
      string name;
      string time;
      float price;
       
      void display(){
        cout<<"ID:" <<id<<"| NAME:" <<name<<"| TIME:" <<time<<"| PRICE:" <<price<< endl;
      }
};

    void updatemovie (movie movies[] ,int size ){
      int searchID;
      cout<< "\n enter movieID to update:";
      cin >> searchID;
      if(!(cin>> searchID)){
        cout<< "invalid ID";
      }
    
    bool found=false;
    for (int i=0;i<size;i++){
      if(movies[i].id ==searchID){
        found=true;
        cout<< "\n new movie details";
        cout<<  " enter name:";
        cin>> movies[i].name;
        cout<< "enter time:";
        cin>> movies[i].time;
        cout<< "enter price:";
        cin>> movies[i].price;
        cout<<"\n movie updated";
        break;
        return;

      }
    }
  
  if(!found){
    cout<<"movie not found";
  }
}
int main(){
  movie movies[2]={
    {1,"avtar","4pm", 449.0},
    {2,"joker","8pm", 499.0}
  };
  updatemovie(movies,2);
  cout<<"\n updated movie;\n";
  for(int i=0;i<2;i++){
    movies[i].display();
  }
  return 0;

}



//View all bookings

#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

void viewAllBookings(){
    ifstream file("bookings.txt");
    if(!file){
        cout<<"Error: Could not open bookings.txt\n";
        return;
    }

string line;
cout<<"\n==== All Bookings =====\n";
cout<<"BookingID | UserID | Username | MovieTitle | Seats | Amount\n";
cout<<"--------------------------------------------------------------------------\n";


while(getline(file,line)){
    stringstream ss(line);
    string bookingId,userId,username,movieTitle,seats,amount;

    getline(ss,bookingId,'|');
    getline(ss,userId,'|');
    getline(ss,username,'|');
    getline(ss,movieTitle,'|');
    getline(ss,seats,'|');
    getline(ss,amount,'|');

    cout<<bookingId<<"|"<<userId<<"|"<<username<<"|"<<movieTitle<<"|"<<seats<<"|"<<"Rs."<<amount<<"\n";
}
file.close();
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