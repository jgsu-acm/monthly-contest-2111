#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

namespace Segtree {
constexpr inline int lch(const int now) { return now << 1; }
constexpr inline int rch(const int now) { return now << 1 | 1; }

int n, p;
struct Node {
    int val, idx;

    bool operator<(const Node & rhs) const { return val == rhs.val ? idx > rhs.idx : val < rhs.val; }
} sgt[N * 4];
int a[N];

void pushup(const int now) { sgt[now] = max(sgt[lch(now)], sgt[rch(now)]); }

void _init(const int now, const int l, const int r) {
    if (l == r) {
        sgt[now] = {a[l], l};
        return;
    }
    int mid = (l + r) / 2;
    _init(lch(now), l, mid);
    _init(rch(now), mid + 1, r);
    pushup(now);
}   // namespace Segtree

void _modify(const int pos, const int k, const int now, const int l, const int r) {
    if (l == r) {
        if ((sgt[now].val += k) >= p) sgt[now].val -= p;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
        _modify(pos, k, lch(now), l, mid);
    else
        _modify(pos, k, rch(now), mid + 1, r);
    pushup(now);
}

auto _query(const int ql, const int qr, const int now, const int l, const int r) {
    if (ql <= l && r <= qr) return sgt[now];
    int mid = (l + r) / 2;
    Node _1 = {-1, 0}, _2 = {-1, 0};
    if (ql <= mid)
        _1 = _query(ql, qr, lch(now), l, mid);
    if (qr > mid)
        _2 = _query(ql, qr, rch(now), mid + 1, r);
    return max(_1, _2);
}

void init() {
    cin >> n >> p;
    ++p;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    _init(1, 1, n);
}

void modify(int x, int y) {
    if (!(1 <= x && x <= n)) {
        cout << "invalid\n";
        return;
    }
    _modify(x, y % p, 1, 1, n);
}

void query(int x, int y) {
    if (!(1 <= x && x <= y && y <= n)) {
        cout << "invalid\n";
        return;
    }
    auto _ = _query(x, y, 1, 1, n);
    cout << _.val << ' ' << _.idx << '\n';
}
}   // namespace Segtree
using Segtree::init;
using Segtree::modify;
using Segtree::query;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    init();
    int m;
    cin >> m;
    for (int i = 1, op, x, y; i <= m; ++i) {
        cin >> op >> x >> y;
        if (op == 1)
            modify(x, y);
        else
            query(x, y);
    }
    return 0;
}