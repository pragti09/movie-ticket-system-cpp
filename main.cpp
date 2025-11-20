#include <iostream>
#include <string>
#include <limits>
#include "user.h"    
#include "movie.h"  
#include "booking.h" 

bool login(std::string & username, std::string & role, int & userId); 

void adminPanel(int userId, const std::string& username);
void userpanel(int userId, const std::string& username);

void viewMovies();
void bookTicket(int userId, const std::string& username);
void viewMyBookings(int userId);
void cancelTicket(int userId, const std::string& username);
void printTicket(int userId, const std::string& username);
void viewAllBookings();


int main(){
    User newUser;
    int choice;
    int userId;
    std::string username, role;
    do {
        std::cout<<"----- MOVIE TICKET BOOKING SYSTEM -----"<<std::endl;
        std::cout<<"1. Login As Admin"<<std::endl;
        std::cout<<"2. Login As User"<<std::endl;
        std::cout<<"3. Register As New User"<<std::endl;
        std::cout<<"4. Exit"<<std::endl;
        std::cout<<"Enter your choice:"<<std::endl;
        
        if (!(std::cin >> choice)) {
                std::cout << "Invalid input. Please enter a number." << std::endl;
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                choice = 0;
                continue;
            }

        switch (choice)
        {
        case 1:  { 
            std::cout<<"---- Login as Admin ----"<<std::endl;
            if (login(username,role, userId)) {
                if (role == "Admin") {
                    std::cout << "\nAdmin Login Successful! Welcome, " << username << std::endl;
                    adminPanel(userId, username);
                } else {
                    std::cout << "Access denied: You are not an admin.\n";
                }
            } else {
                std::cout << "Admin login failed.\n";
            }
            break;
        }

        case 2: { 
            std::cout<<"---- Login as User ----"<<std::endl;
            if (login(username,role, userId)) {
                if (role == "User") {
                    std::cout << "\nUser Login Successful! Welcome, " << username << std::endl;
                    userpanel(userId, username);
                } else {
                    std::cout << "Access denied: You are not a customer.\n";
                }
            } else {
                std::cout << "User login failed.\n";
            }
            break;
        }        

        case 3:
            std::cout<<"---- Register as New User ----"<<std::endl;
            newUser.registerUser();
            break;
        case 4:
            std::cout<<"Thank for using the system"<<std::endl;
            break;
        default:
            std::cout<<"Invalid Choice. Try again"<<std::endl;
            break;
        }
    } while (choice !=4);

    return 0;
}

void adminPanel(int userId, const std::string& username){
    std::vector<Movie> movies;
    int choice;
    Movie movieObj;
    do{
        std::cout<<"===== Admin Panel (" << username << ") ====="<<std::endl;
        std::cout<<"1. Add Movie"<<std::endl;
        std::cout<<"2. Update Movie"<<std::endl;
        std::cout<<"3. Delete Movie"<<std::endl;
        std::cout<<"4. View All Movies"<<std::endl;
        std::cout<<"5. View All Bookings"<<std::endl;
        std::cout<<"6. Logout"<<std::endl;
        std::cout<<"Enter your Choice:";
        if (!(std::cin >> choice)) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0; 
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1: movieObj.addMovie(); break;
            case 2: movieObj.updateMovie(); break;
            case 3: movieObj.deleteMovie(movies, "movie.txt"); break;
            case 4: viewMovies(); break; 
            case 5: viewAllBookings(); break;
            case 6: std::cout << "\nLogging out of Admin Panel." << std::endl; break;
            default: std::cout << "Invalid choice. Try again (1-6)." << std::endl; // Range is 1-6
        }
    } while (choice != 6);
}

void userpanel(int userId, const std::string& username){
    int choice;
    do {
        std::cout <<"\n===== User Panel (" << username << ") =====" << std::endl;
        std::cout << "1. View Available Movies " << std::endl;
        std::cout << "2. Book Ticket" << std::endl;
        std::cout << "3. View My Bookings" <<std::endl;
        std::cout << "4. Cancel Ticket" << std::endl;
        std::cout << "5. Print Ticket" << std::endl;
        std::cout << "6. Logout" << std::endl;
        std::cout << "Enter your choice: ";
        if(!(std::cin>>choice)) {
            std::cout<<"Invalid input. Please enter a number."<<std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0;
            continue;     
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch(choice) {
            case 1:viewMovies();break;
            case 2:bookTicket(userId, username);break;
            case 3:viewMyBookings(userId); break;
            case 4: cancelTicket(userId, username); break; 
            case 5: printTicket(userId, username); break;
            case 6: std::cout << "\nLogging out of User Panel. Returning to Main Menu." << std::endl; break;
            default: std::cout << "Invalid choice. Please try again (1-6)." << std::endl;
        }
    } while (choice != 6);
}



 