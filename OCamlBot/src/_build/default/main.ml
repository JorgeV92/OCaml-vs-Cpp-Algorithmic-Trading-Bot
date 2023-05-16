open Lwt
open Cohttp
open Cohttp_lwt_unix

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

let () =
  let resp = Lwt_main.run (get_account_info ()) in
  match resp with
  | (200, body) -> print_endline ("Success: " ^ body)
  | _ -> print_endline "Error"
