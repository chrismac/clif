-module(clif).

-export([init/0,
         cl_info/0]).

init() ->
  erlang:load_nif("./ebin/clif", 0).

cl_info() ->
  {error, nif_library_not_loaded}.
