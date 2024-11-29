#pragma once
#include <sqlite3.h>
#include "vehicle.h"

class Database {
private:
    sqlite3* db;
    
public:
    Database();
    ~Database();
    
    bool connect(const char* filename);
    bool saveVehicleState(const Vehicle& vehicle);
    bool loadVehicleState(Vehicle& vehicle);
    void close();
};