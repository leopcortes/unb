section .bss
    output  resd 1           ; Reserva 1 dword para armazenar o endereço do buffer de saída
    len     resd 1             ; Reserva 1 dword para armazenar o tamanho da string de entrada

section .data
    decode_table db \
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, \
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, \
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 62, 63, 62, 62, 63, \
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61,  0,  0,  0,  0,  0,  0, \
        0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, \
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,  0,  0,  0,  0, 63, \
        0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, \
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
   pad dd 0

section .text
global BASE64_decode
extern malloc, realloc

BASE64_decode:
    enter 0, 8             ; pilha de quadros
    pusha                  ; Salva todos os registradores gerais na pilha

    ; input: [ebp+8] -> char* input, [ebp+12] -> size_t input_size, [ebp+16] -> size_t* output_size
    mov esi, [ebp + 8]     ; Carrega o ponteiro da string de entrada em esi
    mov ecx, [ebp + 12]    ; Carrega o tamanho da string de entrada em ecx
    test ecx,ecx            ; Verifica se o tamanho da string é zero
    jz after_padding_check  ; Se for, pula para .after_padding_check
    ;verifica se tem padding
aqui:
    mov ebx, 0  ; garante que ebx tem 0, ja q so salvar em bl n muda o resto do reg
    dec ecx     ; como ecx contem o size, o indice final e ecx - 1
    ;mov bl, [esi+ecx]  ; carrega em bl o byte do ultimo char da entrada
    ;cmp bl, '=' ; compara com = pra saber se tem padding
    ;jne after_padding_check ; se n tiver nao seta a flag de padding
    ;mov bl,1    ; como n pode ser feita operacao de imediato pra memoria botamos o valor em bl
    ;mov [pad], bl ;  settamos a flag de padding pra 1
    movzx ebx, byte [esi + ecx - 1]  ; Carrega o último caractere do input
    cmp bl, '='                      ; Verifica se é '='
    jne after_padding_check         ; Se não for '=', pula para a próxima etapa
    mov dword [pad], 1              ; Define a flag de padding para 1

after_padding_check:
    ; Calcula o tamanho da saída
    ; len = ((input_size + 3)/ 4 - pad) * 4;
    ; quantos bytes vao ser considerados
    mov eax, [ebp+12]   ; carrega o tamanho do input
    add eax, 3
    shr eax, 2
    sub eax, [pad]
    shl eax,2
    push eax ; salva o len na pilha, agr eax sera usado pra calcular output_size

    ; output_size = len/4 *3 + pad;
    shr eax,2
    mov edx,0
    mov ecx,3
    mul ecx
    add eax,[pad]
    ; como a var e um ponteiro, e n da pra fazer ** no opcode, primeiro botamos o ponteiro no reg
    ; pra depois acessar a memoria de verdade
    mov ebx,[ebp + 16]     ; carrega o *int output_size
    mov [ebx], eax         ; Armazena o tamanho da saída no ponteiro

    ; Aloca buffer de saída
    push eax
    call malloc
    add esp,4

dps:

    test eax, eax          ; Verifica se malloc retornou NULL
    jz malloc_fail         ; Se falhou, vai para .malloc_fail
    mov edi, eax           ; endereco da saida
    mov [output], eax      ; salva o endereco de saida na var
    pop eax                ; recupera o len da pilha
    ; Decodifica Base64
    mov ecx, 0  ; indice entrada
    mov edx, 0  ; indice saida

;; for(int i = 0, int j = 0; i  < len;)
decode_loop:
    ;; check i < len
    cmp ecx, eax
    jge after_decode

    push eax  ; salva len na linha
    ;; junta 6 bytes de 4 entradas do input apos o decode
    ;1

    ; n = B64_decoder[input[i++]] << 18 |
    ;     B64_decoder[input[i++]] << 12 |
    ;     B64_decoder[input[i++]] << 6 |
    ;     B64_decoder[input[i++]];

    ;n = B64_decoder[input[i++]] << 18
    mov ebx,0 ;; garante ebx esta zerado
    mov bl, [esi+ecx]   ; bl = input[i]
    inc ecx             ; i++
    mov bl,[decode_table +ebx] ; decode[input[i]]
    shl ebx,18  ;; decode[input[i]] << 18
    mov eax,ebx

    ;n |= B64_decoder[input[i++]] << 12
    mov ebx, 0
    mov bl, [esi+ecx]
    inc ecx
    mov bl,[decode_table +ebx]
    shl ebx,12
    or eax,ebx

    ; n|= B64_decoder[input[i++]] << 6
    mov ebx, 0
    mov bl, [esi+ecx]
    inc ecx
    mov bl,[decode_table +ebx]
    shl ebx,6
    or eax,ebx

    ; n|= B64_decoder[input[i++]];
    mov ebx, 0
    mov bl, [esi+ecx]
    inc ecx
    mov bl,[decode_table +ebx]
    or eax,ebx
    ; agora pra salvar no output
    ;output[j++] = n >> 16;
    ;output[j++] = n >> 8 & 0xFF;
    ;output[j++] = n & 0xFF;
