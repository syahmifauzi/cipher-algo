text = input("Enter ASCII String: ")
text = [bin(ord(ch))[2:] for ch in text]
text = ['0' * (8-len(ch)) + ch for ch in text]
print(''.join(text))

# TODO: Binary to ASCII Conversion
