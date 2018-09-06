/* NOTE: This program is free software; you can redistribute it 
 * and/or modify it under the terms of the GNU General Public 
 * License as published by the Free Software Foundation; either 
 * version 3, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * Bugs can be reported to Yu Zhang <emguy2000@gmail.com>.
 *
 *     File Name : permutation.cpp
 * Last Modified : Thu Sep  6 09:42:34 2018
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

void print_result(vector<string> result) {
  for (string& s: result) {
    cout << s << endl;
  }
}

inline void swap(char& a, char& b) {
  char tmp = a;
  a = b;
  b = tmp;
}

void fill_subset(string& cur, unordered_set<char>& set, const string& s, vector<string>& result) {
  result.push_back(cur); 
  cur.resize(cur.size() + 1);
  for (int i = 0; i < s.size(); ++i) {
    if (set.find(s[i]) != set.end()) {
      continue;
    }
    cur[cur.size() - 1] = s[i];
    set.insert(s[i]);
    fill_subset(cur, set, s, result);
    set.erase(s[i]);
  }
  cur.resize(cur.size() - 1);
}

void fill_permutation(string& cur, int index, vector<string>& result) {
  if (index == cur.size() - 1) {
    result.push_back(cur);
  }
  for (int i = index; i < cur.size(); ++i) {
    swap(cur[index], cur[i]);
    fill_permutation(cur, index + 1, result);
    swap(cur[index], cur[i]);
  }
}

int main(int argc, char **argv) {
  if (argc == 1) {
    cout << "ERROR: no arguments." << endl;
    exit(0);
  }

  vector<string> result;

  string s(argv[1]);
  string cur;
  unordered_set<char> set;
  cout << "input:" << endl;
  cout << s << endl;
  fill_subset(cur, set, s, result);
  cout << "subsets: (" << result.size() << ")" << endl;
  print_result(result);

  result.clear();
  cur = s;
  fill_permutation(cur, 0, result);
  cout << "permulations: (" << result.size() << ")" << endl;
  print_result(result);
}
