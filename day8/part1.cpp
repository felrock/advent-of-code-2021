#include <helper.h>

// segments needed per digit
const int ZERO  = 6;
const int ONE   = 2;
const int TWO   = 5;
const int THREE = 5;
const int FOUR  = 4;
const int FIVE  = 5;
const int SIX   = 6;
const int SEVEN = 3;
const int EIGHT = 7;
const int NINE  = 6;

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "pass filename" << std::endl;
    return 1;
  }
  auto file_content = helper::getFileContent(argv[1]);
  std::vector<std::vector<std::string>> signals;
  std::vector<std::vector<std::string>> digits;

  for (auto line : file_content)
  {
    auto segments = helper::split(line, " ");
    bool div_found = false;
    std::vector<std::string> signal_row;
    std::vector<std::string> digit_row;
    for (auto segment : segments)
    {
      if (segment == "|")
      {
        div_found = true;
      }
      else if (!div_found)
      {
        signal_row.push_back(segment);
      }
      else
      {
        digit_row.push_back(segment);
      }
    }
    signals.push_back(signal_row);
    digits.push_back(digit_row);
  }
  int taget_numbers = 0;
  for (auto digit_row : digits)
  {
    for (auto digit : digit_row)
    {
      if (digit.size() == ONE)
      {
        taget_numbers++;
      }
      else if(digit.size() == FOUR)
      {
        taget_numbers++;
      }
      else if(digit.size() == SEVEN)
      {
        taget_numbers++;
      }
      else if(digit.size() == EIGHT)
      {
        taget_numbers++;
      }
    }
  }
  std::cout << "answer: " << taget_numbers << std::endl;
  return 0;
}
