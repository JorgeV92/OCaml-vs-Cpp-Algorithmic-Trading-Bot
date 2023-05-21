open Lwt
open Alpaca

(* let alpaca_endpoint = "https://paper-api.alpaca.markets"
let alpaca_key = "PKQ6ZYP9Q3HLDCVJB1TV"
let alpaca_secret = "wjobG7qsUWMRfXlg6uGpWjmKWdqUf2MdTavc4OWA"

let headers = Header.init ()
  |> fun h -> Header.add_list h [("APCA-API-KEY-ID", alpaca_key);
                                 ("APCA-API-SECRET-KEY", alpaca_secret)] *)

let rec take n list =
  match list with
  | [] -> []
  | h :: t -> if n = 0 then [] else h :: take (n-1) t


(* let moving_average n lst =
  let rec aux acc lst = match lst with
    | [] -> List.rev acc
    | _ when List.length acc < n -> aux (0.0 :: acc) (List.tl lst)
    | _ -> let avg = (List.fold_left (+.) 0.0 (take n lst)) /. (float_of_int n) in
           aux (avg :: acc) (List.tl lst)
  in aux [] lst *)

  let moving_average n lst =
    let rec aux acc lst = match lst with
      | [] -> List.rev acc
      | _ -> let avg = (List.fold_left (+.) 0.0 (take (min n (List.length lst)) lst)) /. (float_of_int (min n (List.length lst))) in
             aux (avg :: acc) (List.tl lst)
    in aux [] lst
  

(* let should_buy short_ma long_ma =
  List.hd short_ma > List.hd long_ma && List.hd (List.tl short_ma) < List.hd (List.tl long_ma)

let should_sell short_ma long_ma =
  List.hd short_ma < List.hd long_ma && List.hd (List.tl short_ma) > List.hd (List.tl long_ma) *)
(* 
let execute_strategy short_term long_term symbol data =
  let short_ma = moving_average short_term data in
  let long_ma = moving_average long_term data in
  if should_buy short_ma long_ma then place_order symbol 10 "buy" "market" "gtc"
  else if should_sell short_ma long_ma then place_order symbol 10 "sell" "market" "gtc"
  else Lwt.return (0, "") *)
(*     
  let execute_strategy short_term long_term symbol data =
      let _ = Lwt_io.printf "Running execute_strategy for symbol: %s\n" symbol in
      let short_ma = moving_average short_term data in
      let long_ma = moving_average long_term data in
      let _ = Lwt_io.printf "Short MA: %f, Long MA: %f\n" (List.hd short_ma) (List.hd long_ma) in
      if should_buy short_ma long_ma then begin
        Lwt_io.printf "Executing BUY strategy for symbol: %s\n" symbol >>= fun () ->
        place_order symbol 1 "buy" "market" "gtc"
      end else if should_sell short_ma long_ma then begin
        Lwt_io.printf "Executing SELL strategy for symbol: %s\n" symbol >>= fun () ->
        place_order symbol 1 "sell" "market" "gtc"
      end else Lwt.return (0, "") *)


  let execute_strategy short_term long_term symbol data =
    let _ = Lwt_io.printf "Running execute_strategy for symbol: %s\n" symbol in
    let short_ma = moving_average short_term data in
    let long_ma = moving_average long_term data in
    let _ = Lwt_io.printf "Short MA: %f, Long MA: %f\n" (List.hd short_ma) (List.hd long_ma) in
    (*
    if should_buy short_ma long_ma then begin
      Lwt_io.printf "Executing BUY strategy for symbol: %s\n" symbol >>= fun () ->
      place_order symbol 10 "buy" "market" "gtc"
    end else if should_sell short_ma long_ma then begin
      Lwt_io.printf "Executing SELL strategy for symbol: %s\n" symbol >>= fun () ->
      place_order symbol 10 "sell" "market" "gtc"
    end else Lwt.return (0, "")
    *)
    Lwt_io.printf "Executing BUY strategy for symbol: %s\n" symbol >>= fun () ->
    place_order symbol 3 "buy" "market" "gtc"

    
  

let parse_prices body =
    let json = Yojson.Basic.from_string body in
    let open Yojson.Basic.Util in
    let bars = json |> member "bars" |> to_list in
    let prices = bars |> List.map (fun obj -> 
      try obj |> member "c" |> to_float 
      with Type_error (_, _) -> float_of_int (obj |> member "c" |> to_int)) 
    in
    prices
  
  (* ... *)

  let _ = 
    Lwt_main.run (
      get_bars "MS"
      >>= fun (code, body, _) ->
      begin match code with
      | 200 -> 
        let prices = parse_prices body in
        (* Degugging check output of prices *)
        let _ = Lwt_io.printf "\nPrices: %s\n" (String.concat ", " (List.map string_of_float prices)) in
        execute_strategy 5 20 "MS" prices >>= fun _ -> Lwt.return (0, "")
      | _ -> Lwt.return (0, "Error")
      end
    )


  
  
  