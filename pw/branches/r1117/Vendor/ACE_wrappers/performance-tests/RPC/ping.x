/*
 * $Id: ping.x 80826 2008-03-04 14:51:23Z wotte $
 */

/*
 * A small program to test RPC round-trip delays.
 */
program PINGPROG {
  version PINGVERS {
    int PING (int) = 1;
  } = 1;
} = 0x20000001;
