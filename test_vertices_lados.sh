#!/bin/bash

#Colours
greenColour="\e[0;32m\033[1m"
endColour="\033[0m\e[0m"
redColour="\e[0;31m\033[1m"
blueColour="\e[0;34m\033[1m"
yellowColour="\e[0;33m\033[1m"
purpleColour="\e[0;35m\033[1m"
turquoiseColour="\e[0;36m\033[1m"
grayColour="\e[0;37m\033[1m"


make clean
make
echo ">>>> Comienzo de los test"
echo ""
for file in grafos/*.txt
do
    echo ""
    echo -e "${purpleColour}<<<<<<<<<<<>>>>>>>>>>>${endColour}"
    echo "Corriendo el archivo ->" $file
    echo -ne "\n${yellowColour}vertices,aristas = ${endColour}"
    array=($(grep "p edge" $file | awk '{print $3 " " $4}'))
    echo -ne "${array[0]},${array[1]}\n"
    array2=($(./discretaII < $file | grep -e "El número de vertices del grafo es:" -e "El número de lados del grafo es:" | awk '{print $8}'))
    if [ ${array[0]} == ${array2[0]} ] && [ ${array[1]} == ${array2[1]} ]; then
        echo ""
        echo -ne "${greenColour}Test OK -> vertices,aristas = ${array2[0]},${array2[1]}${endColour}${endColour}"
        echo ""
    else 
        echo ""
        echo -ne "${redColour}Test FAIL -> vertices,aristas = ${array2[0]},${array2[1]}${endColour}"
        echo ""
    fi; sleep 2
done
echo ""
echo -e "${purpleColour}>>>> Fin de los test${endColour}"
make clean

