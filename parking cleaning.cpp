#include "twister.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 5000;

string buf;
int a[N], b[N];
int cnt[N];

int main() {
  getline(cin, buf);
  bool lewat = 0;
  int ida = 0, idb = 0;
  while(getline(cin, buf)) {
    int p = atoi(buf.c_str());
    if(p == 0) {
      lewat = 1;
    } else {
      if(lewat) {
        b[idb++] = p;
      } else {
        a[ida++] = p;
      }
    }
  }
  assert(ida == idb);
  for(int i = 0; i < ida; i++) {
    cnt[a[i]] = b[i];
  }
  puts("NILAI");
  for(int i = 3900; i <= 4050; i += 5) {
    int cur = 0;
    for(int j = 0; j < 5; j++) {
      cur += cnt[i + j];
    }
    printf("%d\n", i);
  }
 puts("MUNCUL");
  for(int i = 3900; i <= 4050; i += 5) {
    int cur = 0;
    for(int j = 0; j < 5; j++) {
      cur += cnt[i + j];
    }
    printf("%d\n", cur);
  }
  return 0;
}