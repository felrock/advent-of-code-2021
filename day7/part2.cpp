#include <algorithm>
#include <helper.h>

int sumInt(int n)
{
  return n*(n+1)/2;
}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "pass filename" << std::endl;
    return 1;
  }
  auto file_content = helper::getFileContent(argv[1]);
  auto crabs = helper::stoi(helper::split(file_content[0], ","));
  auto max_crab = *std::max_element(crabs.begin(), crabs.end());

  std::vector<int> range(max_crab+1, 0);
  for (auto crab : crabs)
  {
    int fuel_to_move = crab;
    int inc = -1;
    for (int i=0; i < range.size(); ++i)
    {
      if (i == crab)
      {
        inc = 1;
        fuel_to_move = 1;
      }
      else
      {
        range[i] += sumInt(fuel_to_move);
        fuel_to_move += inc;
      }
    }
  }
  auto ans = *std::min_element(range.begin(), range.end());
  std::cout << "answer: " << ans << std::endl;
  return 0;
}
