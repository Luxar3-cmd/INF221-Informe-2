import os

def create_insertion_costs(insertion_cost):
    # Crear una lista donde cada posición representa el costo de insertar una letra
    insertion_costs = [insertion_cost] * 26  # Inicializa con el mismo costo para todas las letras
    return insertion_costs

def create_deletion_costs(deletion_cost):
    # Crear una lista donde cada posición representa el costo de eliminar una letra
    deletion_costs = [deletion_cost] * 26  # Inicializa con el mismo costo para todas las letras
    return deletion_costs

def save_list_to_file(cost_list, filename):
    # Obtener el directorio del archivo actual
    current_dir = os.path.dirname(__file__)
    # Crear la ruta completa del archivo
    file_path = os.path.join(current_dir, filename)
    
    

    with open(file_path, 'w') as file:
        file.write("1 26\n")
        file.write(' '.join(map(str, cost_list)) + '\n')  # Escribir los valores separados por espacios en una sola línea
    print(f"Lista de costos guardada en {file_path}")

# Ejemplo de uso
if __name__ == "__main__":
    # Definir los costos parametrizados
    insertion_cost = 1
    deletion_cost = 1

    # Crear las listas de costos
    insertion_costs = create_insertion_costs(insertion_cost)
    deletion_costs = create_deletion_costs(deletion_cost)
    
    # Guardar las listas de costos en archivos
    save_list_to_file(insertion_costs, "cost_insert.txt")
    save_list_to_file(deletion_costs, "cost_delete.txt")