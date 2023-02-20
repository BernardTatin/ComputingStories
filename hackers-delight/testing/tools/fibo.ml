(*
 * fibo.ml
 *
 * I hoped ocaml gave me some overflow indications on integer operations...
 * but, no, there is nothing like that.
 *
 * ocaml works with 64 bits signed integers (at least on 64 bits processors)
 * BUT there is 1 bit used to differentiate pointers from integers
 * So, ocaml works on 63 bits signed arithmetic.
 *)


let fibo n =
    let rec inner_fib cpt n1 n2 =
       if cpt = n
       then n1 + n2
       else inner_fib (cpt + 1) n2 (n1 + n2)
    in
        if n < 2
        then n
        else inner_fib 2 0 1

let show_fibo n =
    let rec inner_show_fibo k =
        if k <= n
        then (
            Printf.printf ".  fibo %i = %i\n" k (fibo k);
            inner_show_fibo (k + 1)
        )
        else ()
    in
        inner_show_fibo 0;;

show_fibo 90;;
