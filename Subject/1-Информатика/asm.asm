    global _start
    
    section .text

_start:

    rdrand ebx

    ;mov ebx, 3735928559
    mov ebp, 31

ebxl:
    mov ecx, ebx

    mov r9d, 0
brf:cmp r9d, ebp
    jge brs
    shr ecx, 1
    inc r9d
    jmp brf
brs:

    and ecx, 1
    or ecx, 0x30
    mov [temp], ecx

    mov eax, write
    mov edi, 1
    mov esi, temp
    mov edx, 1
    syscall

    cmp ebp, 0
    jle go
    dec ebp
    jmp ebxl


go:

    mov eax, 0xA
    mov [temp], eax

    mov eax, write
    mov edi, 1
    mov esi, temp
    mov edx, 1
    syscall
;;;;;;;;;;;;;

;n1
    mov ebx, ebx

    mov eax, 0
    mov edi, 4
    mov ecx, ebx

    mov esi, ecx
    mov esp, 0
n1ll:cmp esp, eax
    jge n1lrx
    shl esi, 1
    add esp, 1
    jmp n1ll
n1lrx:
    mov esp, 0
n1lr:cmp esp, 28
    jge n1l
    shr esi, 1
    add esp, 1
    jmp n1lr
n1l:


    mov edx, ecx
    mov esp, 0
n1rl:cmp esp, edi
    jge n1rrx
    shl edx, 1
    add esp, 1
    jmp n1rl
n1rrx:
    mov esp, 0
n1rr:cmp esp, 28
    jge n1r
    shr edx, 1
    add esp, 1
    jmp n1rr
n1r:

    sub esi, edx
    mov r8d, esi
;n1



;n2
    mov ebx, ebx

    mov eax, 8
    mov edi, 12
    mov ecx, ebx

    mov esi, ecx
    mov esp, 0
n2ll:cmp esp, eax
    jge n2lrx
    shl esi, 1
    add esp, 1
    jmp n2ll
n2lrx:mov esp, 0
n2lr:cmp esp, 28
    jge n2l
    shr esi, 1
    add esp, 1
    jmp n2lr
n2l:

    mov edx, ecx
    mov esp, 0
n2rl:cmp esp, edi
    jge n2rrx
    shl edx, 1
    add esp, 1
    jmp n2rl
n2rrx:mov esp, 0
n2rr:cmp esp, 28
    jge n2r
    shr edx, 1
    add esp, 1
    jmp n2rr
n2r:

    sub esi, edx
    mov r9d, esi
;n2


;n3
    mov ebx, ebx

    mov eax, 16
    mov edi, 20
    mov ecx, ebx

    mov esi, ecx
    mov esp, 0
n3ll:cmp esp, eax
    jge n3lrx
    shl esi, 1
    add esp, 1
    jmp n3ll
n3lrx:mov esp, 0
n3lr:cmp esp, 28
    jge n3l
    shr esi, 1
    add esp, 1
    jmp n3lr
n3l:

    mov edx, ecx
    mov esp, 0
n3rl:cmp esp, edi
    jge n3rrx
    shl edx, 1
    add esp, 1
    jmp n3rl
n3rrx:mov esp, 0
n3rr:cmp esp, 28
    jge n3r
    shr edx, 1
    add esp, 1
    jmp n3rr
n3r:

    sub esi, edx
    mov r10d, esi
;n3



;n4
    mov ebx, ebx

    mov eax, 24
    mov edi, 28
    mov ecx, ebx

    mov esi, ecx
    mov esp, 0
n4ll:cmp esp, eax
    jge n4lrx
    shl esi, 1
    add esp, 1
    jmp n4ll
n4lrx:mov esp, 0
n4lr:cmp esp, 28
    jge n4l
    shr esi, 1
    add esp, 1
    jmp n4lr
n4l:

    mov edx, ecx
    mov esp, 0
n4rl:cmp esp, edi
    jge n4rrx
    shl edx, 1
    add esp, 1
    jmp n4rl
n4rrx:mov esp, 0
n4rr:cmp esp, 28
    jge n4r
    shr edx, 1
    add esp, 1
    jmp n4rr
n4r:

    sub esi, edx
    mov r11d, esi
;n4





;w1
    mov r12d, ebx
    mov esp, 0
    mov eax, 0
w1f:cmp esp, eax
    jge w1fe
    shl r12d, 1
    add esp, 1
    jmp w1f
