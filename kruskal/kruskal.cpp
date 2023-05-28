#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_set>
#include <algorithm>

class CDS {
 private:
  std::vector<int> p_;
  std::vector<int> rank_;

 public:
  explicit CDS(int n) {
    rank_ = std::vector<int>(n, 0);
    p_ = std::vector<int>(n);
    for (int i = 0; i < n; ++i) {
      p_[i] = i;
    }
  }

  int FindSet(int x) {
    if (x == p_[x]) {
      return x;
    }
    return p_[x] = FindSet(p_[x]);
  }

  void Union(int x, int y) {
    x = FindSet(x);
    y = FindSet(y);

    if (rank_[x] < rank_[y]) {
      p_[x] = y;
    } else if (rank_[x] > rank_[y]) {
      p_[y] = x;
    } else {
      p_[x] = y;
      rank_[y] += 1;
    }
  }
};

struct Edge {
  double weight;
  int first;
  int second;

  bool operator<(const Edge& other) const {
    return weight < other.weight;
  }
};

class Graph {
 private:
  std::vector<Edge> edges_;
  std::vector<Edge> mst_;
  int n_;
  int result_ = 0;

 public:
  explicit Graph(int nv) {
    edges_ = std::vector<Edge>(nv);
    mst_ = std::vector<Edge>(nv);
    this->n_ = nv;
    result_ = 0;
  }

  friend std::istream& operator>>(std::istream& is, Graph& g);

  void FindMST() {
    CDS cds(n_);

    for (auto edge : edges_) {
      if (cds.FindSet(edge.first) != cds.FindSet(edge.second)) {
        mst_.push_back(edge);
        cds.Union(edge.first, edge.second);
        result_ += edge.weight;
      }
    }
  }

  int Answer() {
    return result_;
  }
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int u, v, w;
  is >> u >> v >> w;
  --u;
  --v;

  Edge e;
  e.weight = w;
  e.first = u;
  e.second = v;
  g.edges_.push_back(e);
  return is;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  Graph g(n);

  for (int i = 0; i < m; ++i) {
    std::cin >> g;
  }

  g.FindMST();
  int ans = g.Answer();

  std::cout << ans;
  return 0;
}