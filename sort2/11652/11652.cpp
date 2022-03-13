#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

bool cmp(pair<ll, int> a, pair<ll, int> b)
{
    if (a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
}

class s
{
private:
    int N;
    map<ll, int> CRD;

public:
    s()
    {
        scanf("%d", &N);
        for (int i = 0; i < N; i++)
        {
            ll buff;
            scanf("%lld", &buff);
            CRD[buff]++;
        }
    }

    void ution()
    {
        vector<pair<ll, int>> r;
        for (auto p : CRD)
        {
            r.emplace_back(p);
        }
        sort(r.begin(), r.end(), cmp);
        printf("%lld\n", r[0].first);
    }
};

int main()
{
    freopen("test.txt", "r", stdin);
    s sol;
    sol.ution();

    return 0;
}