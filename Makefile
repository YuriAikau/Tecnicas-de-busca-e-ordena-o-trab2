all: clear
	gcc -lm ./*.c -o trab2

run:
	./teste ../entradas/N10_S3_C3_M3.txt

%.o: %.c
	gcc $< -o $@

clear:
	rm -f ./trab2