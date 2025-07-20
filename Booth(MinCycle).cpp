//Minimal Rotation String

int min_cyc(string s)
{
    int p = 0;
    s += s;

    vector<int> f(s.size(), -1);
    for (int l = 1, r = 1; r < s.size(); ++r)
    {
        for (l = f[r - p - 1]; l != -1 && s[p + l + 1] != s[r]; l = f[l])
            if (s[l + p + 1] > s[r])
                p = r - l - 1;

        if (l == -1 && s[p + l + 1] != s[r])
        {
            if (s[p + l + 1] > s[r])
                p = r;

            f[r - p] = -1;
        }
        else
        {
            f[r - p] = l + 1;
        }
    }

    return p;
}