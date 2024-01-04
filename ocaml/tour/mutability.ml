(* reference *)
let r = ref 0
let () = assert (!r = 0);;

r := 42

let () = assert (!r = 42)
