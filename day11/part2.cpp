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

  int steps = 0;
  const int height = state.size();
  const int width = state[0].size();
  const int all_states = height * width;

  while (true)
  {
    // add one to each
    for (auto& row : state)
    {
      for (auto& itm : row)
      {
        itm += 1;
      }
    }

    // flashing, keep track of previously flashed and contiue to loop
    std::vector<std::vector<bool>> flashed(state.size(), std::vector<bool>(state[0].size(), false));
    bool flash = true;
    int flash_count = 0;
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
            addAdj(j, i, state);
            flash = true;
            flash_count++;
          }
        }
      }
    }

    // set zeroes
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

    steps++;

    // check if all flashed at the same step
    if (all_states == flash_count)
    {
      break;
    }
  }

  std::cout << "answer: " <<  steps << std::endl;
  return 0;
}
