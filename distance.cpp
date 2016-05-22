#include "twister.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 1e4;
const int mod = N * N;

int dist(int a, int b) {
  int ai = a / N;
  int aj = a % N;
  int bi = b / N;
  int bj = b % N;
  return (ai - bi)*(ai - bi) + (aj - bj)*(aj - bj);
}

int main() {
  srand(time(0));
  vector<int> d;
  int mini = 2e9, maks = -2e9;
  for(int t = 0; t < 100; t++) {
    set<int> done;
    while(done.size() < 8000) {
      done.insert(rand() % mod);
    }
    vector<int> s;
    for(auto it : done) s.push_back(it);
    int best = 2e9;
    for(int i = 0; i < s.size(); i++) {
      for(int j = i + 1; j < s.size(); j++) {
        best = min(best, dist(s[i], s[j]));
      }
    }
    mini = min(mini, best);
    maks = max(maks, best);
    d.push_back(best);
    cerr << "done compute " << t << endl;
  }
  printf("mini: %d, maks: %d\n", mini, maks);
  sort(d.begin(), d.end());
  for(int i = 0; i < d.size(); i++) {
    int j = i;
    while(i + 1 < d.size() && d[i + 1] == d[i]) i++;
    printf("%d ada %d\n", d[i], i - j + 1);
  }
  return 0;
}