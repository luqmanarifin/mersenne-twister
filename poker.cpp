#include "twister.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6;

int cnt[1 << 5];

int main() {
  cout << "biggest rand() " << INT32_MAX << endl;
  srand(time(NULL));
  for(int i = 0; i < N; i++) {
    cnt[rand() % (1 << 5)]++;
  }
  int sum = 0;
  for(int i = 0; i < (1 << 5); i++) {
    sum += cnt[i];
    cout << cnt[i] << endl;
  }
  for(int i = 0; i < (1 << 5); i++) {
    printf("\'");
    for(int j = 4; j >= 0; j--) {
      if(i & (1 << j)) {
        printf("1");
      }else {
        printf("0");
      }
    }
    printf("\n");
  }
  assert(sum == N);
  return 0;
}