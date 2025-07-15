#include <bits/stdc++.h>

using namespace std;

#define LSOne(S) ((S) & (-S))

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;

class FenwickTree {                             // index 0 is not used
private:
    vll ft;                                     // internal FT is an array
public:
    FenwickTree(int m) { ft.assign(m + 1, 0); } // create an empty FT

    void build(const vll &f) {                  
        int m = (int)f.size() - 1;              // note f[0] is always 0
        ft.assign(m + 1, 0);
        for(int i = 1;i <= m;i ++) {            // O(m)
            ft[i] += f[i];                      // add this value
            if(i + LSOne(i) <= m)               // i has parent
                ft[i + LSOne(i)] += ft[i];      // add to that parent
        }
    }

    FenwickTree(const vll &f) { build(f); }     // create FT based on f

    FenwickTree(int m, const vi &s) {           // create FT based on s
        vll f(m + 1, 0);
        for(int i = 0;i < (int)s.size();i ++)   // do the conversion first
            ++f[s[i]];                          // in O(n)
        build(f);                               // in O(m)
    }

    int rsq(int j) {                            // returns RSQ(1, j)
        int sum = 0;
        for(; j; j -= LSOne(j)) 
            sum += ft[j];
        return sum;
    }

    int rsq(int i, int j) { return rsq(j) - rsq(i - 1); }   // inc/exclusion

    // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
    void update(int i, int v) {
        for(; i < (int)ft.size(); i += LSOne(i))
            ft[i] += v;
    }

    int select(ll k) {                              // O(log m)
        int lo = 1, hi = ft.size() - 1;
        for (int i = 0;i < 30;++ i) {
            int mid = (lo + hi) / 2;
            (rsq(1, mid) < k) ? lo = mid : hi = mid;
        }
        return hi;
    }
};

class RUPQ {                                    // RUPQ variant
private:
    FenwickTree ft;                             // internally use PURQ FT
public:         
    RUPQ(int m) : ft(FenwickTree(m)) {}
    void range_update(int ui, int uj, int v) {
        ft.update(ui, v);                       // [ui, ui+1, ..., m] +v
        ft.update(uj + 1, -v);                  // [uj+1, uj+2, ..., m] -v
    }                                           // [ui, ui+1, ..., uj] +v
    ll point_query(int i) { return ft.rsq(i); } // rsq(i) is sufficient
};

class RURQ {                                    // RURQ variant
private:                                        // need two helper FTs      
    RUPQ rupq;                                  // one RUPQ and
    FenwickTree purq;                           // one PURQ
public:
    RURQ(int m) : rupq(RUPQ(m)), purq(FenwickTree(m)) {} // initialization
    void range_update(int ui, int uj, int v) {
        rupq.range_update(ui, uj, v);                    // [ui, ui+1, ..., uj] +v
        purq.update(ui, v * (ui - 1));                   // -(ui-1)*v before ui
        purq.update(uj + 1, -v*uj);                      // +(uj-ui+1)*v after uj
    }
    ll rsq(int j) {                                      
        return rupq.point_query(j) * j -                 // optimistic cancellation
               purq.rsq(j);                              // cancellation factor
    }
    ll rsq(int i, int j) { return rsq(j) - rsq(i - 1); } // standard
};

int main() {
    vll f = {0, 0, 1, 0, 1, 2, 3, 2, 1, 1, 0};
    FenwickTree ft(f);
    printf("%lld\n", ft.rsq(1, 6));
    printf("%d\n", ft.select(7));
    ft.update(5, 1);
    printf("%lld\n", ft.rsq(1, 10));
    printf("=====\n");
    RUPQ rupq(10);
    RURQ rurq(10);
    rupq.range_update(2, 9, 7);
    rurq.range_update(2, 9, 7);
    rupq.range_update(6, 7, 3);
    rurq.range_update(6, 7, 3);

    for (int i = 1;i <= 10;i ++)
        printf("%d -> %lld\n", i, rupq.point_query(i));

    printf("RSQ(1, 10) = %lld\n", rurq.rsq(1, 10));
    printf("RSQ(6, 7) = %lld\n", rurq.rsq(6, 7));
}
