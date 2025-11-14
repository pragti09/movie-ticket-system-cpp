// Utility.cpp
#include "Utility.h"
#include <sstream>
#include <limits>
#include <iostream>

// Helper function to determine the next ID for any file (MovieID, UserID, BookingID)
int getNextId(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    int maxId = 0;

    if (!file.is_open()) {
        if (filename == "bookings.txt") return 101;
        return 1;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        
        std::string idStr;

    
    if (std::getline(ss, idStr, '|')) {
        try {
            int currentId = std::stoi(idStr);
            if (currentId > maxId) {
                maxId = currentId;
            }
        } catch (...) {
            std::cout << "Warning: Corrupt ID found in file. Skipping line." << std::endl;
        }
    }
}
    file.close();
    return maxId + 1;
}