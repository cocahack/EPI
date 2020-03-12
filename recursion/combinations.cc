#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void CombinationsHelper(vector<vector<int>>& answer, vector<int>& container, int start, int idx, int n, int k) {
  if(idx == k) {
    answer.push_back(container);
    return;
  }

  for(int i=start; i<=n; ++i) {
    container[idx] = i;
    CombinationsHelper(answer, container, i+1, idx+1, n, k);
  }
}

vector<vector<int>> Combinations(int n, int k) {
  vector<vector<int>> answer;
  vector<int> container(k, 0);

  CombinationsHelper(answer, container, 1, 0, n, k);

  return answer;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "k"};
  return GenericTestMain(args, "combinations.cc", "combinations.tsv",
                         &Combinations, UnorderedComparator{}, param_names);
}

