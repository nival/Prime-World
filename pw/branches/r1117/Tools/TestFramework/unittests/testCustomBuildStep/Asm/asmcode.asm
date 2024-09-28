.386
PUBLIC    _simple
_TEXT     SEGMENT
_x$ = 8
_y$ = 12
_temp$ = -4
_simple PROC NEAR
     push ebp
     mov  ebp, esp
     sub  esp, 4

     mov  eax, DWORD PTR _x$[ebp]
     shl  eax,1
     mov  DWORD PTR _temp$[ebp], eax
     shl  eax,1

     mov  ecx, DWORD PTR _y$[ebp]
     mov  edx, DWORD PTR _temp$[ebp]
     mov  DWORD PTR [ecx], edx
     mov  esp, ebp
     pop  ebp
     ret  0
_simple ENDP
_TEXT ENDS
END
