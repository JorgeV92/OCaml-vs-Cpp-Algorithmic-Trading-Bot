open Alpaca
open Strategy

(* Test Account info works properly. *)
let () = 
  run_account_info_of_user ()

(* Test for correctly placing a sell option. *)
let () =
  let resp = Lwt_main.run (place_order "AAPL" 1 "sell" "market" "gtc") in
  match resp with
  | (200, body) -> print_endline ("Success: " ^ body)
  | (code, body) -> print_endline ("Error: code " ^ string_of_int code ^ ", body: " ^ body)

(* Test strategy *)
let () =
   Strategy.run_strategy_for_symbol "MS" 5 20


