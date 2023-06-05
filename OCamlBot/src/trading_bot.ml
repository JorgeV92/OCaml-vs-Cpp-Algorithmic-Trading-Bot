(* trading_bot.ml *)
open Alpaca
open Strategy
open Stock_data_processing


(* Function to prompt user for stock symbols *)
let get_user_symbols () =
  print_endline "Please enter the stock symbols you want to trade (separated by space):";
  flush stdout;
  let line = read_line () in  (* Read the input from the user *)
  String.split_on_char ' ' line  (* Split the line into a list of symbols *)

(* This is the main trading bot function *)
let run_trading_bot () =
    (* Initialize the bot *)
    run_account_info_of_user ();
  
    (* Get the stock symbols from the user *)
    let symbols = get_user_symbols () in

    (* let _ = get_bars_for_symbols symbols in *)
  
    (* Specify the short term and long term windows for our moving average strategy *)
    let short_term = 20 and long_term = 100 in

    (* Execute the strategy for each symbol *)
    List.iter (fun symbol -> 
      let _ = Strategy.run_strategy_for_symbol symbol short_term long_term in ()
    ) symbols;

    (* Save data to csv for each symbol *)
    List.iter (fun symbol ->
      let _ = Lwt_main.run (save_to_csv symbol short_term long_term) in ()
    ) symbols
    
(* Entry point *)
let () =
    run_trading_bot ();



