(* cons *)
let () = assert (1 :: [ 2; 3; 4 ] = [ 1; 2; 3; 4 ])

(* pattern matching *)
let rec sum u = match u with [] -> 0 | x :: v -> x + sum v
let () = assert (sum [ 1; 2; 3 ] = 6)
let rec length u = match u with [] -> 0 | _ :: v -> 1 + length v
let () = assert (length [ 1; 2; 3 ] = 3)

(* higher order function *)
let rec map f u = match u with [] -> [] | x :: v -> f x :: map f v

let () =
  assert (map length [ [ 1; 2 ]; [ 3; 4; 5 ]; []; [ 7 ] ] = [ 2; 3; 0; 1 ])

(* unpacking optional *)
let f opt =
  match opt with None -> None | Some None -> None | Some (Some x) -> Some x

let () = assert (f None = None)
let () = assert (f (Some None) = None)
let () = assert (f (Some (Some 1)) = Some 1)

(* pattern matching string *)
let g x =
  match x with "foo" -> 1 | "bar" -> 2 | "baz" -> 3 | "qux" -> 4 | _ -> 0

let () = assert (g "foo" = 1)
let () = assert (g "curling_grad" = 0)

(* variant *)
type primary_color = Red | Green | Blue

let color_to_rgb color =
  match color with
  | Red -> (0xff, 0, 0)
  | Green -> (0, 0xff, 0)
  | Blue -> (0, 0, 0xff)

let () = assert (color_to_rgb Red = (0xff, 0, 0))

(* record *)
type person = { first_name : string; surname : string; age : int }

let curling_grad = { first_name = "Ryang"; surname = "Sohn"; age = 20 }
let () = assert (curling_grad.age = 20)
