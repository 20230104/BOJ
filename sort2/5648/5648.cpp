#include <cstdio>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class s
{
private:
    int N;
    vector<ll> V;

    ll reverse(ll n)
    {
        ll ret = 0;
        while (n)
        {
            ret *= 10;
            ret += n % 10;
            n /= 10;
        }
        return ret;
    }

public:
    s()
    {
        scanf("%d", &N);
        V.reserve(N);
        for (int i = 0; i < N; i++)
        {
            ll buff;
            scanf("%lld", &buff);
            V.push_back(reverse(buff));
        }
    }

    void ution()
    {
        sort(V.begin(), V.end());

        for (auto i : V)
            printf("%lld\n", i);
    }
};

int main()
{
    freopen("test.txt", "r", stdin);
    s sol;
    sol.ution();

    return 0;
}