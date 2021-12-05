#include <helper.h>
#include <bitset>

std::string reduce(std::vector<std::string> bits, bool rating)
{
   std::vector<int> common(bits[0].size());
   int i=0; // current bit index
   while (bits.size() >= 1)
   {
      // clear common
      std::fill(common.begin(), common.end(), 0);

      // find frequency of ones
      for (auto bit : bits)
      {
         for (int j=0; j < bit.size(); ++j)
         {
            if (bit[j] == '1')
            {
               common[j]++;
            }
         }
      }
      std::vector<std::string> cpy_bits;
      int ones = common[i];
      int zeroes = bits.size() - ones;
      for (auto bit : bits)
      {
         if(rating)
         {
            if (bit[i] == '1' && ones >= zeroes)
            {
               cpy_bits.push_back(bit);
            }
            else if (bit[i] == '0' && ones < zeroes)
            {
               cpy_bits.push_back(bit);
            }
         }
         else
         {
            if (bit[i] == '0' && ones >= zeroes)
            {
               cpy_bits.push_back(bit);
            }
            else if (bit[i] == '1' && ones < zeroes)
            {
               cpy_bits.push_back(bit);
            }
         }
      }
      i++;
      bits = cpy_bits;
   }
   return bits[0];
}


int main(int argc, char** argv)
{
   if (argc < 2)
   {
      std::cout << "pass filename" << std::endl;
      return 1;
   }
   // read input
   auto bits = helper::getFileContent(argv[1]);

   auto oxy_rating = reduce(bits, true);
   auto oxy_value = std::bitset<12>(oxy_rating).to_ulong();
   auto scr_rating = reduce(bits, false);
   auto scr_value = std::bitset<12>(scr_rating).to_ulong();
   std::cout << "answer: " << oxy_value*scr_value << std::endl;
   return 0;
}
