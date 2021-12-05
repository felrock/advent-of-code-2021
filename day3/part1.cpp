#include <helper.h>

// day 3 part 1

int main(int argc, char** argv)
{
   if (argc < 2)
   {
      std::cout << "pass filename" << std::endl;
      return 1;
   }

   // read input
   auto bits = helper::getFileContent(argv[1]);
   std::cout << bits[0] << std::endl;
   std::cout << bits[0].size() << std::endl;
   std::vector<int> common(bits[0].size());
   std::fill(common.begin(), common.end(), 0);
   for (auto b : bits)
   {
      std::cout << b << std::endl;
      for (int i=0; i < common.size(); ++i)
      {
         if (b[i] == '1')
         {
            common[i]++;
         }
      }
   }
   std::cout << bits.size() << std::endl;
   for (auto c : common)
   {
      std::cout << c << " ";
   }
   std::cout << std::endl;
   int most_common = 0;
   int least_common = 0;
   for (int i=0; i < common.size(); ++i)
   {
      std::cout << "answer: " << most_common << " " <<least_common << std::endl;
      if (common[i] > bits.size()/2)
      {
         most_common++;
         most_common <<= 1;
      }
      else
      {
         least_common++;
         least_common <<= 1;
      }
   }
   std::cout << "answer: " << most_common * least_common << std::endl;

   return 0;
}
