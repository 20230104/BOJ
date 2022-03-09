#include <cstdio>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

class s
{
    typedef struct
    {
        pair<int, int> r, b;
        int d, l;
    } factor;

private:
    int N, M;
    pair<int, int> R, B;
    vector<vector<char>> BRD;
    vector<vector<vector<pair<int, int>>>> MOVE;

    bool incline(pair<int, int> &r, pair<int, int> &b, int d)
    {
        pair<int, int> nr = MOVE[r.first][r.second][d];
        pair<int, int> nb = MOVE[b.first][b.second][d];
        if (nr == nb && BRD[nr.first][nr.second] != 'O')
        {
            switch (d)
            {
            case 0:
                if (r.first < b.first)
                    nb.first++;
                else
                    nr.first++;
                break;
            case 1:
                if (r.second < b.second)
                    nr.second--;
                else
                    nb.second--;
                break;
            case 2:
                if (r.first < b.first)
                    nr.first--;
                else
                    nb.first--;
                break;
            case 3:
                if (r.second < b.second)
                    nb.second++;
                else
                    nr.second++;
                break;

            default:
                break;
            }
        }
        r = nr, b = nb;
        if (BRD[nr.first][nr.second] == 'O' || BRD[nb.first][nb.second] == 'O')
            return true;
        else
            return false;
    }

    void makeMoveTable()
    {
        MOVE.assign(N, vector<vector<pair<int, int>>>(M, vector<pair<int, int>>(4)));

        for (int i = 1; i < N - 1; i++)
        {
            for (int j = 1; j < M - 1; j++)
            {
                int y = i, x = j;
                while (BRD[y][j] != '#')
                {
                    if (BRD[y][j] == 'O')
                    {
                        y--;
                        break;
                    }
                    y--;
                }
                y++;
                MOVE[i][j][0] = {y, j};
                y = i;
                while (BRD[y][j] != '#')
                {
                    if (BRD[y][j] == 'O')
                    {
                        y++;
                        break;
                    }
                    y++;
                }
                y--;
                MOVE[i][j][2] = {y, j};

                while (BRD[i][x] != '#')
                {
                    if (BRD[i][x] == 'O')
                    {
                        x--;
                        break;
                    }
                    x--;
                }
                x++;
                MOVE[i][j][3] = {i, x};
                x = j;
                while (BRD[i][x] != '#')
                {
                    if (BRD[i][x] == 'O')
                    {
                        x++;
                        break;
                    }
                    x++;
                }
                x--;
                MOVE[i][j][1] = {i, x};
            }
        }
    }

public:
    s()
    {
        scanf("%d %d", &N, &M);
        getchar();
        BRD.assign(N, vector<char>(M));
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                BRD[i][j] = getchar();
                if (BRD[i][j] == 'B')
                {
                    B.first = i, B.second = j;
                    BRD[i][j] = '.';
                }
                else if (BRD[i][j] == 'R')
                {
                    R.first = i, R.second = j;
                    BRD[i][j] = '.';
                }
            }
            getchar();
        }
    }

    void ution()
    {
        makeMoveTable();
        queue<factor> q;
        factor f;
        f.l = 0, f.r = R, f.b = B, f.d = -1;
        q.push(f);

        while (!q.empty())
        {
            f = q.front();
            q.pop();
            if (f.l == 10)
            {
                printf("-1\n");
                return;
            }

            pair<int, int> nb, nr;
            for (int d = 0; d < 4; d++)
            {
                if(d == f.d) continue;
                nb = f.b, nr = f.r;
                if (incline(nr, nb, d))
                {
                    if (BRD[nb.first][nb.second] != 'O')
                    {
                        printf("%d\n", f.l + 1);
                        return;
                    }
                }
                else
                {
                    factor nf;
                    nf.l = f.l + 1;
                    nf.r = nr;
                    nf.b = nb;
                    nf.d = d;
                    q.push(nf);
                }
            }
        }
    }

    void show()
    {
        printf("======BRD======\n");
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                printf("%c", BRD[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        printf("R : %d, %d\nB : %d, %d\n", R.first, R.second, B.first, B.second);
        printf("\n");
        printf("\n");

        printf("=====MOVE=====\n");
        for (int i = 1; i < N - 1; i++)
        {
            for (int j = 1; j < M - 1; j++)
            {
                printf("%d, %d\n", i, j);
                for (int d = 0; d < 4; d++)
                {
                    printf("(%d, %d) ", MOVE[i][j][d].first, MOVE[i][j][d].second);
                }
                printf("\n");
            }
        }
    }
};

int main()
{
    freopen("06.txt", "r", stdin);
    s sol;
    sol.ution();
    // sol.show();

    return 0;
}