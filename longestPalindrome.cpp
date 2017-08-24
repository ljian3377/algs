#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    // Transform S into T.
    // For example, S = "abba", T = "^#a#b#b#a#$".
    // ^ and $ signs are sentinels appended to each end to avoid bounds checking
    string preProcess(string s) {
        string res = "^";
        for (auto c:s) {
            res += '#';
            res +=  c;
        }
        res += "#$";
        return res;
    }

    string longestPalindrome(string s) {
        string str = preProcess(s);
        int T[2003];
        int len = str.size();
        for (int i=0; i< len; i++) { T[i] = 0;}

        for (int i=1; i< len-1; i++) {
            // expand from i, T[i] keeps the length that is already examined
            int lenP = T[i];
            while (str[i-lenP-1] == str[i+lenP+1]) lenP++;
            T[i] = lenP;

            int j;
            for (j=1; j <= lenP; j++) {
                // palindrome centered at i+j exceed
                if (T[i-j] + j >= lenP) {
                    T[i+j] = min(T[i-j], lenP-j);
                    break;
                } else {
                    T[i+j] = T[i-j];
                }
            }
            i = i+j-1;
        }
        
        int maxLen = 0, center = -1;
        for (int i=1; i<len-1; i++) {
            if ( T[i] > maxLen) {
                maxLen = T[i];
                center = i;
            }
        }
        return s.substr((center-maxLen-1)/2, maxLen);
    }
};

int main() {
    string s;
    cin>>s;

    Solution *so = new Solution();
    cout<<so->longestPalindrome(s);

    // system("pause");
    return 0;
}