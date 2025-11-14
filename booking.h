#ifndef BOOKING_H
#define BOOKING_H

#include <string>

class Booking {
    public:
        int bookingId;
        int userId;
        std::string username;
        std::string movieTitle;
        int seats;
        float amount;

        Booking() : bookingId(0), userId(0), seats(0), amount(0.0f) {}
};

void bookTicket(int userId, const std::string& username);
#endif