open Alpaca
open Strategy

let write_to_csv filename data =
  try
    let out_chan = open_out filename in
    let write_line line =
      output_string out_chan (String.concat "," line);
      output_char out_chan '\n' in
    List.iter write_line data;
    close_out out_chan
  with
  | Sys_error msg -> print_endline ("Can't write to file: " ^ msg)
  | _ -> print_endline "Unknown error"

let rec combine3 l1 l2 l3 = match l1, l2, l3 with
  | [], _, _ -> []
  | _, [], _ -> []
  | _, _, [] -> []
  | x::xs, y::ys, z::zs -> (x, y, z) :: combine3 xs ys zs

(* `drop n list` is a function that removes the first `n` elements from the list. *)
let rec drop n list = 
  if n <= 0 then list
  else match list with 
  | [] -> []
  | _ :: t -> drop (n-1) t

let save_to_csv symbol short_term_period long_term_period =
  let%lwt _, body, _ = get_bars symbol in
  let prices_and_dates = Strategy.parse_prices_and_dates body in
  let short_term_ma = Strategy.moving_average_tuple short_term_period prices_and_dates in
  let long_term_ma = Strategy.moving_average_tuple long_term_period prices_and_dates in
  let csv_data = combine3 prices_and_dates short_term_ma long_term_ma in
  let csv_data = List.map (fun ((date, price), (_, short_ma), (_, long_ma)) -> 
    [date; string_of_float price; string_of_float short_ma; string_of_float long_ma]
  ) csv_data in
  write_to_csv (symbol ^ ".csv") csv_data;
  Lwt.return_unit

  