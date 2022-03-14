#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>

using namespace std;

class s {
   private:
    vector<vector<int>> A;
    int R_MAX = 3, C_MAX = 3;
    int R, C, K;

    void calR() {
        int new_R_MAX = 0;
        for (int i = 0; i < C_MAX; i++) {
            sort(A[i].begin(), A[i].begin() + R_MAX);
            vector<pair<int, int>> v;
            int idx = upper_bound(A[i].begin(), A[i].begin() + R_MAX, 0) - A[i].begin();
            while (idx < R_MAX) {
                int next = upper_bound(A[i].begin() + idx, A[i].begin() + R_MAX, A[i][idx]) - A[i].begin();
                v.push_back({next - idx, A[i][idx]});
                idx = next;
            }
            int cur_R = min((int)v.size() * 2, 100);
            sort(v.begin(), v.end());
            for (int j = 0; j < cur_R; j += 2) {
                A[i][j] = v[j / 2].second, A[i][j + 1] = v[j / 2].first;
            }
            for (int j = cur_R; j < R_MAX; j++) A[i][j] = 0;
            new_R_MAX = max(new_R_MAX, cur_R);
        }
        R_MAX = new_R_MAX;
    }

    void calC() {
        int new_C_MAX = 0;
        for (int j = 0; j < R_MAX; j++) {
            vector<int> B;
            vector<pair<int, int>> v;
            B.reserve(C_MAX);
            for (int i = 0; i < C_MAX; i++) B.push_back(A[i][j]);
            sort(B.begin(), B.end());
            int idx = upper_bound(B.begin(), B.end(), 0) - B.begin();
            while (idx < C_MAX) {
                int next = upper_bound(B.begin() + idx, B.end(), B[idx]) - B.begin();
                v.push_back({next - idx, B[idx]});
                idx = next;
            }
            int cur_C = min((int)v.size() * 2, 100);
            sort(v.begin(), v.end());
            for (int i = 0; i < cur_C; i += 2) {
                A[i][j] = v[i / 2].second, A[i + 1][j] = v[i / 2].first;
            }
            for (int i = cur_C; i < C_MAX; i++) A[i][j] = 0;
            new_C_MAX = max(new_C_MAX, cur_C);
        }
        C_MAX = new_C_MAX;
    }

   public:
    s() {
        A.assign(100, vector<int>(100, 0));
        scanf("%d %d %d", &R, &C, &K);
        R--, C--;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                scanf("%d", &A[i][j]);
            }
        }
    }

    void show() {
        for (int i = 0; i < C_MAX; i++) {
            for (int j = 0; j < R_MAX; j++) {
                printf("%d ", A[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    void ution() {
        for (int i = 0; i <= 100; i++) {
            // show();
            if (A[R][C] == K) {
                printf("%d", i);
                return;
            }
            if (R_MAX <= C_MAX)
                calR();
            else
                calC();
        }
        printf("-1");
    }
};

int main() {
    s sol;
    sol.ution();
    return 0;
}
