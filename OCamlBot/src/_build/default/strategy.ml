open Lwt
open Alpaca

module Strategy = struct
  let rec take n list =
    match list with
    | [] -> []
    | h :: t -> if n = 0 then [] else h :: take (n-1) t

  let moving_average n lst =
    let rec aux acc lst = match lst with
      | [] -> List.rev acc
      | _ -> let avg = (List.fold_left (+.) 0.0 (take (min n (List.length lst)) lst)) /. (float_of_int (min n (List.length lst))) in
              aux (avg :: acc) (List.tl lst)
    in aux [] lst

  let moving_average_tuple n lst =
    let rec aux acc dates prices = match prices with
      | [] -> List.rev acc
      | _ -> 
        let avg = (List.fold_left (+.) 0.0 (take (min n (List.length prices)) prices)) /. (float_of_int (min n (List.length prices))) in
        let date = match dates with | hd::_ -> hd | [] -> failwith "No date available" in
        aux ((date, avg) :: acc) (List.tl dates) (List.tl prices)
    in 
    let dates, prices = List.split lst in
    aux [] dates prices

  (* let rec should_buy short_ma long_ma = match short_ma, long_ma with
    | [], _ | _, [] -> false
    | sh :: st, lh :: lt -> 
        if sh > lh && List.hd st < List.hd lt then true
        else should_buy st lt

  let rec should_sell short_ma long_ma = match short_ma, long_ma with
    | [], _ | _, [] -> false
    | sh :: st, lh :: lt -> 
        if sh < lh && List.hd st > List.hd lt then true
        else should_sell st lt *)

  let rec should_buy short_ma long_ma = match short_ma, long_ma with
    | [], _ | _, [] -> false
    | sh :: st, lh :: lt -> 
        if sh > lh then true
        else should_buy st lt
  
  let rec should_sell short_ma long_ma = match short_ma, long_ma with
    | [], _ | _, [] -> false
    | sh :: st, lh :: lt -> 
        if sh < lh then true
        else should_sell st lt
      

    let print_float_list l =
      Lwt_list.iter_s (fun x -> Lwt_io.printf "%f " x) l 
    
    let execute_strategy short_term long_term symbol data =
      let _ = Lwt_io.printf "Running execute_strategy for symbol: %s\n" symbol in
      let short_ma = moving_average short_term data in
      let long_ma = moving_average long_term data in
      (* let _ = Lwt_io.printf "Short MA: " >>= fun () -> print_float_list short_ma in *)
      (* let _ = Lwt_io.printf "\nLong MA: " >>= fun () -> print_float_list long_ma in *)
      if should_buy short_ma long_ma then begin
        Lwt_io.printf "Executing BUY strategy for symbol: %s\n" symbol >>= fun () ->
        place_order symbol 1 "buy" "market" "gtc"
      end else if should_sell short_ma long_ma then begin
        Lwt_io.printf "Executing SELL strategy for symbol: %s\n" symbol >>= fun () ->
        place_order symbol 1 "sell" "market" "gtc"
      end else Lwt.return (0, "")

    let parse_prices_and_dates body =
      let json = Yojson.Basic.from_string body in
      let open Yojson.Basic.Util in
      let bars = json |> member "bars" |> to_list in
      let prices_and_dates = bars |> List.map (fun obj -> 
        let price = try obj |> member "c" |> to_float 
                    with Type_error (_, _) -> float_of_int (obj |> member "c" |> to_int) in
        let date = obj |> member "t" |> to_string in
        (date, price)) 
      in
      prices_and_dates


  let parse_prices body =
      let json = Yojson.Basic.from_string body in
      let open Yojson.Basic.Util in
      let bars = json |> member "bars" |> to_list in
      let prices = bars |> List.map (fun obj -> 
        try obj |> member "c" |> to_float 
        with Type_error (_, _) -> float_of_int (obj |> member "c" |> to_int)) 
      in
      prices

  let run_strategy_for_symbol symbol short_term long_term =
    Lwt_main.run (
      get_bars symbol
      >>= fun (code, body, _) ->
      begin match code with
      | 200 -> 
        let prices = parse_prices body in
        (* Debugging check output of prices *)
        (* let _ = Lwt_io.printf "\nPrices: %s\n" (String.concat ", " (List.map string_of_float prices)) in *)
        execute_strategy short_term long_term symbol prices >>= fun _ -> Lwt.return (0, "")
      | _ -> Lwt.return (0, "Error")
      end
    )

end

  
  
  