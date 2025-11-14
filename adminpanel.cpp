#include<string>
#include<iostream>
#include<vector>
#include "movie.h"
using namespace std;

void adminpanel(string username){
     vector<Movie> movies;
    int choice;
    do{
        cout<<"----Admin Panel-----"<<endl;
        cout<<"Welcome"<<"\t"<<username<<"\t"<<"Admin"<<endl;
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
           addMovie(movies);
            break;
            case 2:
            updatemovie();
            break;
            case 3:
            deleteMovie(movies, "movie.txt");
            break;
            case 4:
            viewMovies(movies);
            break;
            case 5:
            viewAllBookings();
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



