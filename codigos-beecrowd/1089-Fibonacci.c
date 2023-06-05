#include <stdio.h>

typedef struct {
  int result;
  int num_calls;
} FibResult;

FibResult fib(int n) {
  FibResult result;
  if (n == 0) {
    result.result = 0;
    result.num_calls = 0;
  } else if (n == 1) {
    result.result = 1;
    result.num_calls = 0;
  } else {
    FibResult fib_n_minus_1 = fib(n - 1);
    FibResult fib_n_minus_2 = fib(n - 2);
    result.result = fib_n_minus_1.result + fib_n_minus_2.result;
    result.num_calls = fib_n_minus_1.num_calls + fib_n_minus_2.num_calls + 2;
  }
  return result;
}

int main() {
  int N, X;
  scanf("%d", &N);

  for (int i = 0; i < N; i++) {
    scanf("%d", &X);
    FibResult result = fib(X);
    printf("fib(%d) = %d calls = %d\n", X, result.num_calls, result.result);
  }

  return 0;
}
