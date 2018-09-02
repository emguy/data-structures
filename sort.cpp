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
 *     File Name : sort.cpp
 * Last Modified : Sat 01 Sep 2018 11:12:50 PM EDT
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

void print_vector(vector<int>& arr) {
  for (int i = 0; i < arr.size(); ++i) {
    cout << arr[i] << " ";
  }
  cout <<"]" << endl;
}

void merge_arr(vector<int>& arr, int left, int mid, int right, vector<int>& arr2) {
  for (int i = left; i <= right; ++i) {
    arr2[i] = arr[i];
  }
  int p1 = left;
  int p2 = mid + 1;
  for (int i = left; i <= right; ++i) {
    if (p1 > mid) {
      arr[i] = arr2[p2++];
    } else if (p2 > right) {
      arr[i] = arr2[p1++];
    } else if (arr2[p2] < arr2[p1]) {
      arr[i] = arr2[p2++];
    } else {
      arr[i] = arr2[p1++];
    }
  }
}

void merge_sort(vector<int>& arr, int left, int right,  vector<int>& arr2) {
  if (left == right) {
    return;
  }

  int mid = left + (right - left) / 2;
  merge_sort(arr, left, mid, arr2);
  merge_sort(arr, mid + 1, right, arr2);
  merge_arr(arr, left, mid, right, arr2);
}

void merge_sort(vector<int>& arr) {
  vector<int> tmp(arr.size());
  merge_sort(arr, 0, arr.size() - 1,  tmp);
}

void insertion_sort(vector<int>& arr) {
  for (int i = 1; i < arr.size(); ++i) { 
    int j = i;
    while (j > 0 && arr[j] < arr[j - 1]) {
      swap(arr[j], arr[j - 1]);
      --j;
    }
  }
}

void selection_sort(vector<int>& arr) {
  for (int i = 0; i < arr.size() - 1; ++i) {
    int jmin = i;
    for (int j = i + 1; j < arr.size(); ++j) {
      if (arr[j] < arr[jmin]) {
        jmin = j;
      }
    }
    swap(arr[i], arr[jmin]);
  }
}

inline void swap(int& a, int& b) {
  a ^= b;
  b ^= a;
  a ^= b;
}

void fill_rand(vector<int>& arr, int low, int high) {
  if (high < low) {
    return;
  }
  std::srand((unsigned)time(0));
  int range = high - low + 1;
  for (int i = 0; i < arr.size(); ++i) {
    arr[i] = low + rand()%range;
  }
}

int main() {
  vector<int> arr(40);
  fill_rand(arr, 0, 30);
  cout << "original:" << endl;
  print_vector(arr);
  cout << "sorted:" << endl;
  merge_sort(arr);
  print_vector(arr);
}
