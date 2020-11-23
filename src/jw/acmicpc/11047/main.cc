#include <iostream>
#include <vector>
#include <memory>


unsigned int N, K;
std::unique_ptr<std::vector<unsigned int>> coins;

int main() {
  std::cin >> N;
  std::cin >> K;

  coins = std::make_unique<std::vector<unsigned int>>(N); 

  for (int i = 0 ; i < N ; i++)
    std::cin >> (*coins)[i];

  return 0;
}
