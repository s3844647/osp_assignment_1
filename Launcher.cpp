#include <iostream>

//Main menu application for Assignment 1. Not sure if it's supposed to work this way.

int main(void) {

    int selection;

    std::cout << "Concurrency problems" << std::endl;
    std::cout << "For the producer-consumer problem type 1" << std::endl;
    std::cout << "For the sleeping barbers problem type 2" << std::endl;

    std::cin >> selection;
    if (selection == 1) {
        //Placeholder code
    } else if (selection == 2) {
        //Also placeholder code
    } else {
        std::cout << "Error: Invalid input" << std::endl;
    }
    
    return 0;
}