#ifndef MOVIE_H
#define MOVIE_H

#include<string>
#include<vector>

class Movie {
public:
    int id;
    std::string title;      
    std::string time;
    float price;      
    int availableSeats;
   
    void display() const; 
};


void addMovie(std::vector<Movie>&movies);
void viewMovies(const std::vector<Movie>&movies);
void updatemovie();
void deleteMovie(std::vector<Movie>& movies, const std:: string& filename);
void viewAllBookings();

#endif