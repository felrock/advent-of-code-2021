#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string str)
{
   std::vector<std::string> strings;
   std::string delimiter = " ";

   size_t pos = 0;
   std::string token;
   while ((pos = str.find(delimiter)) != std::string::npos) {
      token = str.substr(0, pos);
      strings.push_back(token);
      str.erase(0, pos + delimiter.length());
   }
   strings.push_back(str);
   return strings;
}

int main()
{
   // read input
   std::ifstream file("input");
   std::string line;
   int horizontal = 0;
   int depth = 0;
   while(std::getline(file, line))
   {
      auto l = split(line);
      int num = std::stoi(l[1]);
      std::string inc = l[0];
      if (inc == "forward")
      {
         horizontal += num;
      }
      else if (inc == "up")
      {
         depth -= num; 
      }
      else if (inc == "down")
      {
         depth += num; 
      }
      else
      {
         std::cout << "error" << std::endl;
      }
   }
   std::cout << "depth * horizontal: " << depth*horizontal << std::endl;
   return 0;
}