def exibe_candidatos(deque, pos, ordem):
    if ordem == "direta":
        for _ in range(pos):
            deque.remove_front()
        while not deque.is_empty():
            print(deque.remove_front())
    if ordem == "inversa":
        for _ in range(deque.size()-pos-1):
            deque.remove_rear()
        while not deque.is_empty():
            print(deque.remove_rear())