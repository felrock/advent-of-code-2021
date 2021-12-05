#include <helper.h>

class BingoPlayer
{
 public:
  BingoPlayer(std::vector<std::string> raw)
  {
    for (auto line : raw)
    {
      auto values = helper::split_ud(line, ' ');
      auto values_int = helper::stoi(values);

      std::vector<std::pair<int, bool>> r;
      for (const auto& val : values_int)
      {
        r.emplace_back(val, false);
      }
      numbers.push_back(r);
    }
  }

  void add(int number)
  {
    for (int i=0; i < numbers.size(); ++i)
    {
      for (int j=0; j < numbers[0].size(); ++j)
      {
        if (numbers[i][j].first == number)
        {
          numbers[i][j].second = number;
        }
      }
    }
    for (auto& row : numbers)
    {
      for (auto& itm : row)
      {
        if (itm.first == number)
        {
          itm.second = true;
        }
      }
    }
  }

  bool won()
  {
    // check rows
    for (const auto& row : numbers)
    {
      bool won = true;
      for (const auto& itm : row)
      {
        won &= itm.second;
      }
      if (won)
      {
        return true;
      }
    }
    // check columns
    for (int i=0; i < numbers[0].size(); ++i)
    {
      bool won = true;
      for (int j=0; j < numbers.size(); ++j)
      {
        won &= numbers[j][i].second;
      }
      if (won)
      {
        return true;
      }
    }
    return false;
  }

  int nonWinningNumbers()
  {
    int sum = 0;
    for (auto& row : numbers)
    {
      for( auto& itm : row)
      {
        if (!itm.second)
        {
          sum += itm.first;
        }
      }
    }
    return sum;
  }
 private:
  std::vector<std::vector<std::pair<int, bool>>> numbers;
};

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "pass filename" << std::endl;
    return 1;
  }

  auto file_content = helper::getFileContent(argv[1]);
  auto bingo_round = helper::stoi(helper::split(file_content[0],","));

  std::vector<std::string> current_player;
  std::vector<BingoPlayer> bingo_players;
  for (int i=2; i < file_content.size(); ++i)
  {
    if (file_content[i].size() == 1)
    {
      bingo_players.emplace_back(current_player);
      current_player.clear();
    }
    else
    {
      current_player.push_back(file_content[i]);
    }
  }
  bingo_players.emplace_back(current_player);
  bool win = false;
  int last_winner_sum =0, winning_number=0, last_winning_number=0;
  std::vector<bool> winners(bingo_players.size());
  for (const int& current_number : bingo_round)
  {
    winning_number = current_number;
    for (int i=0; i < bingo_players.size(); ++i)
    {
      bingo_players[i].add(current_number);
      win = bingo_players[i].won();
      if (win)
      {
        int count = 0;
        for (auto win : winners)
        {
          if (win)
          {
            count++;
          }
        }
        if (count == winners.size()-1)
        {
          last_winner_sum = bingo_players[i].nonWinningNumbers();
          last_winning_number = winning_number;
        }
        winners[i] = true;
      }
    }
  }
  std::cout << "answer: " << last_winner_sum*last_winning_number << std::endl;
  return 0;
}
