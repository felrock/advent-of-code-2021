#include <helper.h>

void addAdj(int x, int y, std::vector<std::vector<int>>& grid)
{
  grid[y][x]++;
  if (x-1 >= 0)
  {
    grid[y][x-1]++;
  }
  if (y-1 >= 0)
  {
    grid[y-1][x]++;
  }
  if (x+1 < grid[0].size())
  {
    grid[y][x+1]++;
  }
  if (y+1 < grid.size())
  {
    grid[y+1][x]++;
  }

  if (y+1 < grid.size() && x+1 < grid[0].size())
  {
    grid[y+1][x+1]++;
  }
  if (y-1 >= 0 && x+1 < grid[0].size())
  {
    grid[y-1][x+1]++;
  }
  if (y+1 < grid.size() && x-1 >= 0)
  {
    grid[y+1][x-1]++;
  }
  if (y-1 >= 0 && x-1 >= 0)
  {
    grid[y-1][x-1]++;
  }
}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "pass filename" << std::endl;
    return 1;
  }
  auto file_content = helper::getFileContent(argv[1]);
  std::vector<std::vector<int>> state;
  for (auto line : file_content)
  {
    std::vector<int> row;
    for(auto chr : line)
    {
      row.push_back(chr-'0');
    }
    state.push_back(row);
  }

  int flashes = 0;
  const int height = state.size();
  const int width = state[0].size();

  for (int step=0; step < 100; ++step)
  {
    // add one to each
    for (auto& row : state)
    {
      for (auto& itm : row)
      {
        itm += 1;
      }
    }

    // flashes, keep track of previous flashed and continue to loop over
    // the state to update newly flashed
    std::vector<std::vector<bool>> flashed(state.size(),
        std::vector<bool>(state[0].size(), false));
    bool flash = true;
    while (flash)
    {
      flash = false;
      for (int i=0; i < height; ++i)
      {
        for (int j=0; j < width; ++j)
        {
          if (state[i][j] >= 10 && !flashed[i][j])
          {
            flashed[i][j] = true;
            flashes++;
            addAdj(j, i, state);
            flash = true;
          }
        }
      }
    }

    // set zeros
    for (auto& row : state)
    {
      for (auto& itm : row)
      {
        if (itm >= 10)
        {
          itm = 0;
        }
      }
    }
  }
  std::cout << "answer: " << flashes << std::endl;
  return 0;
}
