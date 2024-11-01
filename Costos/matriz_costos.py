import os

def create_cost_matrix(cost):
    cost_matrix = [[0 for _ in range(26)] for _ in range(26)]
    
    # Inicializar la matriz de costos con el costo de sustitución parametrizable
    for i in range(26):
        for j in range(26):
            if i == j:
                cost_matrix[i][j] = 0  # No hay costo si es la misma letra
            else:
                cost_matrix[i][j] = cost  # Costo de sustitución parametrizado
    return cost_matrix

def save_matrix_to_file(matrix, filename):
    # Obtener el directorio del archivo actual
    current_dir = os.path.dirname(__file__)
    # Crear la ruta completa del archivo
    file_path = os.path.join(current_dir, filename)
    
    with open(file_path, 'w') as file:
        # Escribir la matriz en el archivo
        file.write("26 26\n")
        for row in matrix:
            file.write(' '.join(map(str, row)) + '\n')  # Convertir cada fila en texto y añadir un salto de línea
    print(f"Matriz de costos guardada en {file_path}")

if __name__ == "__main__":
    substitution_cost = 2  # Ejemplo de costo parametrizable

    # Crear matriz de costos con un costo de sustitución de 2
    cost_matrix = create_cost_matrix(substitution_cost)
    
    # Guardar la matriz en un archivo de texto
    save_matrix_to_file(cost_matrix, "cost_replace.txt")