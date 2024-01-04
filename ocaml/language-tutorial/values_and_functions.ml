(* pattern matching in definitions *)
let x, y = List.split [ (1, 2); (3, 4); (5, 6); (7, 8) ]
let () = assert (x = [ 1; 3; 5; 7 ])
let () = assert (y = [ 2; 4; 6; 8 ])

(* pattern matching on records *)
type name = { first : string; last : string }

let curling_grad = { first = "Ryang"; last = "Sohn" }
let { first; last = l } = curling_grad
let () = assert (first = "Ryang")
let () = assert (l = "Sohn")

(* application operator *)
let () = assert (int_of_float @@ sqrt @@ float_of_int @@ int_of_string "81" = 9)

(* pipe operator *)
let () =
  assert ("81" |> int_of_string |> float_of_int |> sqrt |> int_of_float = 9)

(* local functions *)
let () =
  assert (
    let sq x = x * x in
    sq 7 * sq 7 = 2401)

(* closures *)
let j = 2 * 3
let k x = x * j
let () = assert (k 7 = 42)
let j = 7
let () = assert (k 7 = 42)

(* recursive functions *)
let rec fibo n = if n <= 1 then n else fibo (n - 1) + fibo (n - 2)

let () =
  assert (
    List.init 10 Fun.id |> List.map fibo = [ 0; 1; 1; 2; 3; 5; 8; 13; 21; 34 ])

let rec fib_loop m n i = if i = 0 then m else fib_loop n (n + m) (i - 1)
let fib = fib_loop 0 1

let () =
  assert (
    List.init 10 Fun.id |> List.map fib = [ 0; 1; 1; 2; 3; 5; 8; 13; 21; 34 ])
