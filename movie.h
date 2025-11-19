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
   
    Movie(): id(0), availableSeats(0), price(0.0f){}

    void addMovie();
    void updateMovie();
    void deleteMovie(std::vector<Movie>& movies, const std:: string& filename);

    void display() const; 
};


void viewMovies(); 


#endif