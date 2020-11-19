#include <bits/stdc++.h>
using namespace std;

int ans;
class trie_node
{
public:
    long long count;
    int l;
    trie_node *nodes[26];
    trie_node(int k)
    {
        count = 0;
        l = k;
        for (int i = 0; i < 26; i++)
            nodes[i] = NULL;
    }
    void insert(string &s, int i);
};

void trie_node::insert(string &s, int i)
{
    if (i >= s.size())
        return;
    int pos = s[i] - 'A';
    if (i == s.size() - 1)
    {
        if (nodes[pos] == NULL)
            nodes[pos] = new trie_node(i + 1);
        nodes[pos]->count++;
    }

    if (nodes[pos])
    {
        nodes[pos]->insert(s, i + 1);
    }
    else
    {
        nodes[pos] = new trie_node(i + 1);
        nodes[pos]->insert(s, i + 1);
    }
}

int dfs(trie_node *root, int k)
{
    int mod = 0;
    for (int i = 0; i < 26; i++)
    {
        if (root->nodes[i])
        {
            mod += dfs(root->nodes[i], k);
        }
    }
    root->count += mod;
    ans += (root->count / k) * root->l;
    return root->count % k;
}

void solve()
{
    ans = 0;
    int n, k;
    cin >> n >> k;
    trie_node *root = new trie_node(0);
    vector<string> s(n);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        root->insert(s[i], 0);
    }
    dfs(root, k);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    int test_case = 0;
    while (t--)
    {
        test_case++;
        solve();
        cout << "Case #" << test_case << ": " << ans << "\n";
    }
    return 0;
}