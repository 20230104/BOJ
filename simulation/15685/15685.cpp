#include <cstdio>
#include <vector>

#define SZ 102

using namespace std;

class s
{
private:
    int N;
    const int NXT[4] = {1, 2, 3, 0};
    const int dx[4] = {0, -1, 0, 1};
    const int dy[4] = {1, 0, -1, 0};
    vector<vector<bool>> MAP;

    void makeDragonCurve(vector<vector<bool>> &v, int x, int y, int d, int g)
    {
        vector<int> cmd;
        cmd.push_back(d);
        while (g--)
        {
            int size = cmd.size();
            while (size--)
            {
                cmd.push_back(NXT[cmd[size]]);
            }
        }

        v[x][y] = true;
        for (auto c : cmd)
        {
            x += dx[c], y += dy[c];
            v[x][y] = true;
        }
    }

public:
    s()
    {
        scanf("%d", &N);
        MAP.assign(SZ, vector<bool>(SZ, false));
    }

    void show(){
        for(int i = 0 ; i<SZ;i++){
            for(int j = 0 ; j<SZ;j++){
                printf("%d ", MAP[i][j]?1:0);

            }
            printf("\n");
        }
    }

    void ution()
    {
        for (int t = 0; t < N; t++)
        {
            vector<vector<bool>> v(SZ, vector<bool>(SZ, false));
            int x, y, d, g;
            scanf("%d %d %d %d", &x, &y, &d, &g);
            makeDragonCurve(v, y, x, d, g);
            for (int i = 0; i < SZ; i++)
            {
                for (int j = 0; j < SZ; j++)
                {
                    if (v[i][j])
                        MAP[i][j] = true;
                }
            }
        }
        int ret = 0;
        for (int i = 1; i < SZ; i++)
        {
            for (int j = 1; j < SZ; j++)
            {
                if (MAP[i][j] && MAP[i - 1][j] && MAP[i][j - 1] && MAP[i - 1][j - 1])
                    ret++;
            }
        }
        printf("%d\n", ret);
    }
};

int main()
{
    s sol;
    sol.ution();

    return 0;
}