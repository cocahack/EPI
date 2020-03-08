#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;


void setPartialMatch(vector<int>& lps, const string& p) {
  lps = vector<int>(p.size(), 0);
  int len = p.size(), begin = 1, matched = 0;

  while (begin + matched < len) {
    if(p[begin + matched] == p[matched]) {
      matched++;
      lps[begin+matched-1] = matched;
    } else {
      if (matched == 0) {
        begin++;
      } else {
        begin += matched - lps[matched - 1];
        matched = lps[matched-1];
      }
    }
  }
}

// Returns the index of the first character of the substring if found, -1
// otherwise.
int KMP(const string &t, const string &s) {
  if(s.empty()) {
    return 0;
  }
  vector<int> lps;
  setPartialMatch(lps, s);

  int matched = 0, begin = 0, T = t.size(), S = s.size();

  while(begin <= T - S) {
    if(matched < S && t[begin+matched] == s[matched]) {
      matched++;
      if(matched == S) {
        return begin;
      }
    } else {
      if (matched == 0) {
        begin++;
      } else {
        begin += matched - lps[matched - 1];
        matched = lps[matched - 1];
      }
    }
  }

  return -1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"t", "s"};

  return GenericTestMain(args, "substring_match.cc", "substring_match.tsv",
                         &KMP, DefaultComparator{}, param_names);
}

