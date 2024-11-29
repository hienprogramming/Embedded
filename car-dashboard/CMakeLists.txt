cmake_minimum_required(VERSION 3.10)
project(car_dashboard)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Đường dẫn tới SFML
set(SFML_DIR "C:/Users/ADMIN/Downloads/SFML-2.6.1-windows-vc17-64-bit/SFML-2.6.1")
set(SFML_ROOT "C:/Users/ADMIN/Downloads/SFML-2.6.1-windows-vc17-64-bit/SFML-2.6.1/bin")

# Đường dẫn tới SQLite
set(SQLite3_INCLUDE_DIRS "C:/Windows/System32")
set(SQLite3_LIBRARIES "C:/Windows/System32/sqlite3.dll")

# Tìm SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${SFML_INCLUDE_DIR}
    ${SQLite3_INCLUDE_DIRS}
)

# Source files
set(SOURCES
    src/main.cpp
    src/dashboard.cpp
    src/vehicle.cpp
    src/database.cpp
)

# Executable
add_executable(car_dashboard ${SOURCES})

# Link libraries
target_link_libraries(car_dashboard 
    PRIVATE
    ${SQLite3_LIBRARIES}
    sfml-graphics
    sfml-window
    sfml-system
)

# Copy DLLs
if(WIN32)
    file(COPY "${SFML_ROOT}/bin/sfml-graphics-2.dll" DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "${SFML_ROOT}/bin/sfml-window-2.dll" DESTINATION ${CMAKE_BINARY_DIR})
    file(COPY "${SFML_ROOT}/bin/sfml-system-2.dll" DESTINATION ${CMAKE_BINARY_DIR})
endif()