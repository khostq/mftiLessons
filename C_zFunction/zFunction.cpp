#include <iostream>
#include <vector>
#include <string>

std::vector<int> ZFunction(std::string& str) {
  std::vector<int> z(str.size(), 0);
  z[0] = str.size();
  int r = 0, l = 0;
  for (int i = 1; i < static_cast<int>(str.size()); ++i) {
    if (i <= r) {
      z[i] = std::min(z[i - l], (r - i));
    }

    while (i + z[i] < static_cast<int>(str.size()) && str[z[i]] == str[i + z[i]]) {
      ++z[i];
    }

    if (r < (i + z[i])) {
      r = i + z[i];
      l = i;
    }
  }
  return z;
}

int main() {
  std::string in;
  std::cin >> in;
  for (auto i : ZFunction(in)) {
    std::cout << i << " ";
  }
  return 0;
}