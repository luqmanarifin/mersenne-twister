#include "twister.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6;

int cnt[1 << 2];

int main() {
  cout << "biggest rand() " << INT32_MAX << endl;
  srand(time(NULL));
  for(int i = 0; i < N; i++) {
    cnt[rand() % 4]++;
  }
  int sum = 0;
  for(int i = 0; i < (1 << 2); i++) {
    sum += cnt[i];
    cout << cnt[i] << endl;
  }
  assert(sum == N);
  return 0;
}