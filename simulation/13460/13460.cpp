#include <cstdio>
#include <vector>
#include <utility>

using namespace std;

class s
{
private:
    int N, M;
    pair<int, int> R, B;
    vector<vector<char>> BRD;

    bool incline(pair<int, int> &r, pair<int, int> &b, int d)
    {
        switch (d)
        {
        case 0: // NORTH
            if (r.second == b.second)
            {
                if (r.first < b.first)
                {
                    move(r, 0);
                    move(b, 0);
                    if (r.first == b.first && BRD[b.first][b.second] != 'O')
                        b.first++;
                }
                else
                {
                    move(b, 0);
                    move(r, 0);
                    if (r.first == b.first && BRD[r.first][r.second] != 'O')
                        r.first++;
                }
            }
            else
            {
                move(r, 0);
                move(b, 0);
            }
            break;

        default:
            break;
        }
    }

    void move(pair<int, int> &p, int d)
    {
        switch (d)
        {
        case 0:
            while (BRD[p.first - 1][p.second] != '#')
            {
                if (BRD[p.first][p.second] == 'O')
                    return ;
                p.first--;
            }

            break;

        default:
            break;
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

    void test()
    {
        incline(R, B, 0);
        show();
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
    }
};

int main()
{
    freopen("test.txt", "r", stdin);
    s sol;
    sol.test();
    return 0;
}