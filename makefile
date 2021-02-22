run: transcode.c trans_encapsulation.c
	gcc -o run trans_encapsulation.c transcode.c -lavcodec -lavformat -lavutil -lpthread