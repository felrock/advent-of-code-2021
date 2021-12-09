#include <helper.h>

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "pass filename" << std::endl;
  }
  auto file_content = helper::getFileContent(argv[1]);
  const int height = file_content.size();
  const int width = file_content[0].size();
  int low_points = 0;
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
      low_points += (center-'0') + 1;
    }
  }
  std::cout << "answer: " << low_points << std::endl;
  return 0;
}
