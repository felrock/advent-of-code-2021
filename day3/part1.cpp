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
   std::vector<int> common(bits[0].size()-1);
   std::fill(common.begin(), common.end(), 0);
   for (auto b : bits)
   {
      for (int i=0; i < common.size(); ++i)
      {
         if (b[i] == '1')
         {
            common[i]++;
         }
      }
   }
   int most_common = 0;
   int least_common = 0;
   for (int i=0; i < common.size(); ++i)
   {
      if (common[i] > bits.size()/2)
      {
         most_common++;
      }
      else
      {
         least_common++;
      }
      if (i < common.size()-1)
      {
         most_common <<= 1;
         least_common <<= 1;
      }
   }
   std::cout << "answer: " << most_common * least_common << std::endl;

   return 0;
}
