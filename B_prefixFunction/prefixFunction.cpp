#include <iostream>
#include <vector>
#include <string>

std::vector<int> PrefixFunc(std::string& str) {
  std::vector<int> pr(str.size(), 0);
  for (int i = 1; i < int(str.size()); ++i) {
    int k = pr[i - 1];
    while (k > 0 && str[k] != str[i]) {
      k = pr[k - 1];
    }
    if (str[k] == str[i]) {
      pr[i] = k + 1;
    }
  }
  return pr;
}

int main() {
  std::string in;
  std::cin >> in;
  for (auto i : PrefixFunc(in)) {
    std::cout << i << " ";
  }
  return 0;
}