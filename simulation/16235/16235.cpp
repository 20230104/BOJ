#include <cstdio>
#include <vector>

using namespace std;

class s{
private:
    const int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
    const int dy[8] = {1, -1, -1, 0, 1, -1, 0, 1};
    int N, M, K;
    vector<vector<vector<int>>> GROUND;
    vector<vector<int>> FOOD, DELTA;
    
    int max(int x, int y){return x>y?x:y;}
    bool isValid(int x, int y){return 0<=x&&x<N&&0<=y&&y<N;}
public:
    s(){
        scanf("%d %d %d", &N, &M, &K);
        GROUND.assign(N, vector<vector<int>>(N, vector<int>(1111, 0)));
        FOOD.assign(N, vector<int>(N, 5));
        DELTA.assign(N, vector<int>(N));
        
        for(int i = 0 ; i<N;i++){
            for(int j = 0 ; j<N;j++){
                scanf("%d", &DELTA[i][j]);
            }
        }
        
        for(int i = 0 ; i<M;i++){
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            GROUND[x-1][y-1][z]++;
            GROUND[x-1][y-1][0] = max(GROUND[x-1][y-1][0], z);
        }
    }
    
    void springAndSummer(int x, int y){
        int &food = FOOD[x][y];
        vector<int> &spot = GROUND[x][y];
        int i = 1, m = 0, b = 0, cur = 0, flag = 0, size = spot[0];
        for(i = 1 ; i<=size;i++){
            cur = spot[i];
            spot[i] = b;
            if(b) m = i;
            if(cur==0){//해당 나이의 나무가 존재하지 않음
                b = 0;
                continue;
            }
            if(food<i*cur){//말라죽은 나무 존재 
                flag = 1;
                break;
            }
            else{//무럭무럭
                food-=i*cur;
            }
            b = cur;
        }
        if(flag){//말라죽은 나무가 존재함
            if(food>=i){//적어도 하나는 안죽음
                spot[0] = i + 1;
                b = food/i;
                cur -= b;
                food%=i;
                food+=i/2*cur;
            }
            else{//모두 죽음
                spot[0] = m;
                food+=i/2*cur;
                //spot[i] = 0;
                b = spot[m];
            }
            for(i++;i<=size;i++){//이후로는 모두 퇴비화
                food+=i/2*spot[i];
                spot[i] = 0;
            }
            spot[spot[0]] = b;
            
        }
        else{//모두 행복하게 먹음
            spot[i] = b;
            spot[0] = i;
        }
        if(spot[spot[0]]==0)spot[0] = 0;
    }
    void autumn(int x, int y){
        int cnt = 0;
        for(int i = 5;i<=GROUND[x][y][0];i+=5){
            cnt+=GROUND[x][y][i];
        }
        for(int d = 0;d<8;d++){
            int nx = x + dx[d], ny = y + dy[d];
            if(isValid(nx, ny)&&cnt){
                GROUND[nx][ny][1]+=cnt;
                if(GROUND[nx][ny][0]==0)GROUND[nx][ny][0] = 1;
            }
        }
    }
    void winter(int x, int y){
        FOOD[x][y]+=DELTA[x][y];
    }
    void spotInfo(int x, int y){
        printf("%d, %d's info\n", x, y);
        printf("food:%d\n", FOOD[x][y]);
        printf("size:%d\n", GROUND[x][y][0]);
        for(int i = 1;i<=GROUND[x][y][0];i++)printf("%d:%d\n", i, GROUND[x][y][i]);
    }

    void show(){
        // printf("=====[0]=====\n");
        // for(int i = 0 ; i<N;i++){
        //     for(int j = 0 ; j<N;j++){
        //         printf("%d ", GROUND[i][j][0]);
        //     }
        //     printf("\n");
        // }
        printf("=====cnt=====\n");
        for(int i = 0 ; i<N;i++){
            for(int j = 0 ; j<N;j++){
                int cnt = 0;
                for(int k = 1;k<=GROUND[i][j][0];k++)cnt+=GROUND[i][j][k];
                printf("%5d ", cnt);
            }
            printf("\n");
        }
    }
    
    void routine(){
        for(int i = 0 ; i<N;i++){
            for(int j = 0 ; j<N;j++){
                springAndSummer(i, j);
            }
        }
        for(int i = 0 ; i<N;i++){
            for(int j = 0 ; j<N;j++){
                autumn(i, j);
            }
        }
        for(int i = 0 ; i<N;i++){
            for(int j = 0 ; j<N;j++){
                winter(i, j);
            }
        }
    }
    
    void ution(){
        for(int i = 0;i<K;i++){
            //printf("DAY-%d\n", i + 1);            
            //spotInfo(0, 1);
            routine();
            //spotInfo(7, 0);
            //show();
        }
        int cnt = 0;
        for(int i = 0 ; i<N;i++){
            for(int j = 0 ; j<N;j++){
                for(int s = 1;s<=GROUND[i][j][0];s++)cnt+=GROUND[i][j][s];
            }
        }
        printf("%d\n", cnt);
    }
};

int main()
{
    freopen("1000.txt", "r", stdin);
    s sol;
    sol.ution();
    return 0;
}
