#include <bits/stdc++.h>
using namespace std;

bool possible(int *a, int n, int d, int k)
{
    int prev = a[0];
    for (int i = 1; i < n; i++)
    {
        while (a[i] - prev > d)
        {
            if (k > 0)
            {
                prev = prev + d;
                k--;
            }
            else
                return 0;
        }
        prev = a[i];
    }
    return 1;
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
        long long n, k;
        cin >> n >> k;
        int a[n];
        int r = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
            if (i > 0)
                if (a[i] - a[i - 1] + 1 > r)
                    r = a[i] - a[i - 1] + 1;
        }

        int l = 0;
        int ans = 0;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;

            if (possible(a, n, mid, k))
            {
                ans = mid;
                r = mid - 1;
            }
            else
                l = mid + 1;
        }

        cout << "Case #" << test_case << ": " << ans << "\n";
    }
    return 0;
}