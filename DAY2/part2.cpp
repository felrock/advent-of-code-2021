#include <helper.h>

// day2 part2

int main(int argc, char** argv)
{
   if (argc < 2)
   {
      std::cout << "pass filename" << std::endl;
      return 1;
   }

   // read input
   auto file_content = helper::getFileContent(argv[1]);
   int horizontal = 0;
   int depth = 0;
   int aim = 0;
   for (auto& line : file_content)
   {
      auto l = helper::split(line);
      int num = std::stoi(l[1]);
      std::string inc = l[0];
      if (inc == "forward")
      {
         horizontal += num;
         depth += num*aim;
      }
      else if (inc == "up")
      {
         aim -= num;
      }
      else if (inc == "down")
      {
         aim += num;
      }
      else
      {
         std::cout << "error" << std::endl;
      }
   }
   std::cout << "answer: " << depth * horizontal << std::endl;
   return 0;
}
