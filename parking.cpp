#include "twister.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;

int cnt[N];

double dist(double a, double b, double c, double d) {
  return (a - c)*(a - c) + (b - d)*(b - d);
}

int main() {
  srand(time(0));
  for(int t = 1; t <= 1000; t++) {
    set<pair<double, double>> s;
    int circles = 0;
    for(int i = 0; i < 12000; i++) {
      double a = randd_cc() * 98 + 1;
      double b = randd_cc() * 98 + 1;
      bool ada = 0;
      auto from = s.lower_bound(make_pair(a - 1.00001, -1));
      auto to = s.upper_bound(make_pair(a + 1.00001, -1));
      while(from != to) {
        if(dist(a, b, from->first, from->second) <= 1) {
          ada = 1;
          break;
        }
        from++;
      }
      if(!ada) {
        circles++;
        s.insert(make_pair(a, b));
      }
    }
    cerr << t << " done" << endl;
    cnt[circles]++;
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