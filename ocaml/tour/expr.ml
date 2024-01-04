let () = assert (50 * 50 = 2500)

(* lists *)
let u = [ 1; 2; 3; 4 ]
let () = assert (List.length u = 4)
let () = assert (List.length (9 :: u) = 5)

(* if then else *)
let () = assert ((2 * if "hello" = "world" then 3 else 5) = 10)

(* let binding *)
let () =
  assert (
    (let y = 50 in
     y * y)
    = 2500)

let () =
  assert (
    (let a = 1 in
     let b = 2 in
     a + b)
    = 3)

let () = assert ("hello" = "hi" = false)
