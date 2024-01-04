(* strings *)
let () = assert ("hell" ^ " " ^ "world!" = "hell world!")
let () = assert ("hell world".[3] = 'l')

(* byte sequences *)
let () = assert ("hello" |> String.to_bytes |> Bytes.to_string = "hello")
let () = assert ("hello" |> Bytes.of_string |> Bytes.to_string = "hello")

(* arrays *)
let () = assert ([| 1; 2; 3 |].(1) = 2)
let letter = [| 'v'; 'x'; 'y'; 'z' |];;

letter.(2) <- 'F'

let () = assert (letter.(2) = 'F')

(* tuples *)
let () = assert (fst (3, 'g') = 3)
let () = assert (snd (3, 'g') = 'g')

(* variants *)
type commit =
  | Hash of string
  | Tag of string
  | Branch of string
  | Head
  | Fetch_head
  | Orig_head
  | Merge_head

let commit_to_string = function
  | Hash sha -> sha
  | Tag name -> name
  | Branch name -> name
  | Head -> "HEAD"
  | Fetch_head -> "FETCH_HEAD"
  | Orig_head -> "ORIG_HEAD"
  | Merge_head -> "MERGE_HEAD"

let () = assert (commit_to_string (Hash "deadbeef") = "deadbeef")

(* recursive variants *)
type json =
  | Null
  | Bool of bool
  | Int of int
  | Float of float
  | String of string
  | Array of json list
  | Object of (string * json) list

let obj =
  Object
    [
      ("a", Null);
      ("b", Bool false);
      ("c", Int 42);
      ("d", Array [ Int 0; Int 1; Int 2 ]);
      ("e", Object [ ("f", String "hell world!"); ("g", Float 3.14) ]);
    ]

let rec has_field name = function
  | Array u -> List.fold_left (fun b obj -> b || has_field name obj) false u
  | Object u ->
      List.fold_left
        (fun b (key, obj) -> b || key = name || has_field name obj)
        false u
  | _ -> false

let () = assert (has_field "a" obj)

type path_elem = Key of string | Index of int

let rec access_field path obj =
  match (path, obj) with
  | [], _ -> Some obj
  | Key k :: u, Object v -> (
      match List.find_opt (fun field -> fst field = k) v with
      | Some field -> access_field u (snd field)
      | None -> None)
  | Index i :: u, Array v -> (
      match List.nth_opt v i with Some w -> access_field u w | None -> None)
  | _ -> None

let () = assert (access_field [ Key "d"; Index 1 ] obj = Some (Int 1))

let () =
  assert (access_field [ Key "e"; Key "f" ] obj = Some (String "hell world!"))

let () = assert (access_field [ Key "x" ] obj = None)

(* polymorphic data types *)
type 'a tree = Leaf | Node of 'a * 'a tree * 'a tree

let rec sum = function
  | Leaf -> 0
  | Node (x, left, right) -> x + sum left + sum right

let () = assert (sum Leaf = 0)
let () = assert (sum (Node (1, Leaf, Node (2, Leaf, Leaf))) = 3)

let rec map f = function
  | Leaf -> Leaf
  | Node (x, left, right) -> Node (f x, map f left, map f right)

let () =
  assert (
    map List.length (Node ([ 0; 1 ], Leaf, Node ([ 2; 3; 4 ], Leaf, Leaf)))
    = Node (2, Leaf, Node (3, Leaf, Leaf)))

(* example: mathematical expressions *)
type expr =
  | Plus of expr * expr
  | Minus of expr * expr
  | Times of expr * expr
  | Divide of expr * expr
  | Var of string

let rec to_string = function
  | Plus (e1, e2) -> "(" ^ to_string e1 ^ " + " ^ to_string e2 ^ ")"
  | Minus (e1, e2) -> "(" ^ to_string e1 ^ " - " ^ to_string e2 ^ ")"
  | Times (e1, e2) -> "(" ^ to_string e1 ^ " * " ^ to_string e2 ^ ")"
  | Divide (e1, e2) -> "(" ^ to_string e1 ^ " / " ^ to_string e2 ^ ")"
  | Var v -> v

let test_expr = Times (Var "n", Plus (Var "x", Var "y"))
let () = assert (to_string test_expr = "(n * (x + y))")

let rec distrib = function
  | Times (e1, Plus (e2, e3)) ->
      Plus (Times (distrib e1, distrib e2), Times (distrib e1, distrib e3))
  | Times (Plus (e1, e2), e3) ->
      Plus (Times (distrib e1, distrib e3), Times (distrib e2, distrib e3))
  | Plus (e1, e2) -> Plus (distrib e1, distrib e2)
  | Minus (e1, e2) -> Minus (distrib e1, distrib e2)
  | Times (e1, e2) -> Times (distrib e1, distrib e2)
  | Divide (e1, e2) -> Divide (distrib e1, distrib e2)
  | Var v -> Var v

let () = assert (test_expr |> distrib |> to_string = "((n * x) + (n * y))")

let top_factorize = function
  | Plus (Times (e1, e2), Times (e3, e4)) when e1 = e3 ->
      Times (e1, Plus (e2, e4))
  | Plus (Times (e1, e2), Times (e3, e4)) when e2 = e4 ->
      Times (Plus (e1, e3), e4)
  | e -> e

let () =
  assert (test_expr |> distrib |> top_factorize |> to_string = "(n * (x + y))")
