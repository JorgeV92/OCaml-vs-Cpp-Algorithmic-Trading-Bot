(* The Lwt, Cohttp, and Cohttp_lwt_unix modules are opened to provide 
   concurrent I/O and HTTP client functionalities *)
open Lwt
open Cohttp
open Cohttp_lwt_unix

(* Contains functions for interacting with the Alpaca API, including fetching 
   market data and placing orders. *)

let alpaca_endpoint = "https://data.alpaca.markets"
let alpaca_key = "PKQ6ZYP9Q3HLDCVJB1TV"
let alpaca_secret = "wjobG7qsUWMRfXlg6uGpWjmKWdqUf2MdTavc4OWA"

let headers = Header.init ()
  |> fun h -> Header.add_list h [("APCA-API-KEY-ID", alpaca_key);
                                 ("APCA-API-SECRET-KEY", alpaca_secret)]

(* Function to get the bars (trading data) of a given stock symbol *)                            
let get_bars symbol =
  let uri = Uri.of_string (alpaca_endpoint ^ "/v2/stocks/" ^ symbol ^ "/bars") in
  let headers = Header.add headers "Content-Type" "application/json" in
  let query = [("start", "2023-04-01T09:30:00-04:00");
                ("end", "2023-05-15T16:00:00-04:00");
                ("timeframe", "1Min");
                ("limit", "100")] in
  let uri = Uri.with_query' uri query in
  Client.call ~headers `GET uri
  >>= fun (res, body) ->
  let code = res |> Response.status |> Code.code_of_status in
  body |> Cohttp_lwt.Body.to_string >|= fun body ->
  (code, body, symbol)
                                  
let get_bars_multiple symbols =
  Lwt_list.map_s get_bars symbols

let exe () =
  let symbols = ["MS"; "MSFT"; "AAPL"] in
  let responses = Lwt_main.run (get_bars_multiple symbols) in
  List.iter (fun (code, body, symbol) ->
    match code with
    | 200 -> print_endline ("Success for " ^ symbol ^ ": " ^ body)
    | _ -> print_endline ("Error for " ^ symbol ^ ": code " ^ string_of_int code ^ ", body: " ^ body)
  ) responses

(* Function to place a new order on Alpaca's platform. The function accepts the stock symbol, 
   quantity of shares, side (buy or sell), type of order (limit or market), and time in force 
   for the order. It sends a POST request to Alpaca's order API endpoint with these parameters. 
   The function then returns the status code and body of the server's response. *)
let place_order symbol qty side type_ time_in_force =
    let uri = Uri.of_string ("https://paper-api.alpaca.markets/v2/orders") in
    let headers = Header.add headers "Content-Type" "application/json" in
    let body = `Assoc [("symbol", `String symbol);
                       ("qty", `Int qty);
                       ("side", `String side);
                       ("type", `String type_);
                       ("time_in_force", `String time_in_force)] 
               |> Yojson.Basic.to_string in
    print_endline ("Quantity: " ^ (string_of_int qty));  (* Print qty *)
    Client.call ~headers ~body:(`String body) `POST uri
    >>= fun (res, body) ->
    let code = res |> Response.status |> Code.code_of_status in
    body |> Cohttp_lwt.Body.to_string >|= fun body ->
    (code, body)
  
(* let () =
    let resp = Lwt_main.run (place_order "AAPL" 1 "sell" "market" "gtc") in
    match resp with
    | (200, body) -> print_endline ("Success: " ^ body)
    | (code, body) -> print_endline ("Error: code " ^ string_of_int code ^ ", body: " ^ body)
   *)
