call 00UniServerApp-coordinator.cmd
call wait 5
call 01UniServerApp-usermanager.cmd
call wait 5
call 02UniServerApp-relaybalancer.cmd
call wait 5
call 02UniServerApp-relay.cmd
call wait 3
call 05UniServerApp-social_lobby.cmd
call wait 3
call 04UniServerApp-livemm.cmd
call wait 3
call 08UniServerApp-gateway.cmd
call wait 3
call 11UniServerApp-clusteradmin.cmd
call wait 3
call stat-pvx-start.cmd
call wait 3
call 99UniServerApp-login.cmd
