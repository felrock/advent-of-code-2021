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

int same(std::string a, std::string b)
{
  int eq = 0;
  for (auto chr : a)
  {
    if (b.find(chr) == std::string::npos)
    {
      eq++;
    }
  }
  return eq;

}

std::vector<std::string> deduce(std::vector<std::string> signals)
{
  std::vector<std::string> known;
  std::string one = *std::find_if(signals.begin(), signals.end(),
      [](std::string str){ return str.size() == ONE ? true : false; });
  known.push_back(one);
  std::string four = *std::find_if(signals.begin(), signals.end(),
      [](std::string str){ return str.size() == FOUR ? true : false; });
  known.push_back(four);
  std::string seven = *std::find_if(signals.begin(), signals.end(),
      [](std::string str){ return str.size() == SEVEN ? true : false; });
  known.push_back(seven);
  std::string eight = *std::find_if(signals.begin(), signals.end(),
      [](std::string str){ return str.size() == EIGHT ? true : false; });
  known.push_back(eight);

  return known;
}

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
  int total = 0;
  for (int i=0; i < signals.size(); ++i)
  {
    auto signal = signals[i];
    auto known = deduce(signal);
    std::string number;
    for (auto d : digits[i])
    {
      if (d.size() == ONE)
      {
        number += "1";
      }
      else if(d.size() == FOUR)
      {
        number += "4";
      }
      else if(d.size() == SEVEN)
      {
        number += "7";
      }
      else if(d.size() == EIGHT)
      {
        number += "8";
      }
      else if(d.size() == 6)
      {
        if (same(known[0], d) == 1)
        {
          number += "6";
        }
        else if(same(known[1], d) == 0)
        {
          number += "9";
        }
        else
        {
          number += "0";
        }
      }
      else if(d.size() == 5)
      {
        if (same(known[0], d) == 0)
        {
          number += "3";
        }
        else if(same(known[1], d) == 1)
        {
          number += "5";
        }
        else
        {
          number += "2";
        }
      }
    }
    total += std::stoi(number);
    number.clear();
  }

  std::cout << "answer: " << total << std::endl;
  return 0;
}
