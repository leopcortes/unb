import random

def get_nth_bit(binary, position):
    shifted_one = 0x01 << position
    bit_at_position = binary & shifted_one
    return bit_at_position >> position

def set_bit(binary, bit_position):
    return binary | (1 << bit_position)

def clear_bit(binary, bit_position):
    return binary & ~(1 << bit_position)

def invert_nth_bit(binary, position):
    bit = get_nth_bit(binary, position)
    if bit:
        return clear_bit(binary, position)
    else:
        return set_bit(binary, position)

def invert_random_bit(binary_number):
    import random
    #random.seed(0)
    position = random.randint(0, 7)
    return invert_nth_bit(binary_number, position)

x, y = map(int, input().split())
invx, invy = map(invert_random_bit, (x, y))

fmt_tabular = "{:<22} | {:<8} | {:<8}"

print()
print(fmt_tabular.format("inputs: ", x, y))
print(fmt_tabular.format("binary equivalents:", bin(x)[2:].zfill(8), bin(y)[2:].zfill(8)))
print(fmt_tabular.format("binary diffs:", bin(x^invx)[2:].zfill(8), bin(y^invy)[2:].zfill(8)))
print(fmt_tabular.format("inverted equivalents:", bin(invx)[2:].zfill(8), bin(invy)[2:].zfill(8)))

print(f"\nAND ({bin(invx)[2:].zfill(8)}, {bin(invy)[2:].zfill(8)}) = {bin(invx & invy)[2:].zfill(8)}")
print(f"OR ({bin(invx)[2:].zfill(8)}, {bin(invy)[2:].zfill(8)}) = {bin(invx | invy)[2:].zfill(8)}")
print(f"XOR ({bin(invx)[2:].zfill(8)}, {bin(invy)[2:].zfill(8)}) = {bin(invx ^ invy)[2:].zfill(8)}\n")