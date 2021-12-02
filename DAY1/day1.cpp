#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
   // part one
   std::ifstream file("input");
   std::vector<int> input;
   std::string line;
   int previous = INT_MAX;
   int increased = 0;
   while (std::getline(file, line))
   {
      int current = std::stoi(line);
      input.push_back(current);
      if (current > previous)
      {
         increased++;
      }
      previous = current;
   }
   std::cout << "increased: " << increased << std::endl;
   // part two
   previous = INT_MAX;
   increased = 0;
   for (int i=0; i < input.size()-2; ++i)
   {
      int current = input[i+0] + input[i+1] + input[i+2]; 
      if (current > previous)
      {
         increased++;
      }
      previous = current;
   }
   std::cout << "increased: " << increased << std::endl;
   return 0;
}
