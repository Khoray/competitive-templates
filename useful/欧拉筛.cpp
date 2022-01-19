const int N=1e7+5;
int pri[N / 5], notpri[N], prinum;

void init_pri() {
    for(int i = 2; i < N; i++) {
        if(!notpri[i]) pri[++prinum] = i;
        for(int j = 1; j <= prinum && pri[j] * i < N; j++) {
            notpri[pri[j] * i] = pri[j];
            if(i % pri[j] == 0) {
                break;
            }
        }
    }
}


// with phi 
const int N=1e7+5;
int pri[N / 5], notpri[N], prinum, phi[N];;

void init_pri() {
    for(int i = 2; i < N; i++) {
        if(!notpri[i]) pri[++prinum] = i;
        for(int j = 1; j <= prinum && pri[j] * i < N; j++) {
            notpri[pri[j] * i] = pri[j];
            if(i % pri[j] == 0) {
            	phi[pri[j] * i] = pri[j] * phi[i];
                break;
            }
            phi[pri[j] * i] = (pri[j] - 1) * phi[i];
        }
    }
}
