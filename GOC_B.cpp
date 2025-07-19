#include <bits/stdc++.h>
using namespace std;

using ll = long long;
set<ll> palins;

// Build number from digit counts
void generatePalindromes(vector<int>& freq, string half, string& middle) {
    // Base case: all digits consumed
    int total=accumulate(freq.begin(),freq.end(),0);
    if (total==0) {
        string revHalf = half;
        reverse(revHalf.begin(), revHalf.end());
        string full = half + middle + revHalf;
        palins.insert(stoll(full));
        return;
    }

    for (int d=1;d<=9;d++) {
        if (freq[d] >= 2) {
            freq[d] -= 2;
            generatePalindromes(freq, half + char('0' + d), middle);
            freq[d] += 2;
        }
    }
}

void generateAllValidPalindromes() {
    // Try all subsets of digits 1–9
    for (int mask = 1; mask < (1 << 9); ++mask) {
        vector<int>freq(10);
        int total = 0;
        for (int d = 1; d <= 9; ++d) {
            if (mask & (1 << (d - 1))) {
                freq[d] = d;
                total += d;
            }
        }

        // Count how many digits appear odd times
        int odd_count = 0;
        int mid_digit = -1;
        for (int d=1;d<=9;++d) {
            if (freq[d] % 2 == 1) {
                odd_count++;
                mid_digit = d;
            }
        }

        if (odd_count > 1) continue; // can't make palindrome
        if(total>18) continue;
        string mid = "";
        if (mid_digit != -1) {
            mid = char('0' + mid_digit);
            freq[mid_digit]--;
        }

        generatePalindromes(freq, "", mid);
    }

}

int main() {
    int t;
    cin>>t;

    generateAllValidPalindromes();
    while (t--)
    {
        ll n;
        cin >> n;
        cout<<*palins.upper_bound(n)<<endl;
    }
    

}