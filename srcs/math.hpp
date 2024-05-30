#pragma once

#include <vector>
#include <algorithm>

inline unsigned int factorial(unsigned int n)
{
  return n <= 1 ? 1 : n * factorial(n - 1);
}

inline unsigned int choose(unsigned int n, unsigned int k)
{
  return (n < k)
    ? 0
    : factorial(n) / (factorial(n - k) * factorial(k));
}

inline unsigned int pick(unsigned int n, unsigned int k)
{
  return factorial(n) / factorial(n - k);
}

inline int binomialCoefficient(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    int num = 1, denom = 1;
    for (int i = 0; i < k; ++i) {
        num *= (n - i);
        denom *= (i + 1);
    }
    return num / denom;
}