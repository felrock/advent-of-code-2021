#pragma once

#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace helper
{

std::vector<std::string> getFileContent(const std::string filename)
{
   std::vector<std::string> content;
   std::ifstream file(filename);
   std::string line;
   while(std::getline(file, line))
   {
      line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
      content.push_back(line);
   }

   return content;
}

std::vector<std::string> split(std::string str, const std::string delimiter=" ")
{
   std::vector<std::string> strings;
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

std::vector<int> to_string(const std::vector<std::string>& strings)
{
   std::vector<int> numbers;
   for (const auto& str : strings)
   {
      numbers.push_back(std::stoi(str));
   }

   return numbers;
}

} // namespace helper
