(* partial applications *)
let plus a b = a + b
let f = plus 2
let () = assert (f 3 = 5)

(* laziness *)
let lazy_expr = lazy (1 / 0)
let const_three _ = 3
let () = assert (const_three lazy_expr = 3)
