import random
import string
import csv
import os

def random_word(length):
    """Genera una palabra aleatoria de una longitud dada."""
    return ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

def generate_fixed_length_pairs(length, num_pairs=50):
    """Genera pares de palabras aleatorias de una longitud fija."""
    pairs = []
    for _ in range(num_pairs):
        word1 = random_word(length)
        word2 = random_word(length)
        pairs.append((word1, word2))
    return pairs

def generate_fixed_length_dataset(max_length=10, num_pairs=50, filename="dataset1.csv"):
    """Genera un dataset con palabras de longitudes fijas desde 1 hasta max_length y lo guarda en un archivo CSV."""
    # Obtener la ruta actual del script
    current_dir = os.path.dirname(os.path.abspath(__file__))
    filepath = os.path.join(current_dir, filename)
    
    with open(filepath, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["Palabra 1", "Palabra 2", "Longitud"])  # Cabeceras

        for length in range(1, max_length + 1):
            pairs = generate_fixed_length_pairs(length, num_pairs)
            for word1, word2 in pairs:
                writer.writerow([word1, word2, length])

# Ejemplo de uso
max_length = 11  # Longitud máxima de las palabras
num_pairs = 10  # Número de pares por cada longitud
generate_fixed_length_dataset(max_length, num_pairs)
print(f"Archivo 'dataset1.csv' generado con {num_pairs} pares de palabras por cada longitud de 1 a {max_length}.")
