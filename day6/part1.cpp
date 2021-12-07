#include <helper.h>

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "pass filename" << std::endl;

    return 1;
  }
  auto file_content = helper::getFileContent(argv[1]);
  auto states = helper::stoi(helper::split(file_content[0], ","));

  std::vector<unsigned long long> times(9, 0);
  for (auto state : states)
  {
    times[state]++;

  }
  for (int i=0; i < 80; ++i)
  {
    std::vector<unsigned long long> temp_times(9, 0);
    for (int j=8; j > 0; --j)
    {
      temp_times[j-1] = times[j];
    }
    temp_times[6] += times[0];
    temp_times[8] += times[0];
    times = temp_times;
  }
  unsigned long long sum = 0;
  for ( auto t : times)
  {
    sum += t;
  }
  std::cout << "answer: " << sum << std::endl;
  return 0;
}
