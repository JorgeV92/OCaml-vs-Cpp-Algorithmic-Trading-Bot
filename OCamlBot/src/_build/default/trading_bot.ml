(* trading_bot.ml *)
open Alpaca
open Strategy
open Stock_data_processing


(* Function to prompt user for stock symbols *)
let get_user_symbols () =
  print_endline "\nPlease enter the stock symbols you want to trade (separated by space):";
  flush stdout;
  let line = read_line () in  (* Read the input from the user *)
  String.split_on_char ' ' line  (* Split the line into a list of symbols *)


(* Function to prompt the user for an action option *)
let prompt_for_options () =
  print_endline "\nWhat would you like to do?";
  print_endline "1. Check account information";
  print_endline "2. Run the strategy";
  print_endline "3. Save data to a CSV file";
  print_endline "4. Exit";
  flush stdout;
  read_line ()
(* Specify the short term and long term windows for our moving average strategy : The Golden Cross*)
let short_term = 50 and long_term = 200 

(* This is the main trading bot function *)
let rec run_trading_bot () =
  (* Ask the user what they want to do *)
  let option = prompt_for_options () in

  match option with
  | "1" -> (* Check account information *)
      run_account_info_of_user ();
      run_trading_bot ()
  | "2" -> (* Run the strategy *)

      (* Get the stock symbols from the user *)
      let symbols = get_user_symbols () in

      (* Execute the strategy for each symbol *)
      List.iter (fun symbol -> 
          let _ = Strategy.run_strategy_for_symbol symbol short_term long_term in ()
      ) symbols;
      run_trading_bot ()
  | "3" -> (* Save data to CSV *)
      (* Get the stock symbols from the user *)
      let symbols = get_user_symbols () in

      (* Save data to csv for each symbol *)
      List.iter (fun symbol ->
          let _ = Lwt_main.run (save_to_csv symbol short_term long_term) in ()
      ) symbols;
      run_trading_bot ()
  | "4" -> (* Exit *)
      print_endline "Goodbye!";
  | _ -> 
      print_endline "Invalid option selected.";
      run_trading_bot ()
    
(* Entry point *)
let () =
    print_endline "\n\nGreetings, Investor!";
    print_endline "I'm WALL-E, your trusted algorithmic trading assistant.";
    print_endline "I'm fascinated by patterns and numbers, especially those hidden within the financial markets.";
    print_endline "Ready to uncover some promising opportunities?";
    print_endline "Just tell me which stocks has caught your eye, and together, we can make those numbers work in our favor!";  
    run_trading_bot ();
