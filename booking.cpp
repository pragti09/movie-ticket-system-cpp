#include<iostream>
#include<vector>
#include "movie.h"
#include "utility.h"
#include<limits>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>
#include <iomanip>
std::vector<Movie> loadAllMovies_B() {
    std::vector<Movie> movies;
    std::ifstream file("movie.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, title, time, seatsStr, priceStr;

        
        if (std::getline(ss, idStr, '|') && std::getline(ss, title, '|') &&
            std::getline(ss, time, '|') && std::getline(ss, seatsStr, '|') &&
            std::getline(ss, priceStr, '|')) 
        {
            Movie m;
            m.id = std::stoi(idStr);
            m.title = title;
            m.time = time;
            m.availableSeats = std::stoi(seatsStr);
            m.price = std::stof(priceStr);
            movies.push_back(m);
        }
    }
    file.close();
    return movies;
}
void rewriteMoviesFile_B(const std::vector<Movie>& movies) {
    std::ofstream file("movie.txt");
    for (const auto& m : movies) {
        file << m.id << "|" << m.title << "|" << m.time << "|"
             << m.availableSeats << "|" << m.price << std::endl;
    }
    file.close();
}

void bookTicket(int userId, const std::string& username) {
    int movieIdToBook;
    int requestedSeats;
    
    std::vector<Movie> movies = loadAllMovies_B();

    viewMovies(movies);
    
    std::cout << "\nEnter Movie ID to book: ";
    if (!(std::cin >> movieIdToBook)) {
        std::cout << "Invalid input." << std::endl;
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cout << "Enter number of seats: ";
    if (!(std::cin >> requestedSeats)) {
        std::cout << "Invalid input." << std::endl;
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<Movie> updatedmovie = loadAllMovies_B();
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
    rewriteMoviesFile_B(movies);

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