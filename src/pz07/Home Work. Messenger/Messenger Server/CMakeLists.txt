cmake_minimum_required(VERSION 3.15)
project(MessengerServer)

set(CMAKE_CXX_STANDARD 14)

# Always include the source and build directories in the include path.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set the output folder where your program will be created


# Find Poco package  1.8.1
find_package(Poco REQUIRED COMPONENTS Foundation Util Net XML JSON)

# no Poco_INCLUDE_DIRS, we have to set by hand
if(MSVC) # WIN32
    SET(Poco_INCLUDE_DIRS "C:/Program Files/Poco/include")
else()
    SET(Poco_INCLUDE_DIRS "/usr/local/include/Poco")
endif(MSVC)

MESSAGE( [Main] " Poco_INCLUDE_DIRS = ${Poco_INCLUDE_DIRS}")
MESSAGE( [Main] " Poco_LIBRARIES = ${Poco_LIBRARIES}")

# The following folder will be included
include_directories(
        ${MY_SRC_INCLUDE}
        ${Poco_INCLUDE_DIRS}
)

link_directories(${CMAKE_BINARY_DIR})

add_executable(MessengerServer main.cpp Server.cpp Server.h Connection.h Client.cpp Client.h)
target_link_libraries(MessengerServer ${Poco_LIBRARIES})
