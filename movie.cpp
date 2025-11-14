#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include "movie.h"
#include <sstream>
using namespace std;
void Movie::display() const {
     cout<<"ID: "<<id;
        cout<<" | Name: "<<title;
        cout<<" | Time: "<<time;
        cout<<" |Seats: "<<availableSeats;
        cout<<" | Price: "<<price<<endl;
}
//Add Movie
void addMovie(vector<Movie>&movies){
    Movie m;
    cout<<" \nEnter Movie ID: ";
    cin>>m.id;
    cin.ignore(); //clears input buffer
    
    cout<<"Enter Movie Name: ";
    getline(cin, m.title);

    cout<<"Enter Movie Time: ";
    getline(cin, m.time);

    cout<<"Enter Number of seats of available : ";
    cin>>m.availableSeats;

    cout<<"Enter Ticket Price: ";
    cin>>m.price;
    
    movies.push_back(m);
    cout<<"\n Movie added successfully!\n";
     ofstream outFile("movie.txt", ios::app);
    if(outFile.is_open()){
        outFile<<m.id<<"|";
        outFile<<m.title<<"|";
        outFile<<m.time<<"|";
        outFile<<m.availableSeats<<"|";
        outFile<<m.price<<"|"<<endl;
     outFile.close();
     cout<<"\nMovie added successfully and saved to file!\n";
    }else{
        cout<<"\nError: Could not open movie.txt file!\n ";
    }

}                                           

//View Movies
void viewMovies(const vector<Movie>&movies){
    if(movies.empty()){
        cout<<"\nNo movies available.\n";
        return;
    }
    cout<<"\nList of Movies: \n";
    for(const Movie &m : movies){
        m.display();
    }
}
//Update Movie
void updatemovie() {
    vector<Movie> movies;

    ifstream fin("movie.txt");
    if (!fin.is_open()) {
        cout << "Error opening movie.txt" << endl;
        return;
    }

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string part;
        Movie m;

        getline(ss, part, '|'); m.id = stoi(part);
        getline(ss, part, '|'); m.title = part;
        getline(ss, part, '|'); m.time = part;
        getline(ss, part, '|'); m.availableSeats = stoi(part);
        getline(ss, part, '|'); m.price = stof(part);

        movies.push_back(m);
    }
    fin.close();

    if (movies.empty()) {
        cout << "No movies available." << endl;
        return;
    }

    int searchId;
    cout << "Enter movie ID to update: ";
    cin >> searchId;

    bool found = false;
    for (Movie& m : movies) {
        if (m.id == searchId) {
            found = true;
            cout << "\nNew movie details:\n";

            cin.ignore(); // flush newline
            cout << "Enter name: ";
            getline(cin, m.title);

            cout << "Enter time: ";
            getline(cin, m.time);

            cout << "Enter available seats: ";
            cin >> m.availableSeats;

            cout << "Enter price: ";
            cin >> m.price;

            cout << "\nMovie updated.\n";
            break;
        }
    }

    if (!found) {
        cout << "Movie not found." << endl;
        return;
    }

    ofstream fout("movie.txt");
    if (!fout.is_open()) {
        cout << "Error writing to movie.txt" << endl;
        return;
    }

    for (const Movie& m : movies) {
        fout << m.id << "|" << m.title << "|" << m.time << "|"
             << m.availableSeats << "|" << m.price << endl;
    }
    fout.close();
}
//Delete Movie 

vector<Movie> loadMoviesFromFile(const string& filename) {
    vector<Movie> movies;
    ifstream file("movie.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string part;
        Movie m;

        getline(ss, part, '|'); m.id = stoi(part);
        getline(ss, part, '|'); m.title = part;
        getline(ss, part, '|'); m.time = part;
        getline(ss, part, '|'); m.availableSeats = stoi(part);
        getline(ss, part, '|'); m.price = stof(part);

        movies.push_back(m);
    }

    file.close();
    return movies;
}
void deleteMovie(vector<Movie>& movies, const string& filename) {
    movies = loadMoviesFromFile("movie.txt");
    if (movies.empty()) {
        cout << "No movies available to delete." << endl;
        return;
    }

    int deleteId;
    cout << "Enter Movie ID to delete: ";
    cin >> deleteId;

    bool found = false;
    vector<Movie> updatedMovies;

    for (const Movie& m : movies) {
        if (m.id != deleteId) {
            updatedMovies.push_back(m);
        } else {
            found = true;
        }
    }

    if (found) {
        // Save updated list to file
        ofstream file("movie.txt");
        for (const Movie& m : updatedMovies) {
            file << m.id << "|" << m.title << "|" << m.time << "|"
                 << m.availableSeats << "|" << m.price << "\n";
        }
        file.close();

        // Update the original vector
        movies = updatedMovies;

        cout << "Movie deleted successfully!" << endl;
    } else {
        cout << "Movie ID not found." <<endl;
    }
}

//View All Bookings 
void viewAllBookings(){
    ifstream file("booking.txt");
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
    string bookingId,userId,username,movieName,seats,amount;

    getline(ss,bookingId,'|');
    getline(ss,userId,'|');
    getline(ss,username,'|');
    getline(ss,movieName,'|');
    getline(ss,seats,'|');
    getline(ss,amount,'|');

    cout<<bookingId<<"|"<<userId<<"|"<<username<<"|"<<movieName<<"|"<<seats<<"|"<<"Rs."<<amount<<"\n";
}
file.close();
}
