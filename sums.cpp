#include "twister.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6;

double a[N + 5];
double s[N + 5];

vector<double> all[105];

int main() {
  srand(time(0));
  for(int i = 1; i <= N; i++) {
    a[i] = randd_cc();
    s[i] = s[i - 1] + a[i];
  }
  for(int i = 100; i <= N; i++) {
    double add = s[i] - s[i - 100];
    all[(int) add].push_back(add);
  }
  puts("add");
  for(int i = 0; i <= 100; i++) {
    if(all[i].size()) printf("%d\n", i);
  }
  puts("kemunculan");
  for(int i = 0; i <= 100; i++) {
    if(all[i].size()) printf("%d\n", all[i].size());
  }
  return 0;
}