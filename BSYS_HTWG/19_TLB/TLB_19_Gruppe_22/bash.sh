#!/bin/bash

page=1
loop=5000
trials=1000

echo "" > out.csv # Überschreiben der Datei
echo "" > out.txt

echo "starting measurment"

# { ./tlb $page $trials ; echo " $page"; } >> out.txt # Einlesen in die Datei

while [ $page -lt $loop ]; do
    { ./tlb $page $trials ; echo " $page"; } | paste -sd ' ' >> out.csv # Einlesen in die Datei
    let page=page+100
done

echo "done with measurement"
