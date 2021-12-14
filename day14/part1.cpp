#include <algorithm>
#include <helper.h>
#include <unordered_map>

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "pass filename" << std::endl;
    return 1;
  }
  auto file_content = helper::getFileContent(argv[1]);

  std::unordered_map<std::string, std::string> rules;
  std::unordered_set<char> types;
  std::string polymer = file_content[0];

  for (int i=2; i < file_content.size(); ++i)
  {
    auto split = helper::split(file_content[i], " -> ");
    rules[split[0]] = split[1];
    types.insert(split[1][0]);
  }

  for (int i=0; i < 10; ++i)
  {
    std::string new_polymer;
    for (int j=0; j < polymer.size()-1; ++j)
    {
      std::string p = polymer.substr(j, 2);
      // only add left letter to avoid doubles
      new_polymer += polymer[j] + rules[p];
    }
    polymer = new_polymer + polymer[polymer.size()-1];
  }

  // should keep track of this earlier
  int max_q = 0;
  int min_q = polymer.size();
  for (const auto& type : types)
  {
    int count = std::count(polymer.begin(), polymer.end(), type);
    if (count > max_q)
    {
      max_q = count;
    }
    if (count < min_q)
    {
      min_q = count;
    }
  }

  std::cout << "answer: " <<  max_q - min_q << std::endl;
  return 0;
}