w1fe:
    mov esp, 0
w1e:cmp esp, 24
    jge w1ee
    shr r12d, 1
    add esp, 1
    jmp w1e
w1ee:
;w1



;w2
    mov r13d, ebx
    mov esp, 0
    mov eax, 8
w2f:cmp esp, eax
    jge w2fe
    shl r13d, 1
    add esp, 1
    jmp w2f
w2fe:
    mov esp, 0
w2e:cmp esp, 24
    jge w2ee
    shr r13d, 1
    add esp, 1
    jmp w2e
w2ee:
;w2



;w3
    mov r14d, ebx
    mov esp, 0
    mov eax, 16
w3f:cmp esp, eax
    jge w3fe
    shl r14d, 1
    add esp, 1
    jmp w3f
w3fe:
    mov esp, 0
w3e:cmp esp, 24
    jge w3ee
    shr r14d, 1
    add esp, 1
    jmp w3e
w3ee:
;w3

;w4
    mov r15d, ebx
    mov esp, 0
    mov eax, 24
w4f:cmp esp, eax
    jge w4fe
    shl r15d, 1
    add esp, 1
    jmp w4f
w4fe:
    mov esp, 0
w4e:cmp esp, 24
    jge w4ee
    shr r15d, 1
    add esp, 1
    jmp w4e
w4ee:
;w4




    mov ebx, 0
    mov ecx, 0
    mov esp, 0
    mov ebp, 0


;n1n2
    cmp r8d, r9d
    jl n1n2
    inc ebx
    jmp n1n2e
n1n2: inc ecx
n1n2e:
;n1n2


;n1n3
    cmp r8d, r10d
    jl n1n3
    inc ebx
    jmp n1n3e
n1n3: inc esp
n1n3e:
;n1n3


;n1n4
    cmp r8d, r11d
    jl n1n4
    inc ebx
    jmp n1n4e
n1n4: inc ebp
n1n4e:
;n1n4

;n2n3
    cmp r9d, r10d
    jl n2n3
    inc ecx
    jmp n2n3e
n2n3: inc esp
n2n3e:
;n2n3



;n2n4
    cmp r9d, r11d
    jl n2n4
    inc ecx
    jmp n2n4e
n2n4: inc ebp
n2n4e:
;n2n4



;n3n4
    cmp r10d, r11d
    jl n3n4
    inc esp
    jmp n3n4e
n3n4: inc ebp
n3n4e:
;n3n4


    mov edx, 0

    add ebx, ebx
    add ebx, ebx
    add ebx, ebx

    add ecx, ecx
    add ecx, ecx
    add ecx, ecx

    add esp, esp
    add esp, esp
    add esp, esp

    add ebp, ebp
    add ebp, ebp
    add ebp, ebp


;mo w1
    mov edx, 0
w1m:cmp edx, ebx
    jge w1me
    shl r12d, 1
    add edx, 1
    jmp w1m
w1me:


;mo w2
    mov edx, 0
w2m:cmp edx, ecx
    jge w2me
    shl r13d, 1
    add edx, 1
    jmp w2m
w2me:


;mo w3
    mov edx, 0
w3m:cmp edx, esp
    jge w3me
    shl r14d, 1
    add edx, 1
    jmp w3m
w3me:


;mo w4
    mov edx, 0
w4m:cmp edx, ebp
    jge w4me
    shl r15d, 1
    add edx, 1
    jmp w4m
w4me:

    add r12d, r13d
    add r12d, r14d
    add r12d, r15d

;;;;;;;;;;;;;;;;;;;;;;;

    mov ebx, r12d
    mov ebp, 31

ebxlE:
    mov ecx, ebx

    mov r9d, 0
brfE:cmp r9d, ebp
    jge brsE
    shr ecx, 1
    inc r9d
    jmp brfE
brsE:

    and ecx, 1
    or ecx, 0x30
    mov [temp], ecx

    mov eax, write
    mov edi, 1
    mov esi, temp
    mov edx, 1
    syscall

    cmp ebp, 0
    jle goE
    dec ebp
    jmp ebxlE


goE:
;;;;;;;;;;;;;


    mov eax, 0xA
    mov [temp], eax

    mov eax, write
    mov edi, 1
    mov esi, temp
    mov edx, 1
    syscall
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;




    mov eax, 60
    mov edi, 0
    syscall

    section .data

read equ 0
write equ 1

    section .bss
temp resq 1