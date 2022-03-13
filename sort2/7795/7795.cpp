#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class s
{
private:
    int N, M;
    vector<int> A, B;

public:
    s()
    {
        scanf("%d %d", &N, &M);
        A.reserve(N), B.reserve(M);
        for (int i = 0; i < N; i++)
        {
            int buff;
            scanf("%d", &buff);
            A.push_back(buff);
        }
        for (int i = 0; i < M; i++)
        {
            int buff;
            scanf("%d", &buff);
            B.push_back(buff);
        }
    }
    void ution()
    {
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());

        // show();

        int aidx = 0, bidx = 0, cnt = 0;
        for (aidx = 0; aidx < N; aidx++)
        {
            bidx = lower_bound(B.begin() + bidx, B.end(), A[aidx]) - B.begin();
            cnt += bidx;
        }
        printf("%d\n", cnt);
    }
    void show()
    {
        printf("A: ");
        for (auto i : A)
            printf("%d ", i);
        printf("\nB: ");
        for (auto i : B)
            printf("%d ", i);
        printf("\n");
    }
};

int main()
{
    freopen("01.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    while (T--)
    {
        s sol;
        sol.ution();
    }

    return 0;
}