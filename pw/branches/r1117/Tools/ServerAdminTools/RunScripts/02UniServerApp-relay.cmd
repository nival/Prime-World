start UniServerApp-relay.exe relay
call wait 3
start UniServerApp-relay.exe relay --svcpath ""
call wait 3
start UniServerApp-relay.exe relay --config relay_secondary.cfg
call wait 3
start UniServerApp-relay.exe relay --svcpath "" --config relay_secondary.cfg
