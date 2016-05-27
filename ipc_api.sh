git clone https://github.com/nathanweeks/ipcmd.git ./ipcmd-download
cd ./ipcmd-download/
make
msgid=$(./bin/ipcmd msgget -Q 123 -e -m 0600)

echo "Podaj wyraz:"
read x

./bin/ipcmd msgsnd -q $msgid -t 2 -n $x
msg_rcv=$(./bin/ipcmd msgrcv -q $msgid -t 2 -n)
ipcrm -q $msgid

pierwszy=$(printf "%d" "'$msg_rcv:0:1")
if ([[ $pierwszy -ge 65 ]] && [[ $pierwszy -le 90 ]]) || ([[ $pierwszy -ge 97 ]] && [[ $pierwszy -le 122 ]]); then

	wynik=$(echo $msg_rcv | aspell list)
	if [[ $wynik == "" ]]; then
		echo "Wyraz poprawny w języku polskim"
	else
		echo "Wyraz niepoprawny w języku polskim"
	fi
	

else
	echo "Wyraz niepoprawny"
fi
