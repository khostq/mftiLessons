#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_set>
#include <algorithm>

class Graph {
 private:
  std::vector<std::vector<int>> vertexes_;
  size_t v_;

 public:
  explicit Graph(int n) {
    vertexes_.resize(n, std::vector<int>(n));
    v_ = n;
  }

  void Weight() {  // Заполнение матрицы
    for (size_t i = 0; i < v_; ++i) {
      for (size_t j = 0; j < v_; ++j) {
        std::cin >> vertexes_[i][j];
      }
    }
  }

  void See() {  // Вывод матрицы
    for (size_t x = 0; x < v_; ++x) {
      for (size_t y = 0; y < v_; ++y) {
        std::cout << vertexes_[x][y] << " ";
      }
      std::cout << '\n';
    }
  }

  void FloydWarshall() {  // Алг
    for (size_t k = 0; k < v_; ++k) {
      for (size_t x = 0; x < v_; ++x) {
        for (size_t y = 0; y < v_; ++y) {
          vertexes_[x][y] = std::min(vertexes_[x][y], vertexes_[x][k] + vertexes_[k][y]);
        }
      }
    }
  }
};

int main() {
  int n;
  std::cin >> n;
  Graph g(n);
  g.Weight();
  g.FloydWarshall();
  g.See();
  return 0;
}