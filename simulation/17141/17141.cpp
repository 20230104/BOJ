#include <algorithm>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>

#define INF 987654321

using namespace std;

class s {
    typedef struct {
        int r, c;
        int l;
    } NODE;

   private:
    int N, M, V_SIZE;
    const int dc[4] = {0, 0, 1, -1};
    const int dr[4] = {1, -1, 0, 0};
    vector<vector<int>> LAB;  // 0:space 1:wall 2:virusable
    vector<pair<int, int>> VIRUS;
    vector<vector<vector<int>>> DIST;

    bool isValid(int r, int c) {
        if (0 <= r && r < N && 0 <= c && c < N) return true;
        return false;
    }

    int getMinDist(const vector<int> &v) {
        int ret = 0;
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (LAB[r][c] == 1) continue;
                int mn = INF;
                for (auto i : v) {
                    mn = min(mn, DIST[i][r][c]);
                }
                if (mn == INF) return INF;
                ret = max(ret, mn);
            }
        }
        return ret;
    }

    void makeDistanceTable() {
        for (int i = 0; i < V_SIZE; i++) {
            vector<vector<int>> v(LAB);
            queue<NODE> q;
            NODE f;
            f.r = VIRUS[i].first, f.c = VIRUS[i].second;
            f.l = 0;
            q.push({f});
            v[f.r][f.c] = 1;
            DIST[i][f.r][f.c] = 0;
            while (!q.empty()) {
                f = q.front();
                q.pop();
                for (int d = 0; d < 4; d++) {
                    NODE n;
                    int nc = f.c + dc[d], nr = f.r + dr[d], nl = f.l + 1;
                    if (isValid(nc, nr) && v[nr][nc] == 0) {
                        n.r = nr, n.c = nc, n.l = nl;
                        q.push(n);
                        v[nr][nc] = 1;
                        DIST[i][nr][nc] = nl;
                    }
                }
            }
        }
    }

   public:
    s() {
        scanf("%d %d", &N, &M);
        LAB.assign(N, vector<int>(N));
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                scanf("%d", &LAB[r][c]);
                if (LAB[r][c] == 2) VIRUS.push_back({r, c});
            }
        }
        V_SIZE = (int)VIRUS.size();
        for (auto V : VIRUS) {
            LAB[V.first][V.second] = 0;
        }
        DIST.assign(V_SIZE, vector<vector<int>>(N, vector<int>(N, INF)));
    }

    void ution() {
        makeDistanceTable();
        int comb[11] = {
            0,
        };
        for (int i = 0; i < M; i++) comb[i] = 1;
        int result = INF;
        do {
            vector<int> c;
            for (int i = 0; i < V_SIZE; i++) {
                if (comb[i]) c.push_back(i);
            }
            result = min(result, getMinDist(c));
        } while (prev_permutation(comb, comb + V_SIZE));
        printf("%d", result == INF ? -1 : result);
    }

    void show() {
        printf("LAB\n");
        for (auto L : LAB) {
            for (auto i : L) printf("%d ", i);
            printf("\n");
        }
        printf("DIST\n");
        int k = 1;
        printf("%d, %d\n", VIRUS[k].first, VIRUS[k].second);
        for (auto D : DIST[k]) {
            for (auto i : D) printf("%10d ", i);
            printf("\n");
        }
    }
};

int main() {
    s sol;
    sol.ution();
    // sol.show();
    return 0;
}
