#17141[연구소 2](https://www.acmicpc.net/problem/17141)

## 기본 아이디어  
2에서 0까지 도달하는 거리의 최솟값들을 미리 계산하자.  
이때 다른 바이러스를 놓을 수 있는 곳은 빈곳으로 생각한다.  
즉, 조합에 따라 달라져도 같은 virus에 대한 BFS는 동일하게 탐색되기 때문에 중복되는 계산을 줄여주는 것(메모이제이션)  