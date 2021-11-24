//也请让我相信，你一直以来所相信的事吧——“活着是一件很美好的事”
//只要记住你的名字，不管你在世界的哪个地方，我一定会去见你!
//我现在依然喜欢着你，但我们就算是来往一千封邮件，心却不可能接近哪怕一厘米。
//嗯，那样的话，你就再努力一次试试吧！别在这种地方畏畏缩缩的！别对自己说谎！再努力一次吧。
//我说过了，若是有想要拯救之物，就果断地出手全力去守护!
//拜托了，请把力量借给软弱的我，给我从这里再度起身迈步的力量！
//虽然灯塔已经失去了光明……但是，只要有你的那首歌在，就一定能将那些人再次导向此方。
//小时候曾认为这个世界单纯简单，没有赢不了的比试，努力就会有回报，认为这世上一切皆有可能。
//虽然我能办到的或许只有陪伴你……但是，至少我可以陪着你。
//如果声音有形状的话，那一定是你喜欢的样子。
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define fastio ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string& s) {
return '"' + s + '"';
}

string to_string(const char* s) {
return to_string((string) s);
}

string to_string(bool b) {
return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
bool first = true;
string res = "{";
for (int i = 0; i < static_cast<int>(v.size()); i++) {
if (!first) {
res += ", ";
}
first = false;
res += to_string(v[i]);
}
res += "}";
return res;
}

template <size_t N>
string to_string(bitset<N> v) {
string res = "";
for (size_t i = 0; i < N; i++) {
res += static_cast<char>('0' + v[i]);
}
return res;
}

template <typename A>
string to_string(A v) {
bool first = true;
string res = "{";
for (const auto &x : v) {
if (!first) {
res += ", ";
}
first = false;
res += to_string(x);
}
res += "}";
return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
cerr << " " << to_string(H);
debug_out(T...);
}

#ifdef _KHORAY
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif
void solve() {
    cout<<"100000\n";
    for(int i=1;i<=100000;i++) {
        cout<<i<<' ';
    }
}
signed main() {
    freopen("test.in","w",stdout);
    //fastio;
    int t = 1;
    while(t--) solve();
    return 0;
}