#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include "movie.h"
#include "utility.h"
#include <sstream>

std::vector<Movie> loadAllMovies_M() {
    std::vector<Movie> movies;
    std::ifstream file("movie.txt");
    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, title, time, seatsStr, priceStr;

        if (getline(ss, idStr, '|') && getline(ss, title, '|') &&
            getline(ss, time, '|') && getline(ss, seatsStr, '|') &&
            getline(ss, priceStr, '|')) 
        {
           
            Movie m;
            m.id = std::stoi(idStr);
            m.title = title;
            m.time = time;
            m.availableSeats = stoi(seatsStr);
            m.price = std::stof(priceStr);
            movies.push_back(m);
        }
    }
    file.close();
    return movies;
}

void rewriteMoviesFile(const std::vector<Movie>& movies) {
    std::ofstream file("movie.txt"); 
    for (const auto& m : movies) {
        file << m.id << "|" << m.title << "|" << m.time << "|"
             << m.availableSeats << "|" << m.price << std::endl; 
    }
    file.close();
}

void Movie::display() const {
    std::cout<<"ID: "<<id;
    std::cout<<" | Name: "<<title;
    std::cout<<" | Time: "<<time;
    std::cout<<" |Seats: "<<availableSeats;
    std::cout<<" | Price: "<<price<<std::endl;
}

void viewMovies(){
    std::ifstream file("movie.txt");
    
    std::string line;
    std::cout << "\n--- Current Movies and Showtimes ---" << std::endl;
    std::cout << "ID | Title | Time | Seats | Price" << std::endl;
    std::cout << "---|-------|------|-------|-------" << std::endl;

    bool found=false;

    while(getline(file, line)){
        std::stringstream ss(line);
        std::string id, title, time, seats, price;
        getline(ss, id, '|');
        getline(ss, title, '|');
        getline(ss, time, '|');
        getline(ss, seats, '|');
        getline(ss, price, '|');
        std::cout<<id<<" | "<<title<<" | "<<time<<" | "<<seats<<" | "<<price<<std::endl;
        found = true;
    }
    file.close();
    if (!found) {
        std::cout << "No movies currently scheduled." << std::endl;
    }

}


void Movie::addMovie(){ 
    std::cout << "\n--- Add New Movie ---" << std::endl;

    std::cout<<"Enter Movie Name: ";
    getline(std::cin, title);

    std::cout<<"Enter Movie Time: ";
    getline(std::cin, time);

    std::cout<<"Enter Total seats: ";
    std::cin>>availableSeats;

    std::cout<<"Enter Ticket Price: ";
    std::cin>>price;
    
    std::cin.ignore(); 
     
    id = getNextId("movie.txt");
    
    
    std::ofstream outFile("movie.txt", std::ios::app);
    if(outFile.is_open()){
        outFile<<id<<"|";
        outFile<<title<<"|";
        outFile<<time<<"|";
        outFile<<availableSeats<<"|";
        outFile<<price<<"|"<<std::endl;

        outFile.close();
        std::cout<<"\nMovie added successfully!\n";
    } else {
        std::cout<<"\nError: Could not open movie.txt file!\n ";
    }

}                                           


void Movie:: updateMovie() {
    std::vector<Movie> movies;

    std::ifstream fin("movie.txt");
    if (!fin.is_open()) {
        std::cout << "Error opening movie.txt" << std::endl;
        return;
    }

    std::string line;
    while (getline(fin, line)) {
        std::stringstream ss(line);
        std::string part;
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
        std::cout << "No movies available." << std::endl;
        return;
    }
    viewMovies();
    int searchId;
    std::cout << "Enter movie ID to update: ";
    std::cin >> searchId;

    bool found = false;
    for (Movie& m : movies) {
        if (m.id == searchId) {
            found = true;
            std::cout << "\nNew movie details:\n";

            std::cin.ignore(); 
            std::cout << "Enter name: ";
            getline(std::cin, m.title);

            std::cout << "Enter time: ";
            getline(std::cin, m.time);

            std::cout << "Enter available seats: ";
            if(!(std::cin >> m.availableSeats)) {
                std::cout<<"Invalid number of seats entered."<<std::endl;
                std::cin.clear();
                std::cin.ignore();
            };

            std::cout << "Enter price: ";
            if(!(std::cin >> m.price)) {
                std::cout<<"Invalid price entered."<<std::endl;
                std::cin.clear();
                std::cin.ignore();
            };

            std::cout << "\nMovie updated.\n";
            break;
        }
    }

    if (!found) {
        std::cout << "Movie not found." << std::endl;
        return;
    }

    std::ofstream fout("movie.txt");
    if (!fout.is_open()) {
        std::cout << "Error writing to movie.txt" << std::endl;
        return;
    }

    for (const Movie& m : movies) {
        fout << m.id << "|" << m.title << "|" << m.time << "|"
             << m.availableSeats << "|" << m.price << std::endl;
    }
    fout.close();
}




void Movie::deleteMovie(std::vector<Movie>& movies, const std::string& filename) {
    movies = loadAllMovies_M();
    std::cout << "\n--- ADMIN: Delete Movie ---" << std::endl;
    if (movies.empty()) {
        std::cout << "No movies available to delete." << std::endl;
        return;
    }
    viewMovies();
    int deleteId;
    std::cout << "Enter Movie ID to delete: ";
    std::cin >> deleteId;

    bool found = false;
    std::vector<Movie> updatedMovies;

    for (const Movie& m : movies) {
        if (m.id != deleteId) {
            updatedMovies.push_back(m);
        } else {
            found = true;
        }
    }

    if (found) {
       
        std::ofstream file("movie.txt");
        for (const Movie& m : updatedMovies) {
            file << m.id << "|" << m.title << "|" << m.time << "|"
                 << m.availableSeats << "|" << m.price << "\n";
        }
        file.close();

        movies = updatedMovies;

        std::cout << "Movie deleted successfully!" << std::endl;
    } else {
        std::cout << "Movie ID not found." <<std::endl;
    }
}


