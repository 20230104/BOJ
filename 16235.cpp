#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

class s
{
private:
    int N, M, K, T;
    vector<vector<int>> DLT, FOD;
    vector<vector<priority_queue<pair<int, int>>>> GRD;

    const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    bool isValid(int x, int y)
    {
        if (0 <= x && x < N && 0 <= y && y < N)
            return true;
        return false;
    }

public:
    s()
    {
        scanf("%d %d %d", &N, &M, &K);
        T = 0;
        DLT.assign(N, vector<int>(N));
        FOD.assign(N, vector<int>(N, 5));
        GRD.assign(N, vector<priority_queue<pair<int, int>>>(N));
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                scanf("%d", &DLT[i][j]);
            }
        }
        for (int i = 0; i < M; i++)
        {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            GRD[x - 1][y - 1].push({1, -z});
        }
    }

    void routine()
    {
        vector<pair<int, int>> baby;
        for (int i = 0; i < N; i++) // spring and summer
        {
            for (int j = 0; j < N; j++)
            {
                auto &pq = GRD[i][j];
                auto &food = FOD[i][j];
                int n = pq.size();
                while (n--)
                {
                    int f = -pq.top().second;
                    pq.pop();
                    if (f <= food)
                    {
                        if (f % 5 == 4)
                        {
                            baby.push_back({i, j});
                        }
                        food -= f;
                        pq.push({-T, -f-1});
                    }
                    else
                    {
                        food += f / 2;
                        while (n--)
                        {
                            auto f = -pq.top().second;
                            pq.pop();
                            food += f / 2;
                        }
                        n = 0;
                    }
                }
            }
        } // summer over

        for (auto b : baby) // autumn
        {
            for (int d = 0; d < 8; d++)
            {
                int nx = b.first + dx[d], ny = b.second + dy[d];
                if (isValid(nx, ny))
                {
                    GRD[nx][ny].push({-T, -1});
                }
            }
        } // autumn over
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                FOD[i][j] += DLT[i][j];
            }
        }
    }

    void ution()
    {
        for (; T < K; T++)
        {
            routine();
            //printf("DAY%d\n", T + 1);
            //show();
        }
        int ret = 0;
        for (auto G : GRD)
        {
            for (auto pq : G)
            {
                ret += pq.size();
            }
        }
        printf("%d\n", ret);
    }

    void show()
    {
        // printf("delta\n");
        // for (auto d : DLT)
        // {
        //     for (auto i : d)
        //     {
        //         printf("%d ", i);
        //     }
        //     printf("\n");
        // }
        // printf("\n");

        printf("-----food-----\n");
        for (auto F : FOD)
        {
            for (auto i : F)
            {
                printf("%d ", i);
            }
            printf("\n");
        }
        printf("\n");

        printf("-----youngest tree-----\n");
        for (auto G : GRD)
        {
            for (auto pq : G)
            {
                printf("%3d ", pq.empty() ? 0 : -pq.top().second);
            }
            printf("\n");
        }
        printf("\n");
    }
};

int main()
{
    //freopen("05.txt", "r", stdin);

    s sol;
    sol.ution();

    return 0;
}