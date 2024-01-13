#include "IDatabaseConnection.hpp"
#include <iostream>

IDatabaseConnection::IDatabaseConnection(std::string serverAddress)
    : mServerAddress{serverAddress} {}

void IDatabaseConnection::connect() {
  std::cout << "Connecting to database server " << mServerAddress << "\n";
  // initialize real DB connection
  if (nonConnect != nullptr) {
    std::cout << "Callback was set" << std::endl;
    nonConnect(3, 6);
  }
}

void IDatabaseConnection::disconnect() {
  std::cout << "Disconnecting from database\n";
  // close the real connection
}

void IDatabaseConnection::setOnConnect(Callback onConnect) {
  nonConnect = onConnect;
}