(* The Lwt, Cohttp, and Cohttp_lwt_unix modules are opened to provide 
   concurrent I/O and HTTP client functionalities *)
open Lwt
open Cohttp
open Cohttp_lwt_unix
open Yojson.Basic.Util


(* Account Info from Alpaca functionality *)
let alpaca_endpoint = "https://paper-api.alpaca.markets"
let alpaca_key = "PKQ6ZYP9Q3HLDCVJB1TV"
let alpaca_secret = "wjobG7qsUWMRfXlg6uGpWjmKWdqUf2MdTavc4OWA"

let headers = Header.init ()
  |> fun h -> Header.add_list h [("APCA-API-KEY-ID", alpaca_key);
                                 ("APCA-API-SECRET-KEY", alpaca_secret)]

let get_account_info () =
  let uri = Uri.of_string (alpaca_endpoint ^ "/v2/account") in
  Client.call ~headers `GET uri
  >>= fun (res, body) ->
  let code = res |> Response.status |> Code.code_of_status in
  body |> Cohttp_lwt.Body.to_string >|= fun body ->
  (code, body)

let process_json json =
  let id = json |> member "id" |> to_string in
  let status = json |> member "status" |> to_string in
  (id, status)


  let run_account_info_of_user () =
    let thread =
      get_account_info ()
      >>= fun resp1 ->
      begin match resp1 with
      | (200, body) -> 
        print_endline ("Success: Full account info = " ^ body); 
        let json = Yojson.Basic.from_string body in 
        let (id, status) = process_json json in 
        print_endline ("ID = " ^ id ^ ", Status = " ^ status); 
        Lwt.return ()
      | _ -> print_endline "Error"; Lwt.return ()
      end
    in
    Lwt_main.run thread

  
(* End of account info functionality *)

(* START fetching market data and placing orders functionality. *)

let alpaca_endpoint_market = "https://data.alpaca.markets"

(* Function to get the bars (trading data) of a given stock symbol *)                            
let get_bars symbol =
  let uri = Uri.of_string (alpaca_endpoint_market ^ "/v2/stocks/" ^ symbol ^ "/bars") in
  let headers = Header.add headers "Content-Type" "application/json" in
  let query = [("start", "2013-05-15T09:30:00-04:00");
                ("end", "2023-05-15T16:00:00-04:00");
                ("timeframe", "1Hour"); (*  // changed from "1Min" to "1Hour, 1Day" *)
                ("limit", "1000")] in
  let uri = Uri.with_query' uri query in
  Client.call ~headers `GET uri
  >>= fun (res, body) ->
  let code = res |> Response.status |> Code.code_of_status in
  body |> Cohttp_lwt.Body.to_string >|= fun body ->
  (code, body, symbol)
                                  
let get_bars_multiple symbols =
  Lwt_list.map_s get_bars symbols

let get_bars_for_symbols symbols =
  let responses = Lwt_main.run (get_bars_multiple symbols) in
  List.iter (fun (code, body, symbol) ->
    match code with
    | 200 -> print_endline ("Success for " ^ symbol ^ ": " ^ body)
    | _ -> print_endline ("Error for " ^ symbol ^ ": code " ^ string_of_int code ^ ", body: " ^ body)
  ) responses
  
(* Function to place a new order on Alpaca's platform. *)
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
  
(* END fetching market data and placing orders. *)