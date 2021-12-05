#include <helper.h>
#include <bits/stdc++.h>

// day 1 part 2

int main(int argc, char** argv)
{
   if (argc < 2)
   {
      std::cout << "pass filename" << std::endl;
      return 1;
   }

   auto file_content = helper::getFileContent(argv[1]);
   auto numbers = helper::to_string(file_content);
   int previous = INT_MAX;
   int increased = 0;
   for (int i=0; i < numbers.size()-2; ++i)
   {
      int current = numbers[i+0] + numbers[i+1] + numbers[i+2];
      if (current > previous)
      {
         increased++;
      }
      previous = current;
   }
   std::cout << "answer: " << increased << std::endl;

   return 0;
}
