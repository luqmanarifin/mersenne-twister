#include "twister.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

int cnt[N];
bool done[105][105];

int main() {
  srand(time(0));
  for(int t = 1; t <= 10; t++) {
    vector<pair<int, int>> s;
    for(int i = 0; i < 12000; i++) {
      int a = rand() % 100;
      int b = rand() % 100;
      if(!done[a][b]) {
        s.push_back(make_pair(a, b));
        done[a][b] = 1;
      }
    }
    cerr << t << " done" << endl;
    cnt[s.size()]++;
    for(auto it : s) done[it.first][it.second] = 0;
  }
  puts("JUMLAH CIRCLES");
  for(int i = 0; i < N; i++) {
    if(cnt[i]) {
      printf("%d\n", i);
    }
  }
  puts("KEMUNCULAN");
  for(int i = 0; i < N; i++) {
    if(cnt[i]) {
      printf("%d\n", cnt[i]);
    }
  }
  return 0;
}