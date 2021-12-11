#include <helper.h>
#include <stack>
#include <unordered_map>
#include <unordered_set>


int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "pass filename" << std::endl;
    return 1;
  }

  auto file_content = helper::getFileContent(argv[1]);
  std::unordered_map<char, int> point_map;
  point_map['('] = 1;
  point_map['['] = 2;
  point_map['{'] = 3;
  point_map['<'] = 4;
  std::unordered_set<char> left_bracers  = {'(', '[', '{', '<'};
  std::unordered_set<char> right_bracers = {')', ']', '}', '>'};
  std::vector<long long> points;

  for (auto line : file_content)
  {
    bool keep = true;
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
        if ((chr - recent) != 1 && (chr - recent) != 2)
        {
          keep = false;
          break;
        }
      }
    }
    if (keep)
    {
      long long point = 0;
      while (!current_bracers.empty())
      {
        char bracer = current_bracers.top();
        current_bracers.pop();
        point = point*5 + point_map[bracer];
      }
      points.push_back(point);
    }
  }
  std::sort(points.begin(), points.end());
  std::cout << "answer: " << points[points.size()/2] << std::endl;
  return 0;
}
