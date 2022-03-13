#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int N, C;
map<int, int> FRQ, RCT;
vector<pair<int, int>> RST;

bool cmp(pair<int, int> a, pair<int, int> b)
{
    if (a.second == b.second)
        return RCT[a.first] < RCT[b.first];
    return a.second > b.second;
}

class s
{
private:

public:
    s()
    {
        scanf("%d %d", &N, &C);
        for (int i = 0; i < N; i++)
        {
            int buff;
            scanf("%d", &buff);
            FRQ[buff]++;
            if (RCT[buff] == 0)
                RCT[buff] = i + 1;
        }
    }

    void ution()
    {
        for (auto p : FRQ)
        {
            RST.emplace_back(p);
        }
        sort(RST.begin(), RST.end(), cmp);
        for (auto p : RST)
        {
            for (int i = 0; i < p.second; i++)
                printf("%d ", p.first);
        }
    }
};

int main()
{
    freopen("03.txt", "r", stdin);
    s sol;
    sol.ution();

    return 0;
}