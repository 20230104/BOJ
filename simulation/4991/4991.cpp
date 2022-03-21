#include <cstdio>
#include <vector>
#include <utility>
#include <queue>

#define INF 98765432
#define WALL 88888888

using namespace std;

class s
{
private:
    int R, C, DS, VISIT[13] = {
                      0,
    };
    int MN = INF;
    vector<vector<int>> ROOM, COST;
    vector<pair<int, int>> DIRTY;
    pair<int, int> START;

    const int DR[4] = {0, 0, 1, -1};
    const int DC[4] = {1, -1, 0, 0};

    bool isVlaid(int r, int c) { return 0 <= r && r < R && 0 <= c && c < C; }
    int min(int x, int y) { return x > y ? y : x; }

public:
    s(int _r, int _c)
    {
        R = _r, C = _c;
        getchar();
        ROOM.assign(R, vector<int>(C, INF));
        for (int r = 0; r < R; r++)
        {
            for (int c = 0; c < C; c++)
            {
                char buff;
                buff = getchar();
                if (buff == 'o')
                    START = {r, c};
                else if (buff == 'x')
                    ROOM[r][c] = WALL;
                else if (buff == '*')
                    DIRTY.push_back({r, c});
            }
            getchar();
        }
        DIRTY.insert(DIRTY.begin(), START);
        DS = DIRTY.size() - 1;
    }

    void DFS(int level, int sum, int node)
    {
        if(sum>MN) return;
        if (level == DS)
        {
            MN = min(MN, sum);
            return;
        }

        for (int i = 1; i <= DS; i++)
        {
            if (!VISIT[i])
            {
                VISIT[i] = 1;
                DFS(level + 1, sum + COST[node][i], i);
                VISIT[i] = 0;
            }
        }
    }

    void makeCostTable()
    {
        COST.assign(DIRTY.size(), vector<int>(DIRTY.size(), INF));
        for (int from = 0; from < DIRTY.size(); from++)
        {
            auto d = DIRTY[from];
            queue<pair<int, int>> q;
            q.push(d);
            vector<vector<int>> room(ROOM);
            room[d.first][d.second] = 0;

            while (!q.empty())
            {
                auto f = q.front();
                int t = room[f.first][f.second];
                q.pop();
                for (int d = 0; d < 4; d++)
                {
                    int nr = f.first + DR[d], nc = f.second + DC[d];
                    if (isVlaid(nr, nc) && room[nr][nc] == INF)
                    {
                        q.push({nr, nc});
                        room[nr][nc] = t + 1;
                    }
                }
            }
            room[d.first][d.second] = 0;

            for (int to = 0; to < DIRTY.size(); to++)
            {
                COST[from][to] = room[DIRTY[to].first][DIRTY[to].second];
            }

            //    printf("FROM %d, %d\n", d.first, d.second);
            //     for(auto r:room){
            //         for(auto i:r)printf("%2d ", i==WALL?-1:i);
            //         printf("\n");
            //     }
        }
    }

    void ution()
    {
        makeCostTable();
        MN = heuristic1();
        DFS(0, 0, 0);
        printf("%d\n", MN == INF ? -1 : MN);
    }

    int heuristic1(){
        int from = 0, to;
        int ret = 0;
        int visit[13] = {0, };
        for(int i =1;i<=DS;i++){
            int mn = INF;
            for(int j = 1;j<=DS;j++){
                if(visit[j]) continue;
                if(mn>COST[from][j]){
                    to = j;
                    mn = COST[from][j];
                }
            }
            visit[to] = 1;
            ret+=mn;
            from = to;
        }
        return ret>INF?INF:ret;
    }

    void show()
    {
        printf("=====ROOM=====\n");
        for (auto r : ROOM)
        {
            for (auto i : r)
                printf("%3d ", i == WALL ? -1 : 0);
            printf("\n");
        }

        printf("d\n");
        for (auto i : DIRTY)
            printf("%d, %d\n", i.first, i.second);

        printf("COST\n");
        for (auto c : COST)
        {
            for (auto i : c)
            {
                if (i == INF)
                    printf("INF ");
                else
                    printf("%3d ", i);
            }
            printf("\n");
        }
    }
};

int main()
{
    freopen("01.txt", "r", stdin);
    int r, c;
    scanf("%d %d", &c, &r);
    while (r || c)
    {
        s sol(r, c);
        sol.ution();
        scanf("%d %d", &c, &r);
    }

    return 0;
}