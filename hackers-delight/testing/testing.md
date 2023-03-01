# Testing

## Fibonacci numbers and addition overflow

I choose them to test overflow addition because the grow quickly without too much lines of code. The files involved in this test are:

- `ois-fibo.txt`, from [OIS](https://oeis.org/A000045/list), with the Fibonacci numbers from 0 to 40, it gives a reference.
- `fibo.scm`, some Scheme code which compute these numbers from 0 to 184. Some Scheme environments have *big numbers*, so it's easy to get Fibonacci numbers, factorials on great values very easily.
- `fibo.ml`, an *OCaml* script to make these calculations. I hoped to find some overflow detection with *OCaml*, but it is not the case. This language use a bit to differentiate pointers from integers so the integer arithmetic on 64 bits processor is limited to 63 bits.
- `sai-maths.c`, the C source code to compute these numbers with a detection of overflow.

### the Scheme code

The following environments are easy to use:

- [ChezScheme environment](https://github.com/cisco/ChezScheme),
- [Gauche](http://practical-scheme.net/gauche/index.html), 
- [Guile](https://www.gnu.org/software/guile/),

All of these have a `format` function by default. You have to run one of these commands:

```sh
$ scheme -q fibo.scm
$ guile -q fibo.scm
$ gosh -q fibo.scm
```



### the OCaml code

Just run:

```sh
$ ocaml fibo.ml
```



### the C code

Just modify the `main` function in the `main.c` source file:

```C

int main() {
    test_fibo();
    return 0;
}
```

Ensure to define the `BITS` in `safe_int_arith.h` macro to the good value.

### C, tail recursion and performances

The main function to compute these numbers, `sa_fibo` , is written in imperative mode. The function `sa_fibo_r` use an utility function which is tail recursive. With *gcc*, `sa_fibo_r` works well with an optimization level of 1 (option `-O`) but fail with higher levels. With `clang`, even with `-O3`, `sa_fibo_r` runs well and even runs 5% faster than `sa_fibo` with `-O3`.