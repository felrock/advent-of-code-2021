#include <helper.h>
#include <stack>
#include <unordered_set>


int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "pass filename" << std::endl;
    return 1;
  }
  auto file_content = helper::getFileContent(argv[1]);

  std::unordered_map<char, int> fault_map;
  fault_map[')'] = 3;
  fault_map[']'] = 57;
  fault_map['}'] = 1197;
  fault_map['>'] = 25137;
  int points = 0;
  std::unordered_set<char> left_bracers  = {'(', '[', '{', '<'};
  std::unordered_set<char> right_bracers = {')', ']', '}', '>'};
  for (auto line : file_content)
  {
    std::stack<char> current_bracers;
    for (auto chr : line)
    {
      if (left_bracers.find(chr) != left_bracers.end())
      {
        current_bracers.push(chr);
      }
      else if(right_bracers.find(chr) != right_bracers.end())
      {
        char recent = current_bracers.top();
        current_bracers.pop();
        if ((chr - recent) != 1 && (chr-recent) != 2)
        {
          points += fault_map[chr];
        }
      }
    }
  }
  std::cout << "answer: " << points << std::endl;
  return 0;
}
