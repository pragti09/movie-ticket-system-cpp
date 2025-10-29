#include<iostream>
#include "Booking.h"
#include "Movie.h"
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
using namespace std;
//function to split string by a delimeter (|)
vector<string> split(const string& s, char delimeter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while(getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}
void bookTicket(int userID, string& username);
void bookTicket(int userID, string& username) {
    int movieIdToBook;
    int requestedSeats;
    vector<Movie> movies;
    bool movieFound = false;

    ifstream movieFileIn("movies.txt");
    if(!movieFileIn.is.open()) {
        cout<<"Error: Movie data not available."<<endl;
        return;
    }
    string line;
    cout<<"\n--- Available Movies ---"<<endl;
    cout<<"ID | Title | Time | Seats | Price"<<endl;
    cout<<"---|-------|------|-------|-------"<<endl;

    while(getline(movieFileIn, line)) {
        vector<string> parts = split(line,'|');
        if (parts.size()==5) {
            Movie m;
            m.id= stoi(parts[0]);
            m.title = parts[1];
            m.time = parts[2];
            m.availableSeats = stoi(parts[3]);
            m.price = stof(parts[4]);
            movies.push_back(m);
            cout<<m.id<<" | "<<m.title<<" | "<<m.time<<" | "<<m.availableSeats<<" | "<<m.price<<endl;
        }
    }

    movieFileIn.close();
    if(movies.empty()) {
        cout<<"No movies are currently scheduled."<<endl;
        return;
    }

    //VALIDATE INPUT
    cout<<"\n Enter Movie ID to book: ";
    cin>>movieIdToBook;
    cout<<"Enter number of seats: ";
    cin>>requestedSeats;

    auto it = find_if(movie.begin(), movies.end(), [movieIdToBook](const Movie& m){ return m.id==movieIdToBook; });
    of(it==movies.end()) {
        cout<<"Error: Movie ID not found."<<endl;
        return;
    }

    Movie& selectedMovie=*it;

    if(requestedSeats<=0 || requestedSeats > selectedMovie.availableSeats) {
        cout<<"Error: Invalid number of seats or not enough seats available (" <<selectedMovie.availableSeats<<" left)."<<endl;
        return;
    }
    
    //DEDUCTING SEATS
    selectedMovie.availableSeats -= requestedSeats;

    ofstream movieFileInOut("movies.txt");
    for(const auto& m : movies) {
        movieFileOut<<m.id<<"|"<<m.title<<"|"<<m.time<<"|"<<m.availableSeats<<"|"<<m.price<<endl;
    }
    movieFileOut.close();

    //calculate total cost
    float totalAmount = requestedSeats * selectedMovie.price;
    int newBookingId=101;

    ofstream bookingFileOut("bookings.txt", ios::app)
    bookingFileOut << newBookingId << "|" << userId << "|" << username << "|"<< selectedMovie.title << "|" << requestedSeats << "|"<< totalAmount << endl;

    bookingFileOut.close();
pull
    cout<<"\n----------------------------------------"<<endl;
    cout<<"TICKET BOOKED SUCCESSFULLY!"<<endl;
    cout<<"Bookind ID: "<<newBookingId<<endl;
    cout<<"Movie: "<<selectedMovie.title<<" @ "<<selectedMovie.time << endl;
    cout<<"Seats: "<<requestedSeats<<endl;
    cout<<"Total Cost: "<<totalAmount<<endl;
    cout<<"----------------------------------------"<<endl;
    
}

