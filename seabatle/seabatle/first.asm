.386 
PUBLIC _userhit@12
.model flat 
.code 
_userhit@12 proc 

xor eax, eax
xor ebx, ebx
xor ecx, ecx
xor edx, edx

 push ebp
 mov ebp, esp

 mov eax, [ebp+8] ;x
 mov ebx, [ebp+12] ; y
 mov esi, [ebp+16]
 add esi, eax
 mov edx, 10
 mov eax, ebx
 mul edx
 add esi, eax
 mov cl, byte ptr[esi]
 cmp cl, 127
 je End1
 jne Continius
 End1:
  mov eax, 1
  jmp EndAll
 Continius:
  cmp cl, '*'
  je End2
  cmp cl, '.'
  je End2
  jne End3
End2:
 mov eax, -1
 jmp EndAll
End3:
 mov eax, 0
EndAll:
 pop ebp
  ret 12
_userhit@12 endp 
end 
