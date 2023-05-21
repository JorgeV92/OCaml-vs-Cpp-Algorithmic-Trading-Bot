open Lwt
open Cohttp
open Cohttp_lwt_unix
open Yojson.Basic.Util

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
  (code, body)

  let process_json json =
    let id = json |> member "id" |> to_string in
    let status = json |> member "status" |> to_string in
    (id, status)
  

let () =
  let thread =
    get_account_info ()
    >>= fun resp1 ->
    begin match resp1 with
    | (200, body) -> 
      let json = Yojson.Basic.from_string body in 
      let (id, status) = process_json json in 
      print_endline ("Success: ID = " ^ id ^ ", Status = " ^ status); 
      Lwt.return ()
    | _ -> print_endline "Error"; Lwt.return ()
    end
    >>= fun () -> get_bars "AAPL"
    >>= fun resp2 ->
    begin match resp2 with
    | (200, body) -> print_endline ("Success: " ^ body); Lwt.return ()
    | _ -> print_endline "Error"; Lwt.return ()
    end
  in
  let _ = Lwt_main.run thread in
  ()
  
  