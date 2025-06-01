const bool print_mode = false; // false = normal, true = e

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
        if(abs(base) < 1){
            int inv = 10.0/abs(base);
            int cnt = floor(log10(inv));
            base *= pow(10.0, cnt);
            exp-=cnt;
        }
        if(abs(base) >= 10){
            int cnt = floor(log10(base));
            base /= pow(10.0, cnt);
            exp+=cnt;
        }
    }
    
    //printing the bignum
    friend ostream& operator<<(ostream& os, bignum const& n){
        os << setprecision(9) << n.base << (print_mode? "e":" * 10^") << n.exp;
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

    //comparison operators
    bool operator<(const bignum &o) const{
        if(base == 0 || o.base == 0) return base < o.base;
        return (exp < o.exp || (exp == o.exp && base < o.base));
    }

    bool operator<=(const bignum &o) const{
        if(base == 0 || o.base == 0) return base <= o.base;
        return (exp < o.exp || (exp == o.exp && base <= o.base));
    }

    bool operator>(const bignum &o) const{
        if(base == 0 || o.base == 0) return base > o.base;
        return (exp > o.exp || (exp == o.exp && base > o.base));
    }

    bool operator>=(const bignum &o) const{
        if(base == 0 || o.base == 0) return base >= o.base;
        return (exp > o.exp || (exp == o.exp && base >= o.base));
    }

    bool operator==(const bignum &o) const{
        if(base == 0 || o.base == 0) return base == o.base;
        return base == o.base && exp == o.exp;
    }
};

//absolute value
bignum abs(const bignum &x){
    return bignum(abs(x.base), x.exp);
}

//factorial     
bignum fact(long long x){
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

//log base y of x
bignum log(const bignum &x, const bignum &y){
    return bignum((log10(x.base) + x.exp)/(log10(y.base) + y.exp), 0);
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

//raise to power of bignum (base > 0)
bignum powd(const bignum &x, const bignum &y){
    if(y <= bignum(10, 0)){
        long double nx_base = pow(x.base, y.base);
        long double nx_exp = x.exp * y.base;
        nx_base *= pow(10, nx_exp - floor(nx_exp));
        nx_exp = floor(nx_exp);
        return bignum(nx_base, nx_exp);
    } 
    return powd(x, y/bignum(2, 0)) * powd(x, y/bignum(2, 0));
}
