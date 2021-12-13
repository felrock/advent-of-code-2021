#include <algorithm>
#include <cstddef>
#include <helper.h>
#include <string>
#include <unordered_set>

std::string toCoord(int a, int b)
{
  return std::to_string(a) + "," + std::to_string(b);
}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "pass filename" << std::endl;
    return 1;
  }
  auto file_content = helper::getFileContent(argv[1]);
  std::unordered_set<std::string> dots;
  bool add_dots = true;
  for (auto line : file_content)
  {
    if (line  == "")
    {
      add_dots = false;
    }
    else if (add_dots)
    {
      dots.insert(line);
    }
    else
    {
      auto sstr = helper::split(line, " ");
      auto eq   = helper::split(sstr[2], "=");
      std::string axis = eq[0];
      int div = std::stoi(eq[1]);

      std::unordered_set<std::string> new_dots;
      for (const auto& dot : dots)
      {
        auto xy = helper::stoi(helper::split(dot, ","));
        if (axis == "x")
        {
          int x = xy[0];
          if (x > div)
          {
            int dx = x - div;
            new_dots.insert(toCoord(div - dx, xy[1]));
          }
          else
          {
            new_dots.insert(dot);
          }
        }
        else
        {
          int y = xy[1];
          if (y > div)
          {
            int dy = y - div;
            new_dots.insert(toCoord(xy[0], div - dy));
          }
          else
          {
            new_dots.insert(dot);
          }
        }
      }
      dots = new_dots;
    }
  }
  for (int i=0; i < 6; ++i)
  {
    for (int j=0; j < 40; ++j)
    {
      if (dots.find(toCoord(j, i)) != dots.end())
      {
        std::cout << "#";
      }
      else
      {
        std::cout << ".";
      }
    }
    std::cout << std::endl;
  }
  return 0;
}
