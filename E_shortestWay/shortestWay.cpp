#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_set>

class Graph {
 private:
  std::vector<std::unordered_set<int>> vertexes_;
  std::vector<int> dist_;
  std::vector<int> parents_;
  std::vector<int> way_;

 public:
  explicit Graph(int nv) {
    vertexes_ = std::vector<std::unordered_set<int>>(nv);
    dist_ = std::vector<int>(nv, std::numeric_limits<int>::max());
    parents_ = std::vector<int>(nv, -1);
    way_ = std::vector<int>(nv);
  }

  friend std::istream& operator>>(std::istream& is, Graph& g);

  int BFS(int start, int end) {
    --start;
    --end;
    std::queue<int> queue;
    queue.push(start);
    dist_[start] = 0;
    way_[start] = -1;  // нет предыдущих

    while (!queue.empty()) {
      int curr = queue.front();
      queue.pop();
      for (auto neighbour : vertexes_[curr]) {
        if ((dist_[neighbour] >= dist_[curr] + 1)) {
          dist_[neighbour] = dist_[curr] + 1;
          parents_[neighbour] = curr;
          queue.push(neighbour);
          way_[neighbour] = curr;
        }
      }
    }
    return dist_[end];
  }

  std::vector<int> GetWay() {
    return way_;
  }
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
  int n, m, a, b;
  std::cin >> n >> m >> a >> b;

  Graph g(n);

  for (int i = 0; i < m; ++i) {
    std::cin >> g;
  }

  int answer = g.BFS(a, b);

  if (answer == std::numeric_limits<int>::max()) {
    std::cout << -1;
  } else {
    std::cout << answer << "\n";

    std::vector<int> ans_mas;
    std::vector<int> way = g.GetWay();

    int curr = b - 1;  // текущая вершина пути
    while (way[curr] != -1) {
      ans_mas.push_back(curr + 1);
      curr = way[curr];
    }
    ans_mas.push_back(curr + 1);

    for (int i = int(ans_mas.size()) - 1; i >= 0; --i) {
      std::cout << ans_mas[i] << " ";
    }
  }
  return 0;
}