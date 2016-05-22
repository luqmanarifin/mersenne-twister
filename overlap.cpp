#include "twister.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6;

vector<int> p[120];
int cnt[120], all;

void insert(vector<int> a) {
  vector<pair<int, int>> num;
  for(int i = 0; i < a.size(); i++) num.emplace_back(a[i], i);
  sort(num.begin(), num.end());
  for(int i = 0; i + 1 < num.size(); i++) {
    if(num[i].first == num[i + 1].first) return;
  }
  vector<int> id;
  for(auto it : num) id.push_back(it.second);
  for(int i = 0; i < all; i++) {
    bool same = 1;
    for(int j = 0; j < p[i].size(); j++) {
      if(p[i][j] != id[j]) {
        same = 0;
        break;
      }
    }
    if(same) {
      cnt[i]++;
      break;
    }
  }
}

int main() {
  vector<int> r = {0, 1, 2, 3, 4};
  do {
    p[all++] = r;
  } while(next_permutation(r.begin(), r.end()));
  assert(all == 120);
  
  int* a = new int[N];
  srand(time(NULL));
  for(int i = 0; i < N; i++) {
    a[i] = rand();
  }
  for(int i = 0; i + 5 < N; i += 5) {
    vector<int> num;
    for(int j = 0; j < 5; j++) {
      num.push_back(a[i + j]);
    }
    insert(num);
  }
  for(int i = 0; i < all; i++) {
    printf("%d\n", cnt[i]);
  }
  return 0;
}