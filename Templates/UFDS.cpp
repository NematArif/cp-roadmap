#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class UnionFind {
private:
    vi p, rank, setSize;
    int numSets;

public:
    UnionFind(int N) {
        p.assign(N, 0);
        for (int i = 0; i < N; ++i) p[i] = i;
        rank.assign(N, 0);
        setSize.assign(N, 1);
        numSets = N;
    }

    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }

    void UnionSet(int i, int j) {
        if (isSameSet(i, j)) return;
        int x = findSet(i), y = findSet(j);
        if (rank[x] > rank[y]) swap(x, y);
        p[x] = y;
        if (rank[x] == rank[y]) ++rank[y];
        setSize[y] += setSize[x];
        numSets--;
    }
};

int main() {
    UnionFind UF(5);
    printf("%d\n", UF.numDisjointSets());
    UF.UnionSet(0, 1);
    printf("%d\n", UF.numDisjointSets());
    UF.UnionSet(2, 3);
    printf("%d\n", UF.numDisjointSets());
    UF.UnionSet(4, 3);
    printf("%d\n", UF.numDisjointSets());
    printf("isSameSet(0, 3) = %d\n", UF.isSameSet(0, 3));
    printf("isSameSet(4, 3) = %d\n", UF.isSameSet(4, 3));
    for (int i = 0; i < 5; i++)
        printf("findSet(%d) = %d, sizeOfSet(%d) = %d\n",
               i, UF.findSet(i), i, UF.sizeOfSet(i));
    UF.UnionSet(0, 3);
    printf("%d\n", UF.numDisjointSets());
    for (int i = 0; i < 5; ++i)
        printf("findSet(%d) = %d, sizeOfSet(%d) = %d\n",
               i, UF.findSet(i), i, UF.sizeOfSet(i));
    return 0;
}
