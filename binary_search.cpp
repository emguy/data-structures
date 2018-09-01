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
 *     File Name : binary_search.cpp
 * Last Modified : Fri 31 Aug 2018 11:02:00 PM EDT
 */

#include <iostream>
#include <vector>

using namespace std;

int bin_search(vector<int>& arr, int l, int r, int target) {
  if (l > r || r >= arr.size() || l < 0) {
    return -1;
  }

  while (l != r) {
    int mid = l + (r - l) / 2;
    if (target > arr[mid]) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }

  if (arr[l] == target) {
    return l;
  }
  return l;
}

int bin_search_leftmost(vector<int>& arr, int l, int r, int target) {
  if (l > r || r >= arr.size() || l < 0) {
    return -1;
  }

  if (target == arr[l]) {
    return l;
  }

  while (l < r - 1) {
    int mid = l + (r - l) / 2;
    if (target > arr[mid]) {
      l = mid;
    } else {
      r = mid;
    }
  }

  if (arr[r] == target) {
    return r;
  }
  return -1;
}

int bin_search_rightmost(vector<int>& arr, int l, int r, int target) {
  if (l > r || r >= arr.size() || l < 0) {
    return -1;
  }

  if (target == arr[r]) {
    return r;
  }

  while (l < r - 1) {
    int mid = l + (r - l) / 2;
    if (target >= arr[mid]) {
      l = mid;
    } else {
      r = mid;
    }
  }

  if (arr[l] == target) {
    return l;
  }
  return -1;
}

int main() {
  vector<int> v0 = { 0, 0, 1, 2, 4, 4, 5, 7, 7, 7, 7, 7, 9, 9, 11, 11, 16, 16};
  cout << bin_search_leftmost(v0, 0, v0.size() - 1, 6);
  cout << bin_search_rightmost(v0, 0, v0.size() - 1, 6);
}
