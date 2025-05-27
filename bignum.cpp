bool print_mode = false; // false = normal, true = e

struct bignum{
    long double base; //1 <= base < 10
    long long exp;

    explicit bignum(long double _b = 0.0, long long _e = 0){
        base = _b, exp = _e;
        norm();
    }

    void norm(){
        if(base == 0){
            exp = 0;
            return ;
        }
        while(abs(base) >= 10){
            base /= 10.0;
            exp++;
        }
        while(abs(base) < 1){
            base *= 10.0;
            exp--;
        }
    }

    //printing the bignum
    friend ostream& operator<<(ostream& os, bignum const& n){
        os << setprecision(10) << n.base << (print_mode? "e":" * 10^") << n.exp;
        return os;
    }

    //addition
    bignum operator+(const bignum& o) const {
        if(exp > o.exp){
            return bignum(base + o.base / (long double)pow(10.0, exp - o.exp), exp);
        }
        return bignum(base / (long double)pow(10.0, o.exp - exp) + o.base, o.exp);
    }

    //subtraction
    bignum operator-(const bignum &o) const{
        if(exp > o.exp){
            return bignum(base - o.base / (long double)pow(10.0, exp - o.exp), exp);
        }
        return bignum(base / (long double)pow(10.0, o.exp - exp) - o.base, o.exp);
    }

    //multiplication
    bignum operator*(const bignum &o) const{
        return bignum(base * o.base, exp + o.exp);
    }

    //division
    bignum operator/(const bignum &o) const{
        return bignum(base / o.base, exp - o.exp);
    }
};

//factorial     
bignum factorial(long long x){
    bignum y(1, 0);
    while(x > 0){
        y = y * bignum(x, 0);
        x--;
    }
    return y;
}

//square root
bignum sqrt(const bignum &x){
    if(x.exp % 2 == 1){
        return bignum(sqrt(x.base) * sqrt(10), x.exp/2);
    }
    return bignum(sqrt(x.base), x.exp/2);
}

//raise to power of integer
bignum pow(bignum x, long long y){
    bignum r(1, 0);
    while(y){
        if(y & 1) r = r * x;
        x = x * x;
        y >>= 1;
    }
    return r;
}
