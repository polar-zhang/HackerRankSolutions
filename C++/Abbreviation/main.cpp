#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Complete the abbreviation function below.
string abbreviation(string a, string b) {
    vector<vector<bool>> dp(b.size() + 1, vector<bool>(a.size() + 1, false));
    dp[0][0] = true;
    for (int i = 0; i <= b.size(); i++) {
        for (int j = 1; j <= a.size(); j++) {
            if (i == 0) {
                dp[i][j] = a[j - 1] >= 'a' && dp[i][j - 1];
            }
            else {
                if (a[j - 1] == b[i - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else if (a[j - 1] == b[i - 1] + 'a' - 'A') {
                    dp[i][j] = dp[i - 1][j - 1] || dp[i][j - 1];
                }
                else if (a[j - 1] >= 'a') {
                    dp[i][j] = dp[i][j - 1];
                }
                // else a[j - 1] < 'a', default value is false
            }
        }
    }

    return dp[b.size()][a.size()] ? "YES" : "NO";
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));
    ifstream fin("input14.txt");

    int q;
    fin >> q;
    fin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string a;
        getline(fin, a);

        string b;
        getline(fin, b);

        string result = abbreviation(a, b);

        cout << result << "\n";
    }

    // fout.close();

    return 0;
}