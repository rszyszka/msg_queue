#!/bin/bash

./send
message=$(./recieve)

if [[ $message != 'niepoprawny' ]]; then
	wynik=$(echo $message | aspell list)
	if [[ $wynik == "" ]]; then
		echo "Wyraz poprawny w języku polskim"
	else
		echo "Wyraz niepoprawny w języku polskim"
	fi
else
	echo "Wyraz niepoprawny"
fi
