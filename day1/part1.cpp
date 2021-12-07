#include <helper.h>
#include <bits/stdc++.h>

// day 1 part 1

int main(int argc, char** argv)
{
   if (argc < 2)
   {
      std::cout << "pass filename" << std::endl;
      return 1;
   }
   auto file_content = helper::getFileContent(argv[1]);
   int previous = INT_MAX;
   int increased = 0;
   for (const auto& line : file_content)
   {
      int current = std::stoi(line);
      if (current > previous)
      {
         increased++;
      }
      previous = current;
   }

   std::cout << "answer: " << increased << std::endl;
   return 0;
}
