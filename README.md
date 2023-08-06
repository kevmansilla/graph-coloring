# Proyecto matemática discreta II

## Manejo

Primero descargar algunos grafos de [aquí](https://drive.google.com/drive/folders/17hktF1u1oIRteQdL8uLQJGAIrTbIagK0?usp=sharing). 
Luego compilar con los siguientes comandos.

```
cd graph-coloring/

make

./discretaII < grafo_de_prueba.txt
```

## Testing

Primero se debe crear una carpeta llamada grafos en el directorio del proyecto y pegar algunos.

Velocidad para cargar el grafo
```
./test_velocidad.sh
```

Verificar que los lados y vertices coincidan 
```
./test_vertices_lados.sh
```
## Importante

Quedo un bug en la ordenación de la función orden jedi
