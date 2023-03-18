#!/bin/bash

make clean
make
echo ">>>> Comienzo de los test"
echo ""
for file in grafos/*.txt
do
    echo "<<<<<<<<<<<>>>>>>>>>>>"
    echo "Corriendo el archivo ->" $file
    ./discretaII < $file
done
echo ""
echo ">>>> Fin de los test"
make clean