vector<int> KMP(string & s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i= 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

