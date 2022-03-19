#include "LinearFeedbackShiftRegister.hpp"

#include <random>
#include <sstream>
#include <iostream>

int main(void)
{
   LinearFeedbackShiftRegister eng(100);
   int i;

   std::cout << "Raw numbers" << std::endl;
   for (i = 0; i < 10; i++)
   {
     std::cout << eng() << std::endl;
   }
   std::cout << std::endl;

   std::cout << "Uniform real numbers" << std::endl;
   std::uniform_real_distribution<double> distribution(0.0,1.0);

  for (int i=0; i<10; ++i) {
    std::cout << distribution(eng) << std::endl;
  }

  std::cout << "Serialised: " << eng << std::endl;

  std::stringstream ss;

  ss << eng << std::endl;
  ss.seekg(0, std::ios::beg);
  LinearFeedbackShiftRegister eng2;
  ss >> eng2;

  std::cout << "Recovery" << std::endl;
  std::cout << eng() << "," << eng2() << std::endl; 


   return 0;
}