salva:
    ; output[j++] = n >> 16;
    push eax ; salva n na pilha pra manipular
    shr eax,16
    mov [edi+edx],eax ; salva no output
    inc edx ; j++

    ; output[j++] = n >> 8 & 0xFF;
    mov eax, [esp] ; pra n ter q dar push dnv
    shr eax, 8
    and eax, 0xFF
    mov [edi+edx],eax ; salva no output
    inc edx ; j++

    ; output[j++] = n & 0xFF;
    pop eax
    and eax, 0xFF
    mov [edi+edx],eax; salva na pilha
    inc edx ; j++

    pop eax ; recupera len da pilha pra cmp no comeco do loop

    jmp decode_loop



after_decode: ; AQUI Q TEM Q VER O TREM DO PADDING
    mov eax, [pad]
    test eax,eax
    jz done


end_padding: ;
; n = B64_decoder[(unsigned char)input[len]] << 18 | B64_decoder[(unsigned char)input[len + 1]] << 12
    movzx eax, byte [esi + ecx - 1]  ; Carrega (unsigned char)input[len]
    movzx ebx, byte [esi + ecx - 2]  ; Carrega (unsigned char)input[len + 1]
    mov al, [decode_table + eax]    ; Decodifica o valor
    shl al, 18                      ; Desloca 18 bits para a esquerda
    mov cl, [decode_table + ebx]    ; Decodifica o valor
    shl cl, 12                      ; Desloca 12 bits para a esquerda
    or al, cl                       ; Combina com n

    ; output[(int)*output_size - 1] = n >> 16;
    mov eax, [ebp + 16]             ; Carrega o ponteiro para output_size
    mov ebx, [eax]                 ; Carrega o valor de output_size
    dec ebx                        ; Decrementa para obter o índice correto (output_size - 1)
    mov al, al
    mov [edi + ebx], al            ; Armazena o byte no buffer de saída

    ; Verifica se input_size > len + 2 e se input[len + 1] != '='
    mov eax, [ebp + 12]           ; Carrega input_size
    sub eax, ecx                  ; Ajusta o tamanho para ignorar o padding
    add eax, 1                    ; Adiciona 1 para verificar input[len + 1]
    cmp [ebp + 12], eax           ; Compara input_size com len + 1
    jle done                      ; Se não há mais caracteres para verificar, pula para done

    ; Verifica se input[len + 1] não é '='
    movzx eax, byte [esi + ecx]  ; Carrega (unsigned char)input[len + 1]
    cmp al, '='                    ; Compara com '='
    je done                        ; Se for '=', pula para done

    ; n |= B64_decoder[(unsigned char)input[len + 1]] << 8
    movzx eax, byte [esi + ecx]   ; Carrega (unsigned char)input[len + 1]
    mov al, [decode_table + eax]  ; Decodifica o valor
    shl al, 8                     ; Desloca o valor 8 bits para a esquerda
    or bl, al                     ; Combina o novo valor com n

    ; output[(int)*output_size - 2] = n >> 8 & 0xFF
    mov eax, [ebp + 16]          ; Carrega o ponteiro para output_size
    mov ebx, [eax]              ; Carrega o valor de output_size
    sub ebx, 2                 ; Ajusta para o índice (output_size - 2)
    shr bl, 8                 ; Desloca n 8 bits para a direita para obter o byte significativo
    mov [edi + ebx], bl       ; Armazena o byte no buffer de saída

done:
    popa    ; Restaura todos os registradores gerais da pilha
    leave   ; Libera a pilha de quadros
    mov eax, [output] ; salva o output pra retorno
    ret     ; Retorna o endereço do buffer decodificado

malloc_fail:

      jmp done
