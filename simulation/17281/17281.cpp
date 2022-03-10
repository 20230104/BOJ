#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class s {
  private:
    int N, M = 0;
    vector<vector<int>> BRD;

  int calScore(int p[9]) {
    int start = 0, ret = 0;
    for (int i = 0; i < N; i++) {
      if (M >= ret + (N - i) * 24) return 0;
      int out = 0, t = start;
      while (out != 3) {
        if (BRD[i][p[t % 9]] == 0) {
          out++;
        }
        t++;
      }
      int cnt = t - start - 3, las = 0;
      int tmp_start = t % 9;
      t--;
      for (int c = 0; c < 3; c++, t--) {
        while (t >= start && BRD[i][p[t % 9]] == 0) {
          t--;
        }
        if (t < start) {
          cnt = 0;
          break;
        }
        las += BRD[i][p[t % 9]];
        if (las >= 4) {
          cnt -= c;
          break;
        }
      }
      if (cnt >= 3 && las == 3) cnt -= 3;
      ret += cnt;
      start = tmp_start;
    }
    return ret;
  }
  public:
    s() {
      scanf("%d", & N);
      BRD.assign(N, vector < int > (9));
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < 9; j++) {
          scanf("%d", & BRD[i][j]);
        }
      }
    }
  void ution() {
    int semi_p[8] = {1,2,3,4,5,6,7,8};
    do {
      int p[9];
      for (int i = 0; i < 3; i++) p[i] = semi_p[i];
      p[3] = 0;
      for (int i = 4; i < 9; i++) p[i] = semi_p[i - 1];
      M = max(M, calScore(p));
    } while (next_permutation(semi_p, semi_p + 8));
    printf("%d", M);
  }
};

int main() {
  s sol;
  sol.ution();
  return 0;
}
