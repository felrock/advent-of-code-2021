#include <helper.h>

using Point = helper::Point;
using Line = helper::Line;
using Grid = std::vector<std::vector<int>>;

void draw(Grid& g, Line line)
{
  Point pen = line.first;
  Point dir = helper::direction_simple(line);

  while (!helper::equal(pen, line.second))
  {
    g[pen.second][pen.first]++;
    pen = helper::add(pen, dir);
  }
  g[pen.second][pen.first]++;
}

void printGrid(Grid g)
{
  for (auto row : g)
  {
    for (auto itm : row)
    {
      std::cout << itm;
    }
    std::cout << std::endl;
  }
}

int countOverlap(Grid g)
{
  int count=0;
  for (auto row : g)
  {
    for (auto p : row)
    {
      if (p >= 2)
      {
        count++;
      }
    }
  }
  return count;
}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "pass filename" << std::endl;
    return 1;
  }

  auto file_content = helper::getFileContent(argv[1]);
  std::vector<Line> lines;
  int max_x = 0;
  int max_y = 0;
  for (auto& content : file_content)
  {
    auto first_split = helper::split(content, " -> ");
    auto second_split = helper::stoi(helper::split(first_split[0], ","));
    auto third_split = helper::stoi(helper::split(first_split[1], ","));
    auto first_point = Point(second_split[0], second_split[1]);
    auto second_point = Point(third_split[0], third_split[1]);
    lines.emplace_back(first_point, second_point);

    if (max_x < second_split[0])
    {
      max_x = second_split[0];
    }
    if (max_x < third_split[0])
    {
      max_x = third_split[0];
    }

    if (max_y < second_split[1])
    {
      max_y = second_split[1];
    }
    if (max_y < third_split[1])
    {
      max_y = third_split[1];
    }
  }
  Grid grid(max_x+1, std::vector<int>(max_y+1, 0));
  for (auto& line : lines)
  {
    if (line.first.first == line.second.first || line.first.second == line.second.second)
    {
      draw(grid, line);
    }
  }
  std::cout << "answer: " << countOverlap(grid) << std::endl;
  return 0;
}
