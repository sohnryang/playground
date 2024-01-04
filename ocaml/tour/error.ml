(* exception *)
let id_42 n = if n <> 42 then raise (Failure "Wrong") else n
let () = assert (id_42 42 = 42)
let () = assert ((try id_42 0 with Failure _ -> 0) = 0)

(* result *)
let id_42_res n = if n <> 42 then Error "Wrong" else Ok n
let () = assert (id_42_res 42 = Ok 42)
let () = assert (id_42_res 0 = Error "Wrong")
