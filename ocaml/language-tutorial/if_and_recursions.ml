(* for and while *)
let acc = ref 0;;

for i = 1 to 10 do
  acc := !acc + i
done

let () = assert (!acc = 55)
let count = ref 0;;

while !count < 10 do
  count := !count + 1
done

let () = assert (!count = 10)

(* looping over lists *)
let acc = ref 0
let ls = [ 1; 2; 3; 4 ]

let () =
  let f x = acc := !acc + x in
  List.iter f ls

let () = assert (!acc = 10)

let () =
  assert (
    let is_even i = i mod 2 = 0 in
    List.filter is_even ls = [ 2; 4 ])

let () = assert (List.mem 2 ls)
let sum = List.fold_left ( + ) 0
let product = List.fold_left ( * ) 1
let () = assert (sum ls = 10)
let () = assert (product ls = 24)

(* recursion *)
let rec range2 a b acc = if b < a then acc else range2 a (b - 1) (b :: acc)
let range a b = range2 a b []
let () = assert (range 0 5 = [ 0; 1; 2; 3; 4; 5 ])

(* mutable records *)
type name = { name : string; mutable access_count : int }

let curling_grad = { name = "Ryang Sohn"; access_count = 0 };;

curling_grad.access_count <- curling_grad.access_count + 1

let () = assert (curling_grad.access_count = 1)
let arr = Array.make 10 0;;

for i = 0 to Array.length arr - 1 do
  arr.(i) <- i
done

let () = assert (arr = [| 0; 1; 2; 3; 4; 5; 6; 7; 8; 9 |])

(* mutually recursive functions *)
let rec even n = match n with 0 -> true | x -> odd (x - 1)
and odd n = match n with 0 -> false | x -> even (x - 1)

let () = assert (even 1 = false)
let () = assert (odd 1)
let () = assert (even 42)
let () = assert (odd 42 = false)
