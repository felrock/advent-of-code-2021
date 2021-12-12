#include <helper.h>

class CaveSearch
{
 public:
  CaveSearch(std::unordered_map<std::string, std::vector<std::string>> graph)
    : graph(graph)
    , visited_twice(false)
  {
  }

  void findPaths(std::string local_node,
      std::unordered_set<std::string> visited_nodes = {},
      bool visited_twice=false)
  {
    if (local_node == end)
    {
      found_paths++;
    }
    else
    {
      visited_nodes.insert(local_node);
      for (const auto& next_node : graph[local_node])
      {
        if (next_node == start)
        {
          continue;
        }
        if (std::islower(next_node[0]))
        {
          if (visited_nodes.find(next_node) == visited_nodes.end())
          {
            findPaths(next_node, visited_nodes, visited_twice);
          }
          else if(!visited_twice)
          {
            findPaths(next_node, visited_nodes, true);
          }
        }
        else
        {
          findPaths(next_node, visited_nodes, visited_twice);
        }
      }
    }
  }
  int getPaths(){ return found_paths; }

 private:
  const std::string start = "start";
  const std::string end = "end";
  std::unordered_map<std::string, std::vector<std::string>> graph;
  int found_paths;
  bool visited_twice;
};

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "pass filename" << std::endl;
    return 1;
  }

  auto file_content = helper::getFileContent(argv[1]);
  std::unordered_map<std::string, std::vector<std::string>> graph;
  for (auto line : file_content)
  {
    auto p = helper::split(line, "-");
    std::string node_left  = p[0];
    std::string node_right = p[1];

    // node_left -> node_right
    if (graph.find(node_left) != graph.end())
    {
      graph[node_left].push_back(node_right);
    }
    else
    {
      graph[node_left] = std::vector<std::string>();
      graph[node_left].push_back(node_right);
    }

    // node_right -> node_left
    if (graph.find(node_right) != graph.end())
    {
      graph[node_right].push_back(node_left);
    }
    else
    {
      graph[node_right] = std::vector<std::string>();
      graph[node_right].push_back(node_left);
    }
  }

  CaveSearch cs(graph);
  cs.findPaths("start");
  std::cout << "answer: " << cs.getPaths() << std::endl;
  return 0;
}
