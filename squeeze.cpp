#include "twister.h"
#include <bits/stdc++.h>

using namespace std;

int cnt[1005];

int main() {
  srand(time(0));
  for(int tt = 1; tt <= 1000000; tt++) {
    double now = (1LL << 31);
    int need = 0;
    while(now > 1) {
      need++;
      double a = randd_oo();
      now *= a;
    }
    cnt[need]++;
    if(tt % 1000 == 0) {
      cerr << tt << " done" << endl;
    }
  }
  puts("BUTUH");
  for(int i = 0; i <= 1005; i++) {
    if(cnt[i]) {
      printf("%d\n", i);
    }
  }
  puts("KEMUNCULAN");
  for(int i = 0; i <= 1005; i++) {
    if(cnt[i]) {
      printf("%d\n", cnt[i]);
    }
  }
  return 0;
}