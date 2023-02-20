;;
;; fibo.scm
;;
;; computing first Fibonacchi numbers with Scheme big numbers
;; cf https://en.wikipedia.org/wiki/Fibonacci_number
;;
;; works well with chezscheme, guile or gauche:
;; $ scheme -q fibo.scm
;; $ guile -q fibo.scm
;; $ gosh -q fibo.scm
;;

(define fibo
  (lambda (N)
    (define inner_fibo
      (lambda (cpt n1 n2)
        (if (= cpt N)
          (+ n1 n2)
          (inner_fibo (+ cpt 1) n2 (+ n1 n2)))))
              (cond
                ((= N 0) 0)
                ((= N 1) 1)
                (#t (inner_fibo 2 0 1)))
              ))

(define show-fibo
  (lambda(N)
    (define ishow (lambda(k)
               (when (<= k N)
                 (format #t "fibo ~a = ~a~%" k (fibo k))
                 (ishow (+ k 1))) ))
              (ishow 0)
              ))

;; in C, with 128 bits the greatest computable fibo is (fibo 183)
;; after, it's overflow
(show-fibo 183)
(exit)
