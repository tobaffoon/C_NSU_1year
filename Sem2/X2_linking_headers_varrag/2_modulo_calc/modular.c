long long MOD = 2;

long long pnorm(long long n){
    return (n % MOD + MOD) % MOD;
}

long long inv(long long a, long long b){
    static long long x=0, x1=0, y1=0;

    if(b == 0){
        x1 = 1;
        y1 = 0;
        return x;
    }
    else{
        inv(b, a % b);
    }
    x = y1;

    y1 = x1 - (a/b) * y1;
    x1 = x;

    return pnorm(x);
}

long long padd(long long a, long long b){
    return pnorm(a+b);
}

long long psub(long long a, long long b){
    return pnorm(a-b);
}

long long pmul(long long a, long long b){
    return pnorm(pnorm(a) * pnorm(b));
}

long long pdiv(long long a, long long b){
    return pmul(a, inv(pnorm(b), MOD));
}