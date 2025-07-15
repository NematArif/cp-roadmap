#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class UnionFind {                                                                   //OOP style
private:
    vi p, rank, setSize;
    int numSets;

public:
    UnionFind(int N) {
        p.assign(N, 0);
        for (int i = 0; i < N; ++i) p[i] = i;
        rank.assign(N, 0);                    // optional speed up
        setSize.assign(N, 1);                 // optional speed up
        numSets = N;                          // optional speed up
    }

    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    int numDisjointSets() { return numSets; }                                  // optional
    int sizeOfSet(int i) { return setSize[findSet(i)]; }                        // optional

    void UnionSet(int i, int j) {
        if (isSameSet(i, j)) return;                        // i and j are in the same set
        int x = findSet(i), y = findSet(j);                 // find both rep items
        if (rank[x] > rank[y]) swap(x, y);                  // keep x 'shorter' than y
        p[x] = y;                                           // set x under y
        if (rank[x] == rank[y]) ++rank[y];                  // optional speed up
        setSize[y] += setSize[x];                           // combine set sizes at y
        numSets--;                                          // a union reduces numSets
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
