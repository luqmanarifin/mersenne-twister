#ifndef __MARSENNE_H
#define __MARSENNE_H

using namespace std;

#define int unsigned

struct mersenne_twister {
  mersenne_twister() {
    srand(time(NULL));
    seed_mt(rand());
  }
  mersenne_twister(int seed) {
    seed_mt(seed);
  }
  void seed_mt(int seed) {
    id = n;
    MT[0] = seed;
    for(int i = 1; i < n; i++) {
      MT[i] = (lowest_w & (f * (MT[i-1] xor (MT[i-1] >> (w-2))) + i));
    }
  }
  int get_num() {
    if(id >= n) {
      twist();
    }
    int y = MT[id];
    y ^= ((y >> u) and d);
    y ^= ((y << s) and b);
    y ^= ((y << t) and c);
    y ^= (y >> l);
    id++;
    return lowest_w & y;
  }
  void twist() {
    for(int i = 0; i < n; i++) {
      int c = (MT[i] and upper_mask) + (MT[(i+1) % n] and lower_mask);
      int cA = (c >> 1);
      if(c % 2 != 0) {
        cA ^= a;
      }
      MT[i] = (MT[(i + m) % n] ^ cA);
    }
    id = 0;
  }

  static const int w, n = 624, m, r;
  static const int a;
  static const int u, d;
  static const int s, b;
  static const int t, c;
  static const int l;
  static const int f;
  
  static const int lowest_w;
  static const int lower_mask;
  static const int upper_mask;
  
  int MT[n];
  int id = n + 1;
};

const int mersenne_twister::w = 32;
const int mersenne_twister::m = 397;
const int mersenne_twister::r = 31;
const int mersenne_twister::a = 0x9908B0DF;
const int mersenne_twister::u = 11;
const int mersenne_twister::d = 0xFFFFFFFF;
const int mersenne_twister::s = 7;
const int mersenne_twister::b = 0x9D2C5680;
const int mersenne_twister::t = 15;
const int mersenne_twister::c = 0xEFC60000;
const int mersenne_twister::l = 18;
const int mersenne_twister::f = 0x6C078965;

const int mersenne_twister::lowest_w = (w == 32? -1 : (1 << w) - 1);
const int mersenne_twister::lower_mask = (1 << r) - 1;
const int mersenne_twister::upper_mask = ((~lower_mask) & lowest_w);


#endif