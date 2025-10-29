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