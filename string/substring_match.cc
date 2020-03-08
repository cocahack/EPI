#include <string>

#include "test_framework/generic_test.h"
using std::string;

inline unsigned long long charToInt(const char c) {
  return c - 'A';
}

unsigned long long getHash (const string& s) {
  unsigned long long hash = 0;
  for (char c : s) {
    hash = (hash * 10) + charToInt(c);
  }
  return hash;
}

// Returns the index of the first character of the substring if found, -1
// otherwise.
int RabinKarp(const string &t, const string &s) {
  unsigned long long targetHash = getHash(s);
  int len = s.size();
  unsigned long long maxBase = pow(10, len - 1);
  unsigned long long subStrHash = getHash(string(t.begin(), t.begin() + len));

  if(targetHash == subStrHash) {
    return 0;
  }

  for(int i = 1; i < (int)(t.size() - len + 1); ++i) {
    subStrHash -= maxBase * charToInt(t[i-1]);
    subStrHash *= 10;
    subStrHash += charToInt(t[i + len - 1]);
    if(targetHash == subStrHash) {
      return i;
    }
  }

  return -1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"t", "s"};

  return GenericTestMain(args, "substring_match.cc", "substring_match.tsv",
                         &RabinKarp, DefaultComparator{}, param_names);
}

