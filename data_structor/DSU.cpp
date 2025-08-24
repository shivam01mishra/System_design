#include<iostream>
#include<vector>
using namespace std;

class DSU {
    int n;
    vector<int> parent;
    vector<int> sz;

public:
    DSU(int n) {
        this->n = n;
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    int get_parent(int x) {
        if (parent[x] == x) return x;
        return parent[x] = get_parent(parent[x]); // path compression
    }

    bool is_connected(int x, int y) {
        return get_parent(x) == get_parent(y);
    }

    void connect(int x, int y) {
        int par1 = get_parent(x);
        int par2 = get_parent(y);
        if (par1 == par2) return;  // already in same set

        // Union by size
        if (sz[par1] < sz[par2]) {
            sz[par2] += sz[par1];
            parent[par1] = par2;
        }
        else {
            sz[par1] += sz[par2];
            parent[par2] = par1;
        }
    }
};

int main() {
    DSU mydsu(5);
    mydsu.connect(1, 4);
    mydsu.connect(1, 3);
    mydsu.connect(2, 5);

    cout << "1 and 3 connected? " << mydsu.is_connected(1, 3) << "\n";
    cout << "1 and 5 connected? " << mydsu.is_connected(1, 5) << "\n";

    return 0;
}
