#include <stdio.h>

class Fib
{
    public:
        Fib() {}
        ~Fib() {}

        int Compute(int n)
        {
            if (n <= 0)
                return 0;
            if (n <= 2)
                return 1;
            return Compute(n - 2) + Compute(n - 1);
        }

};

extern "C" int fib(int n) {
    return Fib().Compute(n);
}

int main() {
    printf("fib(42) = %d", fib(42));
}

