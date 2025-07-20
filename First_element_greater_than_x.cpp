vector<int> v;

class SegTree {
public:
    vector<int> seg;

    SegTree(int n) {
        seg = vector<int>(4 * n);
    }

    void build(int i,int l, int r) {
        if (l == r) {
            seg[i] = v[l];
            return;
        }
        int mid = l + r >> 1;
        build(i * 2, l, mid);
        build(i * 2 + 1, mid + 1, r);
        seg[i] = max(seg[i * 2], seg[i * 2 + 1]);
    }

    void update(int i, int l, int r, int idx, int val) {
        if (l > idx || r < idx) return;
        if (l == r) {
            seg[i] = val;
            return;
        }
        int mid = l + r >> 1;
        update(i * 2, l, mid, idx, val);
        update(i * 2 + 1, mid + 1, r, idx, val);
        seg[i] = max(seg[i * 2], seg[i * 2 + 1]);
    }

    int query(int i, int l, int r, int val) {
        if (seg[i] < val) return 0;
        if (l == r) return l;
        int mid = l + r >> 1;
        if (seg[i * 2] >= val) return query(i * 2, l, mid, val);
        return query(i * 2 + 1, mid + 1, r, val);
    }
};
