// user.h
#ifndef USER_H
#define USER_H
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include <string>
class User {
    public:
        int id;
        std::string username;
        std::string password;
        std::string role;

        User(): id(0) {}

        void registerUser();

};

void viewMovies();
void bookTicket(int userId, const std::string& username);
void viewMyBookings();
void cancelTicket();
void printTicket(std::string username);
void userpanel(int userId, const std::string& username);

#endif