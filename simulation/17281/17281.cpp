#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class s{
    private:
    int N, M = 0;
    vector<vector<int>> BRD;
    int calScore(int p[9]){
        int start = 0, ret = 0;
        for(int i = 0 ; i<N;i++){
            if(M>=ret + (N - i)*24) return 0;
            int tmp[3];
            int cnt = 0, out = 0, t = start;
            while(out!=3){
                if(BRD[i][p[t%9]] == 0){
                    out++;
                }
                else{
                    tmp[cnt%3] = BRD[i][p[t%9]];
                    cnt++;
                }
                t++;
            }
            int las = 0;
            for(int c = 1; c<4;c++){
                if(cnt - c <0){
                    cnt = 0;
                    break;
                }
                las+=tmp[(cnt - c) % 3];
                if(las >= 4){
                    cnt -= c - 1;
                    break;
                }
            }
            if(cnt >= 3&&las == 3)cnt -=3 ;
            ret+=cnt;
            start = t%9;
        }
        return ret;
    }
    public:
    s(){
        scanf("%d", &N);
        BRD.assign(N, vector<int>(9));
        for(int i = 0 ; i<N;i++){
            for(int j = 0 ; j<9;j++){
                scanf("%d", &BRD[i][j]);
            }
        }
    }
    void ution(){
        int semi_p[8] = {1, 2, 3, 4, 5, 6, 7, 8};
        do{
            int p[9];
            for(int i = 0 ; i<3;i++) p[i] = semi_p[i];
            p[3] = 0;
            for(int i = 4;i<9;i++) p[i] = semi_p[i-1];
            //show(p);
            M = max(M, calScore(p));
        }while(next_permutation(semi_p, semi_p + 8));
        printf("%d", M);
    }
    
    void test(){
        int p[9] = {0, 1, 2,3,4,5,6,7,8};
        printf("%d", calScore(p));
    }
    
    void show(int p[]){
        for(int i = 0 ; i<9;i++) printf("%d ", p[i]);
        printf("\n");
    }
};

int main()
{
    s sol;
    sol.ution();
    return 0;
}
