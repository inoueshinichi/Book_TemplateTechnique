#include "macro_max.hpp"

#include <cstdio>
#include <iostream>

using namespace std;

// 宣言
declare(MAX, int)
declare(MAX, double)

// 実装
implement(MAX, int)
implement(MAX, double)

int main(int argc, char** argv)
{
    cout << "========== ch1 : macro max ==========" << endl;
    int i = 0;
    int j = 2;
    double u = 1.23;
    double v = 0.12;

    printf("MAX(%d,%d) = %d\n", i, j, MAX(int)(i, j));
    printf("MAX(%f,%f) = %f\n", u, v, MAX(double)(u, v));

    return 0;
}