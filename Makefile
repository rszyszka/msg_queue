all: send recieve

send: send.c
	gcc send.c -o send
	
receive: receive.c
	gcc receive.c -o receive
