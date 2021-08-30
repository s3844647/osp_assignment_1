#include <iostream>
#include <stdlib.h>
#include "ProdCon.h"

//Main menu application for Assignment 1. Not sure if it's supposed to work this way.

int main(void)
{

   int selection;
   bool progRunning = true;

   while (progRunning)
   {
      std::cout << "Concurrency problems" << std::endl;
      std::cout << "For the producer-consumer problem type 1" << std::endl;
      std::cout << "For the sleeping barbers problem type 2" << std::endl;
      std::cout << "To exit the program type 3" << std::endl;

      std::cin >> selection;
      if (selection == 1)
      {
         progRunning = false;
         ProdCon *pc = new ProdCon();
         pc->runMethod();
      }
      else if (selection == 2)
      {
      }
      else if (selection == 3)
      {
         exit(0);
      }
      else
      {
         std::cout << "Error: Invalid input" << std::endl;
         std::cout << std::endl;
      }
   }

   return 0;
}