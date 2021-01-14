#!/bin/bash

memsize=500
end=4000


echo "" > out.csv # Überschreiben der Datei
echo "" > out.txt

echo "starting measurment"

# { ./tlb $page $trials ; echo " $page"; } >> out.txt # Einlesen in die Datei

while [ $memsize -lt $end ]; do
    { ./mem2 $memsize ; echo " $memsize"; } | paste -sd ' ' >> out.csv # Einlesen in die Datei
    let memsize=memsize+500
done

echo "done with measurement"
