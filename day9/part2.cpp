#include <functional>
#include <helper.h>
#include <stack>

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "pass filename" << std::endl;
  }
  auto file_content = helper::getFileContent(argv[1]);

  const int height = file_content.size();
  const int width = file_content[0].size();
  std::vector<std::pair<int, int>> low_points;

  for (int i=0; i < height; ++i)
  {
    for (int j=0; j < width; ++j)
    {
      int center = file_content[i][j];
      // check right
      if (j+1 < width)
      {
        if (file_content[i][j+1] <= center)
        {
          continue;
        }
      }
      // check left
      if (j-1 >= 0)
      {
        if (file_content[i][j-1] <= center)
        {
          continue;
        }
      }
      // check above
      if (i-1 >= 0)
      {
        if (file_content[i-1][j] <= center)
        {
          continue;
        }
      }
      // check below
      if (i+1 < height)
      {
        if (file_content[i+1][j] <= center)
        {
          continue;
        }
      }
      low_points.emplace_back(i, j);
    }
  }

  std::vector<int> sizes;
  std::vector<std::vector<bool>> visited(height,
      std::vector<bool>(width, false));
  std::stack<std::pair<int, int>> que;
  for (auto coord : low_points)
  {
    int size = 0;
    que.push(coord);
    while (que.size() > 0)
    {
      auto que_front = que.top();
      que.pop();
      int y = que_front.first;
      int x = que_front.second;

      if (visited[y][x])
      {
        // location has been visited before goto next in que
        continue;
      }
      visited[y][x] = true;
      size++;

      // check right location
      if (x+1 < width)
      {
        if (file_content[y][x+1] != '9')
        {
          que.push({y, x+1});
        }
      }
      // check left location
      if (x-1 >= 0)
      {
        if (file_content[y][x-1] != '9')
        {
          que.push({y, x-1});
        }
      }
      // check above location
      if (y-1 >= 0)
      {
        if (file_content[y-1][x] != '9')
        {
          que.push({y-1, x});
        }
      }
      // check below location
      if (y+1 < height)
      {
        if (file_content[y+1][x] != '9')
        {
          que.push({y+1, x});
        }
      }
    }
    sizes.push_back(size);
  }

  // sort reverse
  std::sort(sizes.begin(), sizes.end(), std::greater<int>());

  std::cout << "answer: " << sizes[0]*sizes[1]*sizes[2] << std::endl;
  return 0;
}
