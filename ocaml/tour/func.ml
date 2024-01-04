(* ordinary functions *)
let square x = x * x
let () = assert (square 50 = 2500)

(* anonymous functions *)
let () = assert ((fun x -> x * x) 50 = 2500)

(* currying *)
let cat a b = a ^ " " ^ b
let () = assert (cat "ha" "ha" = "ha ha")
let cat_hi = cat "hi"
let () = assert (cat_hi "curling_grad" = "hi curling_grad")

(* higher-order functions *)
let () = assert (List.map (fun x -> x * x) [ 0; 1; 2; 3 ] = [ 0; 1; 4; 9 ])

(* recursive functions *)
let rec range lo hi = if lo > hi then [] else lo :: range (lo + 1) hi
let () = assert (range 2 5 = [ 2; 3; 4; 5 ])
