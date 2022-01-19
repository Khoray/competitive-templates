struct Fenwick {
    vector<int> fen;
    Fenwick(int n) : fen(n + 1) { }
    void add(int pos, int val) {
        for(; pos < fen.size(); pos += pos & -pos) {
            fen[pos] += val;
        }
    }
    int query(int pos) {
        int ret = 0;
        for(; pos > 0; pos -= pos & -pos) {
            ret += fen[pos];
        }
        return ret;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};