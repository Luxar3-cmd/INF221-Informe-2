# INF221-Informe-2

## Informe 2: Análisis de Algoritmos
Algunos lineamientos que tengo que seguir para el informe 2 son los siguientes: 

Especificar la maquina.

Links usados para la investigación:

Para la fuerza bruta:
https://www.geeksforgeeks.org/damerau-levenshtein-distance/  (redy)
https://www.enjoyalgorithms.com/blog/edit-distance  (redy)
https://dl.acm.org/doi/pdf/10.1145/363958.363994 (este es el paper de Damerau-Levenshtein) (redy)

Para la programación dinámica:
https://www.geeksforgeeks.org/dynamic-programming-set-5-edit-distance/ (redy)
https://en.wikipedia.org/wiki/Edit_distance (not)
https://www.geeksforgeeks.org/edit-distance-in-cpp/ (redy)
https://www.geeksforgeeks.org/what-is-memoization-a-complete-tutorial/
https://stackoverflow.com/questions/10638597/minimum-edit-distance-reconstruction
https://bdebo.medium.com/edit-distance-643a4bcfaa09 (redy)
https://www.spiceworks.com/tech/devops/articles/what-is-dynamic-programming/

Basado en los trabajos de Damerau y Levenshtein
 
La transposición solamente se lleba a cabo si ambos caracteres están en su posición final.



Para los datasets lo que haré es que cuando los algoritmos estén completamente listos evaluaremos palabras 
con distancias de la menor a la mayor, por ejemplo, sea k la distancia entre dos palabras, probaremos con 
k=1, k=2, k=3, k=4, etc.... Se compararán los tiempos con el enfoque de fuerza bruta y de esta manera se 
contrastarán las complejidades.


 Brill, Eric; Moore, Robert C. (2000). An Improved Error Model for Noisy Channel Spelling Correction (PDF). Proceedings of the 38th Annual Meeting on Association for Computational Linguistics. pp. 286–293. doi:10.3115/1075218.1075255.
 