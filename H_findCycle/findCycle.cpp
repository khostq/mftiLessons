#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_set>
#include <algorithm>

enum Colour { WHITE, GREY, BLACK };

class Graph {
 private:
  std::vector<std::unordered_set<int>> vertexes_;
  std::vector<int> dynasty_;

  bool has_circle_ = false;
  int last_ = -1;

  // проверка цикличности
  bool DFS2(size_t vertex, std::vector<Colour>& visited) {
    visited[vertex] = GREY;

    if (has_circle_) {
      return true;
    }

    for (auto neighbour : vertexes_[vertex]) {
      dynasty_[neighbour] = vertex;

      if (visited[neighbour] == GREY) {
        has_circle_ = true;
        last_ = neighbour;
      }

      if (visited[neighbour] == WHITE) {
        DFS2(neighbour, visited);
        if (has_circle_) {
          return true;
        }
      }
    }
    visited[vertex] = BLACK;

    return false;
  };

 public:
  explicit Graph(int nv) {
    vertexes_ = std::vector<std::unordered_set<int>>(nv);
    dynasty_ = std::vector<int>(nv, -1);
  }

  friend std::istream& operator>>(std::istream& is, Graph& g);

  // Проверка на цикличность
  int GetHasCircle() {
    std::vector<Colour> visited = std::vector<Colour>(vertexes_.size(), WHITE);

    for (size_t i = 0; i < vertexes_.size(); ++i) {
      if (visited[i] == WHITE) {
        if (DFS2(i, visited)) {
          return last_;
        }
      }
    }

    return -1;
  }

  std::vector<int> GetDynasty() {
    return dynasty_;
  }

  bool HasCircle() {
    return has_circle_;
  }
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int begin, end;
  is >> begin >> end;
  --begin;
  --end;

  g.vertexes_[begin].insert(end);

  return is;
}

int main() {
  int n, m;
  std::cin >> n >> m;

  Graph g(n);

  for (int i = 0; i < m; ++i) {
    std::cin >> g;
  }

  int last = g.GetHasCircle();

  if (!g.HasCircle()) {
    std::cout << "NO";
  } else {
    std::cout << "YES\n";

    std::vector<int> dynasty = g.GetDynasty();
    std::vector<int> answer;

    int copy = last;

    last = dynasty[last];
    answer.push_back(last + 1);

    while (copy != last) {
      last = dynasty[last];
      answer.push_back(last + 1);
    }

    for (int i = (answer.size()) - 1; i >= 0; --i) {
      std::cout << answer[i] << " ";
    }
  }

  return 0;
}