#include <bits/stdc++.h>
using namespace std;

class UnionFind
{
public:
    vector<int> parent, sz;
    UnionFind(int size)
    {
        parent.resize(size);
        sz.resize(size, 1);
        for (int i = 0; i < size; i++)
        {
            parent[i] = i;
        }
    }
    int find(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }
    void Union(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a != b)
        {
            if (sz[a] < sz[b])
                swap(a, b);
            parent[b] = a;
            sz[a] += sz[b];
        }
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    UnionFind uf(n);
    int p, q;
    while (m--)
    {
        cin >> p >> q;
        p--, q--;
        uf.Union(p, q);
    }

    // group indices by component
    vector<vector<int>> components(n);
    for (int i = 0; i < n; i++)
    {
        components[uf.find(i)].push_back(i);
    }

    long long result = 0;
    for (int i = 0; i < n; i++)
    {
        vector<int> vals;
        int pos = 0, neg = 0;
        for (int idx : components[i])
        {
            vals.push_back(a[idx]);
            if ((idx % 2) == 0)
                pos++;
            else
                neg++;
        }
        sort(vals.begin(), vals.end(), greater<int>());
        for (int i = 0; i < pos; i++)
            result += vals[i];
        for (int j = pos; j < pos + neg; j++)
            result -= vals[j];
    }

    cout << result << endl;
    return 0;
}