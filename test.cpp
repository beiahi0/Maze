#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include <sources/dbg.h>
#else
#define dbg(...) (__VA_ARGS__)
#endif

#define IO ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define fi first
#define se second
#define endl "\n"
#define int long long
#define sz(x) (int) x.size()
#define alls(v) v.begin(), v.end()
#define ralls(v) v.rbegin(), v.rend()
#define vi vector<int>
#define vb vector<bool>
#define vs vector<string>


typedef long long LL;
typedef pair<int, int> PII;

const int INF = 0x3f3f3f3f;

void solve()
{
    vs v;

    v.push_back("你好");
    v.push_back("啊啊啊啊");
    v.push_back("徐");
    v.push_back("伍");

    sort(alls(v));

    for (auto x : v)
        cout << x << endl;
}

signed main()
{
#ifdef LOCAL
    freopen("../../in.txt", "r", stdin);
    freopen("../../out.txt", "w", stdout);
#endif
    IO;
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
}
