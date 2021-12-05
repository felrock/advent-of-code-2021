#include <helper.h>
#include <bitset>

bool checkFor(int ones, int zeroes, bool type)
{
   if (type)
   {
      return ones >= zeroes;
   }
   else
   {
      return ones < zeroes;
   }
}

void reduce(std::vector<std::string>& bits, bool type)
{
   std::vector<int> common(bits[0].size());
   while (bits.size() != 1)
   {
      // clear common
      std::fill(bits.begin(), bits.end(), 0);

      // find frequency of ones
      for (auto b : new_bits)
      {
         for (int j=0; j < b.size(); ++j)
         {
            if (b[j] == '1')
            {
               common[j]++;
            }
         }
      }

      // make a copy to transfer to
      std::vector<std::string> cpy_bits;
      int ones = common[i];
      int zeroes = new_bits.size() - ones;
      std::remove_if(oxygen.begin(), oxygen.end(), [&](std::string item){
            return item[i] == '0' && checkFor(ones, zeroes, type);
      });
   }
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
   // oxygen
   std::vector<std::string> oxygen = bits;
   reduce(oxygen, true);
   int oxygen_value = std::bitset<32>(oxygen[0]).to_ulong() << std::endl;

   std::vector<std::string> scrubber = bits;
   reduce(scrubber, false);
   int scrubber_value = std::bitset<32>(scrubber[0]).to_ulong() << std::endl;

   std::cout << "answer: " << oxygen_value*scrubber_value << std::endl;
   return 0;
}
