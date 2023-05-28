#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_set>
#include <set>
#include <algorithm>

class Graph {
 private:
  std::vector<std::unordered_set<int>> vertexes_;
  std::set<int> articulation_points_;
  time_t time_;
  std::vector<int> time_in_;
  std::vector<int> time_up_;
  std::vector<bool> visited_;

  void DFS(int vertex, bool is_root) {  // конкретная вершина
    visited_[vertex] = true;
    time_in_[vertex] = time_up_[vertex] = ++time_;
    int children = 0;

    for (auto neighbour : vertexes_[vertex]) {
      if (visited_[neighbour]) {  // значит это обратное ребро
        time_up_[vertex] = std::min(time_up_[vertex], time_in_[neighbour]);
      } else {  // иначе встретили новую вершину
        ++children;
        DFS(neighbour, false);
        time_up_[vertex] = std::min(time_up_[vertex], time_up_[neighbour]);

        if (!is_root && time_in_[vertex] <= time_up_[neighbour]) {
          articulation_points_.insert(vertex);
        }
      }
    }

    if (is_root && children > 1) {
      articulation_points_.insert(vertex);
    }
  };

 public:
  explicit Graph(int nv) {
    vertexes_ = std::vector<std::unordered_set<int>>(nv);
    articulation_points_ = std::set<int>();
    time_in_ = std::vector<int>(nv);
    time_up_ = std::vector<int>(nv);
    visited_ = std::vector<bool>(nv);
  }

  std::set<int> DoDFS() {
    for (size_t i = 0; i < vertexes_.size(); ++i) {
      DFS(i, true);
    }

    return articulation_points_;
  }

  friend std::istream& operator>>(std::istream& is, Graph& g);
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int begin, end;
  is >> begin >> end;
  --begin;
  --end;

  g.vertexes_[begin].insert(end);
  g.vertexes_[end].insert(begin);

  return is;
}

int main() {
  int n, m;
  std::cin >> n >> m;

  Graph g(n);

  for (int i = 0; i < m; ++i) {
    std::cin >> g;
  }

  std::set<int> answer = g.DoDFS();
  std::cout << answer.size() << "\n";

  for (auto i : answer) {
    std::cout << i + 1 << "\n";
  }

  return 0;
}