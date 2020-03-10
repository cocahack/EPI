#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

string keypad[10] = {"0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"};

void PhoneMnemonicHelper(vector<string>& ans, const string& phone_number, string& s, int idx) {
  if(idx == phone_number.size()) {
    ans.push_back(s);
    return;
  }

  int key = phone_number[idx] - '0';
  for (char c : keypad[key]) {
    s[idx] = c;
    PhoneMnemonicHelper(ans, phone_number, s, idx + 1);
  }

}

vector<string> PhoneMnemonic(const string& phone_number) {
  vector<string> answer;
  string s;
  for(int i=0; i<phone_number.size(); ++i) s += 'a';

  PhoneMnemonicHelper(answer, phone_number, s, 0);

  return answer;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"phone_number"};
  return GenericTestMain(args, "phone_number_mnemonic.cc",
                         "phone_number_mnemonic.tsv", &PhoneMnemonic,
                         UnorderedComparator{}, param_names);
}

