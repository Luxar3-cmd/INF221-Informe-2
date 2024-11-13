import random
import string
import os
import csv

def generate_random_string(length):
    return ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

def generate_repeated_char_string(length):
    char = random.choice(string.ascii_lowercase)  # Seleccionar un carácter aleatorio
    return char * length  # Repetir el carácter para toda la longitud

def generate_file_with_transpositions_and_repetitions(num_transpositions, num_repetitions, num_empty_non_empty_pairs, num_equal_repetitions, max_length):
    # Obtener la ruta del directorio actual donde está el archivo .py
    current_directory = os.path.dirname(os.path.abspath(__file__))
    filepath = os.path.join(current_directory, "dataset2.csv")

    with open(filepath, mode="w", newline="") as file:
        writer = csv.writer(file)
        # Escribir la cabecera del archivo CSV
        writer.writerow(["String 1", "String 2", "Case"])

        # Generar pares con transposiciones de caracteres adyacentes
        for _ in range(num_transpositions):
            length = random.randint(2, max_length)  # Longitud mínima de 2 para permitir transposición
            base_string = generate_random_string(length)
            # Elegir una posición aleatoria para la transposición adyacente
            i = random.randint(0, length - 2)  # Índice entre 0 y length - 2 para garantizar adyacencia
            transposed_string = list(base_string)
            # Intercambiar caracteres adyacentes
            transposed_string[i], transposed_string[i + 1] = transposed_string[i + 1], transposed_string[i]
            transposed_string = ''.join(transposed_string)
            writer.writerow([base_string, transposed_string, "Transposition"])

        # Generar pares de cadenas con caracteres repetidos
        for _ in range(num_repetitions):
            length = random.randint(1, max_length)
            string1 = generate_repeated_char_string(length)
            string2 = generate_repeated_char_string(length)
            writer.writerow([string1, string2, "Repetition"])

        # Generar casos donde un string está vacío y el otro no
        for _ in range(num_empty_non_empty_pairs):
            non_empty_length = random.randint(1, max_length)
            non_empty_string = generate_random_string(non_empty_length)
            # Elegir aleatoriamente cuál de los dos strings estará vacío
            if random.choice([True, False]):
                writer.writerow(["", non_empty_string, "Empty-NonEmpty"])
            else:
                writer.writerow([non_empty_string, "", "Empty-NonEmpty"])

        # Agregar pares de cadenas idénticas (Equal-Repetition)
        for _ in range(num_equal_repetitions):
            length = random.randint(1, max_length)
            equal_string = generate_random_string(length)
            writer.writerow([equal_string, equal_string, "Equal"])

        # Agregar caso de cadenas vacías
        writer.writerow(["", "", "Empty"])

# Ejemplo de uso: 5 transposiciones, 10 repeticiones, 5 pares de cadena vacía y no vacía, 5 pares idénticos, longitud máxima de 10
generate_file_with_transpositions_and_repetitions(num_transpositions=100, num_repetitions=100, num_empty_non_empty_pairs=100, num_equal_repetitions=100, max_length=11)
