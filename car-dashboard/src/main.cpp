#include <C:\Working\C-development\car-dashboard\src\dashboard.h>
#include "database.h"
#include <iostream>

int main() {
    try {
        // Initialize vehicle
        Vehicle vehicle;
        
        // Initialize database
        Database db;
        if (!db.connect("vehicle.db")) {
            std::cerr << "Failed to connect to database" << std::endl;
            return 1;
        }
        
        // Initialize and run dashboard
        Dashboard dashboard(vehicle);
        dashboard.run();
        
        // Save final state
        db.saveVehicleState(vehicle);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}