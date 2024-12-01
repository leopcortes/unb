def decapitalize_string(capitalized_string):
  decapitalized_string = capitalized_string[:2] + capitalized_string[2:].lower()
  return decapitalized_string

input_string = "\nNO AMBIENTE MICROSOFT EXISTEM AS BIBLIOTECAS DLL PARA LIGAÇÃO DINÂMICA.\n"
print(decapitalize_string(input_string))