#include "database.h"
#include <iostream>

Database::Database() : db(nullptr) {}

Database::~Database() {
    close();
}

bool Database::connect(const char* filename) {
    int rc = sqlite3_open(filename, &db);
    if (rc) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Create table if not exists
    const char* sql = 
        "CREATE TABLE IF NOT EXISTS vehicle_state ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "speed INTEGER,"
        "battery_level REAL,"
        "temperature REAL,"
        "ac_temperature REAL,"
        "drive_mode INTEGER,"
        "gear INTEGER,"
        "total_distance REAL,"
        "remaining_range REAL,"
        "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP"
        ");";

    char* errMsg = nullptr;
    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool Database::saveVehicleState(const Vehicle& vehicle) {
    const char* sql = 
        "INSERT INTO vehicle_state (speed, battery_level, temperature, "
        "ac_temperature, drive_mode, gear, total_distance, remaining_range) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_int(stmt, 1, vehicle.getSpeed());
    sqlite3_bind_double(stmt, 2, vehicle.getBatteryLevel());
    sqlite3_bind_double(stmt, 3, vehicle.getTemperature());
    sqlite3_bind_double(stmt, 4, vehicle.getACTemperature());
    sqlite3_bind_int(stmt, 5, static_cast<int>(vehicle.getDriveMode()));
    sqlite3_bind_int(stmt, 6, static_cast<int>(vehicle.getGear()));
    sqlite3_bind_double(stmt, 7, vehicle.getTotalDistance());
    sqlite3_bind_double(stmt, 8, vehicle.getRemainingRange());

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

void Database::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}