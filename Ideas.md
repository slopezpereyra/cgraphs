# Hash table

### Por que usar una funcion hash ?
Cuando los grafos sean gigantes sera necesario cuando busquemos entre los vecinos una forma rapida de llegar a ellos, por eso creo que es conveniente usar una tabla hash donde la busqueda promedio es O(1)

### Como funciona ?
A travez de la clave, se analizan los bits del input genera un calculo y devuelve el indice donde se almacena la informacion. Esto puede llevar a que dos claves tengan el mismo valor (esto depende de la funcion usada)

### Resolución de colisiones
Direccionamiento cerrado, encadenamiento separado o hashing abierto.