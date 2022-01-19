string itt(int time) {
    string ret = "";
    ret += char(time / 60 / 10 + '0');
    ret += char(time / 60 % 10 + '0');
    ret += ":";
    ret += char(time % 60 / 10 + '0');
    ret += char(time % 60 % 10 + '0');
    return ret;
}

int tti(string time) {
    return ((time[0] - '0') * 10 + (time[1] - '0')) * 60 + (time[3] - '0') * 10 + (time[4] - '0');
}
