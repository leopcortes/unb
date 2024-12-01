section .bss
    size resd 1
    enc  resd 1
    a resb 1
    b resb 1
    c resb 1

section .data
    encoding_table db \
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',  \
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P' , \
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',  \
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',  \
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',  \
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',  \
    'w', 'x', 'y', 'z', '0', '1', '2', '3',  \
    '4', '5', '6', '7', '8', '9', '+', '/'   \

    reboco_vec db 0,2,1
section .text
global BASE64_encode
extern malloc
; input
; eax -> char* msg
; ebx -> msg_size
;output
; eax ->encoded_msg
; ebx ->encoded_msg_size

BASE64_encode:

    enter 8, 0
    pusha

    mov esi,  [ebp+8]  ;; char* input
    mov eax, [ebp+12] ;; size_t input_size

    ;; calcula tamanho do output
    ;; output = (input+2)/3 * 4
    add eax, 2
    mov edx, 0 ; edx faz parte do mul em 32 bits
    mov ecx, 3
    div ecx
    mov ebx, 4
    mul ebx
    mov [size], eax ;; salva o tamanho do vetor na var
    mov ebx, [ebp+16]
    mov [ebx], eax
    add eax,1   ;; \0 no final
    push eax    ;; push da quantidade de bytes a ser alocado
    call malloc ;; aloca vetor e retorna * em eax
    add esp,4   ;; undo push

    mov edi, eax    ;; passa * para edi
    mov [enc], eax  ;; salva na var tmb

    mov ebx, [size] ;;carrega tamanho em ebx
    mov byte [edi+ebx], 0 ;; null termination


    mov ecx,0
    mov edx,0
;; esi = input
;; edi = output
;; for(ecx = 0, edx = 0; ecx < size;)
encode_for_loop:
    ;check ecx < size
    mov eax, [ebp+12]
    cmp ecx, eax
    je after_encoding

;;  a = byte1 <<16 | byte2 <<8 | byte3

;; a = byte1 << 16
    mov ebx,0
    mov bl,[esi+ecx]
    inc ecx
    shl ebx,16
    mov eax,ebx

; if i < inputsize b = input[i] else b = 0
check_b:
    mov ebx,0
    push eax
    mov  eax, [ebp+12]
    cmp  ecx,eax
    jl check_b_less
    jmp check_b_end

check_b_less:
    mov bl,[esi+ecx]
    inc ecx


check_b_end:
    pop eax
    shl ebx,8
    or eax,ebx

check_c:
    mov ebx,0
    push eax
    mov  eax, [ebp+12]
    cmp  ecx,eax
    jl check_c_less
    jmp check_c_end

check_c_less:
    mov bl,[esi+ecx]
    inc ecx

check_c_end:
    pop eax
    or eax,ebx
    mov ebx,0


after_check:

    ;; adiciona 4 entradas no ouput a partir das 3 entradas
    ;;output[j++] = encoding_table[(tripla >> 3 * 6) & 0x3F];
    ;;output[j++] = encoding_table[(tripla >> 2 * 6) & 0x3F];
    ;;output[j++] = encoding_table[(tripla >> 1 * 6) & 0x3F];
    ;;output[j++] = encoding_table[(tripla >> 0 * 6) & 0x3F];

    ;; entrada 1
    push eax
    shr eax,18

    and eax,0x3F

    mov bl, [encoding_table+eax]

    mov [edi+edx], bl
    inc edx
   ;; entrada 2
    mov eax,[esp]

    shr eax,12

    and eax,0x3F

    mov bl, [encoding_table+eax]

    mov [edi+edx], bl
    inc edx

    ;; entrada 3
    mov eax,[esp]

    shr eax,6

    and eax,0x3F

    mov bl, [encoding_table+eax]

    mov [edi+edx], bl
    inc edx

   ;; entrada 4
    pop eax
    and eax,0x3F

    mov bl, [encoding_table+eax]

    mov [edi+edx], bl
    inc edx

    jmp encode_for_loop
after_encoding:

; vamos usar o vec do reboco pro padding, com reboco[size%3] entradas

    ; input_size % 3pro loop do reboco
    mov eax,[ebp+12]
    mov edx,0  ;limpando pro div
    mov ecx,3
    div ecx  ; resto em edx
    mov ebx,0
    mov bl,[reboco_vec+edx] ; quantidade de padding
    mov ecx,0 ; ecx pro loop
    mov edx, [size]

;; for(ecx = 0; ecx < reboco_vec[input_size % 3]; i++)
; '=' = 3D
padding_loop:
    cmp ecx,ebx
    jge after_padding
    mov eax,edx
    sub eax,1
    sub eax,ecx
    mov byte [edi+eax], 0x3D
    inc ecx
    jmp padding_loop
after_padding:


    popa
    leave
    mov eax,[enc]

    ret
