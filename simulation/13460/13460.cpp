#include <cstdio>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

class s
{
    typedef struct{
        pair<int, int> r, b;
        int l;
    }factor;
private:
    int N, M;
    pair<int, int> R, B;
    vector<vector<char>> BRD;
    vector<vector<vector<pair<int, int>>>> MOVE;

    bool incline(pair<int, int> &r, pair<int, int> &b, int d)
    {
        pair<int, int> nr;
        pair<int, int> nb;
        switch (d)
        {
        case 0:
            nr = MOVE[r.first][r.second][0];
            nb = MOVE[b.first][b.second][0];
            if (nr == nb && BRD[nr.first][nr.second] != 'O')
            {
                if (r.first < b.first)
                    nb.first++;
                else
                    nr.first++;
            }
            break;
        case 1:
            nr = MOVE[r.first][r.second][1];
            nb = MOVE[b.first][b.second][1];
            if (nr == nb && BRD[nr.first][nr.second] != 'O')
            {
                if (r.second < b.second)
                    nr.second--;
                else
                    nb.second--;
            }
        case 2:
            nr = MOVE[r.first][r.second][2];
            nb = MOVE[b.first][b.second][2];
            if (nr == nb && BRD[nr.first][nr.second] != 'O')
            {
                if (r.first < b.first)
                    nr.first--;
                else
                    nb.first--;
            }
        case 3:
            nr = MOVE[r.first][r.second][3];
            nb = MOVE[b.first][b.second][3];
            if (nr == nb && BRD[nr.first][nr.second] != 'O')
            {
                if (r.second < b.second)
                    nb.second++;
                else
                    nr.second++;
            }

        default:
            break;
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

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
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

    void ution(){
        makeMoveTable();
        queue<factor> q;
        factor f;
        f.l = 0, f.r = R, f.b = B;
        q.push(f);

        while(!q.empty()){
            f = q.front();
            q.pop();
            if(f.l == 10){
                printf("-1\n");
                return;
            }
            pair<int, int> nb, nr;  
            for(int d = 0;d<4;d++){
                nb = f.b, nr = f.r;
                if(incline(nr, nb, d)){
                    if(BRD[nb.first][nb.second] != 'O'){
                        printf("%d\n", f.l + 1);
                        return;
                    }
                }
                else{
                    factor nf;
                    nf.l = f.l + 1;
                    nf.r = nr;
                    nf.b = nb;
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
    }
};

int main()
{
    freopen("01.txt", "r", stdin);
    s sol;
    sol.ution();

    return 0;
}