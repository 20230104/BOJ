#include <cstdio>
#include <vector>
#include <tuple>

using namespace std;

class s{
    typedef struct{
        int s, d, z;
    }SHARK_INFO;
private:
    int R, C, M;
    int G = 0;
    int MOD_R, MOD_C;
    vector<vector<SHARK_INFO>> MAP;
    vector<pair<int, int>> SHARKS;
    SHARK_INFO EMPTY;

    int shift(int x, int a, int d){
        int n = d>2?C:R;
        int ret = x + a;
        if(ret <= 0) return -shift(1, 1-a-x, d);
        if(ret > n) return -shift(n, n-a-x, d);
        return ret;
    }
    
    pair<int, int> move(int r, int c, SHARK_INFO &s){
        //printf("r%d, c%d, s%d, d%d, z%d    ", r, c, s.s, s.d, s.z);
        pair<int, int> ret;
        ret = make_pair(r, c);
        if(s.d>2){//left or right
            ret.second = shift(c, s.d==3?s.s:-s.s, s.d);
            if(ret.second < 0){
                ret.second = -ret.second;
                s.d = 7-s.d;
            }
        }
        else{
            ret.first = shift(r, s.d==2?s.s:-s.s, s.d);
            if(ret.first < 0){
                ret.first = -ret.first;
                s.d = 3-s.d;
            }
        }
        //printf("r%d, c%d, s%d, d%d, z%d    \n", ret.first, ret.second, s.s, s.d, s.z);
        return ret;
    }
    
    void next(){
        vector<vector<SHARK_INFO>> m(R + 1, vector<SHARK_INFO>(C+1, EMPTY));
        vector<pair<int, int>> s;
        for(auto shark:SHARKS){
            int r = shark.first, c = shark.second;
            auto info = MAP[r][c];
            tie(r, c) = move(r, c, info);
            if(m[r][c].z == 0){
                s.push_back({r, c});
            }
            if(m[r][c].z < info.z)m[r][c] = info;
        }
        
        MAP.swap(m);
        SHARKS.swap(s);
    }
public:
    s(){
        EMPTY.d = EMPTY.s = EMPTY.z = 0;
        scanf("%d %d %d", &R, &C, &M);
        MOD_R = R>1?R*2-2:1, MOD_C = C>1?C*2-2:1;
        MAP.assign(R + 1, vector<SHARK_INFO>(C + 1, EMPTY));
        for(int i = 0 ; i<M;i++){
            int r, c;
            SHARK_INFO b;
            scanf("%d %d %d %d %d", &r, &c, &b.s, &b.d, &b.z);
            if(MAP[r][c].z == 0){
                SHARKS.push_back({r, c});
            }
            if(MAP[r][c].z < b.z)MAP[r][c] = b;
        }
    }

    void test(){
        SHARK_INFO s;
        s.s = 8;
        s.d = 4;
        s.z = 10;
        printf("%d\n", shift(6, 1, 4));
    }
    
    void show(){
        printf("=====SHOW MAP=====\n");
        for(auto M:MAP){
            for(auto i:M)printf("%d ", i.z);
            printf("\n");
        }
        printf("=====SHARKS=====\n");
        for(auto s:SHARKS){
            printf("%d %d\n", s.first, s.second);
        }
        printf("\n");
        
    }
    
    void ution(){
        for(int i = 1;i<=C;i++){ 
            int r;
            for(r = 1;r<=R;r++){
                if(MAP[r][i].z) break;
            }
            if(0<r&&r<=R){
                G+=MAP[r][i].z;
                MAP[r][i] = EMPTY;
            }
            next();
        }
        printf("%d", G);
    }
};

int main()
{
    freopen("04.txt", "r", stdin);
    s sol;
    //sol.test();
    sol.ution();
    
    return 0;
}
