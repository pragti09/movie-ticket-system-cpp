#include "booking.h"
#include <iostream>
#include <vector>
#include "movie.h"
#include "utility.h"
#include <limits>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iomanip>

void viewMovies();
std::vector<Movie> loadAllMovies_M(); 
void rewriteMoviesFile(const std::vector<Movie>& movies);

void bookTicket(int userId, const std::string& username) {
    int movieIdToBook;
    int requestedSeats;
    
    std::vector<Movie> movies = loadAllMovies_M();

    viewMovies();
    
    std::cout << "\nEnter Movie ID to book: ";
    if (!(std::cin >> movieIdToBook)) {
        std::cout << "Invalid input." << std::endl;
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cout << "Enter number of seats";
    if (!(std::cin >> requestedSeats)) {
        std::cout << "Invalid input." << std::endl;
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto it = std::find_if(movies.begin(), movies.end(), 
                           [movieIdToBook](const Movie& m){ return m.id == movieIdToBook; });

    if (it == movies.end()) {
        std::cout << "Error: Movie ID not found." << std::endl;
        return;
    }
    
    Movie& selectedMovie = *it; 
    if (requestedSeats <= 0 || requestedSeats > selectedMovie.availableSeats) {
        std::cout << "Error: Invalid seat count or not enough seats available ("
                  << selectedMovie.availableSeats << " left)." << std::endl;
        return;
    }

    selectedMovie.availableSeats -= requestedSeats;
    rewriteMoviesFile(movies);

    float totalAmount = requestedSeats * selectedMovie.price;
    int newBookingId = getNextId("booking.txt"); 

    std::ofstream bookingFileOut("booking.txt", std::ios::app);
    if (!bookingFileOut.is_open()) {
        std::cout << "Error: Could not open booking.txt" << std::endl;
        return;
    }

    bookingFileOut << newBookingId << "|" << userId << "|" << username << "|"
                   << selectedMovie.title << "|" << requestedSeats << "|"
                   << totalAmount << std::endl;
    bookingFileOut.close();

    std::cout << "\n--- TICKET BOOKED! ---" << std::endl;
    std::cout << "Booking ID: " << newBookingId 
              << ". Total Cost: " << std::fixed << std::setprecision(2) << totalAmount << std::endl;
}


void viewMyBookings(int userId){
    std::vector<Booking> bookings;
    std::ifstream file("booking.txt");
    std::string line;
    bool found = false;
    std::string unusedUsername;

    std::cout << "\n===Your Booking Details===" << std::endl;
    std::cout << "ID | Movie | Seats | Amount" << std::endl;
    std::cout << "---|-------|-------|-------" << std::endl;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string part;
        Booking b;

        if (std::getline(ss, part, '|') && 
            (b.bookingId = stoi(part), true) &&
            std::getline(ss, part, '|') && 
            (b.userId = stoi(part), true) && 
            std::getline(ss, b.username, '|') && 
            std::getline(ss, b.movieTitle, '|') && 
            std::getline(ss, part, '|') && 
            (b.seats = stoi(part), true) &&
            std::getline(ss, part, '|')) 
        {
             b.amount = stof(part);
             bookings.push_back(b);
        }
    }
    file.close();
    
    for (const Booking& b: bookings){
        if (b.userId == userId) {
            found=true;
            std::cout << b.bookingId << " | " << b.movieTitle << " | " << b.seats << " | " << b.amount << std::endl;
        }
    }
    if(!found){
        std::cout<<" no booking found.\n";
    }
}

void cancelTicket(int userId, const std::string& username) {
    
    int bookingIdToCancel;
    std::cout << "\n--- Customer: Cancel Ticket ---" << std::endl;
    std::cout << "Enter Booking ID to cancel: ";

    if (!(std::cin >> bookingIdToCancel)) {
        std::cout << "Invalid input. Returning." << std::endl;
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::ifstream fin("booking.txt");
    std::vector<std::string> lines;
    std::string line;
    bool found = false;
    std::string cancelledMovieName;
    int cancelledSeats = 0;

    while (getline(fin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string bookingId, userIdstr, username, moviename, seats, amount;

        getline(ss, bookingId, '|');
        getline(ss, userIdstr, '|');
        getline(ss, username, '|'); 
        getline(ss, moviename, '|');
        getline(ss, seats, '|');
        getline(ss, amount, '|');

        if (std::stoi(bookingId) == bookingIdToCancel && std::stoi(userIdstr) == userId) {
            found = true;
            cancelledMovieName = moviename;
            cancelledSeats = std::stoi(seats);
            continue; 
        }

        lines.push_back(line); 
    }
    fin.close();

    if (!found) {
        std::cout << "\nNo booking found. \n";
        return;
    }
    if (cancelledSeats > 0) {
        std::vector<Movie> movies = loadAllMovies_M();
        auto it = std::find_if(movies.begin(), movies.end(), 
                               [&cancelledMovieName](const Movie& m){ return m.title == cancelledMovieName; });

        if (it != movies.end()) {
            it->availableSeats += cancelledSeats;
            rewriteMoviesFile(movies);
            std::cout << "Seats restored for movie: " << cancelledMovieName << std::endl;
        } else {
            std::cout << "Warning: Could not find movie to restore seats, data inconsistency." << std::endl;
        }
    }

    std::ofstream fout("booking.txt");
    for (const std::string& l : lines)
        fout << l << "\n";
    fout.close();

    std::cout << "\nTicket cancelled successfully!\n";
}

void printTicket(int userId, const std::string& username){
    int bookingIdToPrint;
    std::cout << "\n--- Customer: Print Ticket ---" << std::endl;
    std::cout << "Enter Booking ID to print: ";

    if (!(std::cin >> bookingIdToPrint)) {
        std::cout << "Invalid input. Returning." << std::endl;
        std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::ifstream file("booking.txt");
    std::string line;
    bool found = false;
    while(getline(file,line)){
        std::stringstream ss(line);
        std::string booking_id, user_id, uname, movie, seats, amount;
        getline(ss,booking_id, '|');
        getline(ss,user_id,'|' );
        getline(ss,uname,'|' );
        getline(ss,movie,'|' );
        getline(ss,seats,'|' );
        getline(ss,amount,'|');

        if (std::stoi(booking_id) == bookingIdToPrint && std::stoi(user_id) == userId) {
                found = true;
                
                std::cout << "\n======================================" << std::endl;
                std::cout << "          MOVIE TICKET CONFIRMATION   " << std::endl;
                std::cout << "======================================" << std::endl;
                std::cout << "Booking ID: " << booking_id << std::endl;
                std::cout << "Customer:   " << uname << std::endl; 
                std::cout << "--------------------------------------" << std::endl;
                std::cout << "Movie:      " << movie << std::endl;
                std::cout << "Seats:      " << seats << std::endl;
                std::cout << "Total Paid: Rs " << std::fixed << std::setprecision(2) << amount << std::endl; // Added formatting
                std::cout << "======================================" << std::endl;
                file.close();
                return;
            }
     }
     file.close();
    if(!found){
        std::cout<<"No tickets found!"<<std::endl;

    }      
}

void viewAllBookings() {
    std::ifstream file("booking.txt");
    std::string line;
    bool found = false;

    std::cout<<"\n====== ADMIN: ALL BOOKING RECORDS ======\n";
    std::cout<<"BookingID | UserID | Username | MovieTitle | Seats | Amount\n";
    std::cout<<"----------|--------|----------|------------|-------|-------" << std::endl;


    while(getline(file,line)){
        std::stringstream ss(line);
        std::string bookingId,userId,username,movieName,seats,amount;

        getline(ss,bookingId,'|');
        getline(ss,userId,'|');
        getline(ss,username,'|');
        getline(ss,movieName,'|');
        getline(ss,seats,'|');
        getline(ss,amount,'|');

        std::cout<<bookingId<<" | "<<userId<<" | "<<username<<" | "<<movieName<<" | "<<seats<<" | "<<"Rs."<<amount<<"\n";
        found = true;
    }
    file.close();
    if (!found) {
        std::cout << "No bookings have been recorded yet." << std::endl;
    }
}
