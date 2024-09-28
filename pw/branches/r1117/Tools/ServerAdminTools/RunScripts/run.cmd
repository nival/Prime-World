call 00UniServerApp-coordinator.cmd
call wait 5
call 01UniServerApp-usermanager.cmd
call wait 5
call 02UniServerApp-relaybalancer.cmd
call wait 5
call 02UniServerApp-relay.cmd
call wait 5
call 03UniServerApp-chat.cmd
call wait 3
call 05UniServerApp-lobby.cmd
call wait 3
call 05UniServerApp-social_lobby.cmd
call wait 3
call 04UniServerApp-livemm.cmd
call wait 3
call 06UniServerApp-gamesvc.cmd
call wait 3
call stat-pvx-start.cmd
call wait 3
call stat-social-start.cmd
call wait 3
call 07UniServerApp-gamebalancer.cmd
call wait 3
call 08UniServerApp-gateway.cmd
call wait 3
call 10UniServerApp-monitoring.cmd
call wait 3
call monitoring-start.cmd
call wait 3
call 11UniServerApp-clusteradmin.cmd
call wait 3
call 12UniServerApp-roll.cmd
call wait 3
call 13UniServerApp-rollbalancer.cmd
call wait 3
call 99UniServerApp-login.cmd
