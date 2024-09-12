start UniServerApp-livemm.exe livemmaking*13 --mm_modes dev
call wait 1
start UniServerApp-livemm.exe livemmaking*12 --mm_modes dev
call wait 1
for /L %%I in (1,1,21) do call 04UniServerApp-livemm-inner.cmd %%I
