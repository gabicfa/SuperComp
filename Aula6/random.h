// double drandom();
// void seed(double low_in, double hi_in);

class random
{

private:

    long mult, add, pmod, random_last;
    double random_low, random_hi;

public:
    random(long mult, long pmod, long random_last, double random_low, double random_hi);
    // ~random();
    double get_next_random();
};

