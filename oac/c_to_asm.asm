.data
mask:  .word 0xFFFF

.text
mul:	
	# x = LSW16(x-1);
	sub a0, a0, 1     # x = (x - 1)
	andi a0, a0, mask # x = ((x) & 0xFFFF)
	
	# t16 = LSW16(y-1);
	sub a1, a1, 1     # y = (y - 1)
	andi t1, a1, mask # t16 = ((y) & 0xFFFF)
	
	# t32 = (uint32_t) x * t16 + x + t16 + 1;
	mul t2, a0, t1    # t32 = x * t16
	add t2, t2, a0    # t32 += x
	add t2, t2, t1    # t32 += t16
	addi t2, t2, 1    # t32 += 1
	
	# x = LWS16(t32);
	andi a0, t2, mask # x = ((t32) & 0xFFFF)
		
	# t16 = MSW16(t32);
	li t3, 16         # t3 = 16
	srl t2, t2, t3    # t32 = t32 >> 16
	andi t1, t2, mask # t16 = ((t32 >> 16) & 0xFFFF)

	# x = (x - t16) + (x <= t16)
	sub a0, a0, t1    # x = x - t16
	bge a0, t1, fim   # if x > t16: x = (x-16) + 0 = x-16, logo encerra
	addi a0, a0, 1    # if x < t16: x = (x-16) + 1
	
fim:
	ret               # x = a0

# REGISTRADORES:
# a0 = x
# a1 = y
# t1 = t16
# t2 = t32
# t3 = 16
