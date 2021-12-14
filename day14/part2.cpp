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

  // map the resulting pairs directly
  std::unordered_map<std::string, std::pair<std::string, std::string>> rules;
  std::string polymer = file_content[0];
  for (int i=2; i < file_content.size(); ++i)
  {
    auto split = helper::split(file_content[i], " -> ");
    rules[split[0]] = {split[0][0] + split[1], split[1] + split[0][1]};
  }

  // count all the pairs that are generated
  std::unordered_map<std::string, unsigned long long> pair_counter;
  for (long long j=0; j < polymer.size()-1; ++j)
  {
    std::string p = polymer.substr(j, 2);
    pair_counter[p]++;
  }
  for (int i=0; i < 40; ++i)
  {
    std::unordered_map<std::string, unsigned long long> new_pair_counter;
    for (auto& pc : pair_counter)
    {
      auto rule_pair = rules[pc.first];

      new_pair_counter[rule_pair.first] += pc.second;
      new_pair_counter[rule_pair.second] += pc.second;
    }
    pair_counter = new_pair_counter;
  }

  // count the first letter occurance in each pair
  std::unordered_map<char, unsigned long long> type_counter;
  // add last letter of polymer, since we add from left
  type_counter[polymer[polymer.size()-1]]++;
  for (auto& pc : pair_counter)
  {
    type_counter[pc.first[0]] += pc.second;
  }
  auto max_q = *std::max_element(type_counter.begin(), type_counter.end(),
      [](const auto& a, const auto& b){return a.second < b.second;});

  auto min_q = *std::min_element(type_counter.begin(), type_counter.end(),
      [](const auto& a, const auto& b){return a.second < b.second;});

  std::cout << "answer: " << max_q.second - min_q.second << std::endl;
  return 0;
}
