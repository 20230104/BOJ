#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef struct
{
    string name;
    int K, E, M;
} SBJ;

bool cmp(SBJ a, SBJ b)
{
    if (a.K > b.K)
        return true;
    else if (a.K < b.K)
        return false;
    if (a.E < b.E)
        return true;
    else if (a.E > b.E)
        return false;
    if (a.M > b.M)
        return true;
    else if (a.M < b.M)
        return false;
    return a.name < b.name;
}

class s
{

private:
    int N;
    vector<SBJ> V;

public:
    s()
    {
        cin >> N;
        V.reserve(N);
        for (int i = 0; i < N; i++)
        {
            SBJ buff;
            cin >> buff.name >> buff.K >> buff.E >> buff.M;
            V.emplace_back(buff);
        }
    }

    void ution()
    {
        sort(V.begin(), V.end(), cmp);
        for (auto i : V)
            cout << i.name << '\n';
    }
};

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("01.txt", "r", stdin);
    s sol;
    sol.ution();

    return 0;
}