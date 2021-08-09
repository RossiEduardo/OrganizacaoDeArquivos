objs= obj/auxiliares.o obj/funcao-fornecida.o obj/funcionalidades.o obj/escrita_linha.o obj/escrita_veiculo.o obj/leitura_linha.o obj/leitura_veiculo.o obj/btree.o obj/auxliares_btree.o obj/leitura_e_escrita_btree.o

all:
	gcc -c src/auxiliares.c -o obj/auxiliares.o -I./include -g
	gcc -c src/funcao-fornecida.c -o obj/funcao-fornecida.o -I./include -g
	gcc -c src/funcionalidades.c -o obj/funcionalidades.o -I./include -g
	gcc -c src/escrita_linha.c -o obj/escrita_linha.o -I./include -g
	gcc -c src/escrita_veiculo.c -o obj/escrita_veiculo.o -I./include
	gcc -c src/leitura_linha.c -o obj/leitura_linha.o -I./include -g
	gcc -c src/leitura_veiculo.c -o obj/leitura_veiculo.o -I./include -g
	gcc -c src/btree.c -o obj/btree.o -I./include -g
	gcc -c src/auxiliares_btree.c -o obj/auxliares_btree.o -I./include -g
	gcc -c src/leitura_e_escrita_btree.c -o obj/leitura_e_escrita_btree.o -I./include -g


	gcc -o executavel main.c $(objs) -I ./include -g

run:
	./executavel

clean:
	rm -f obj/*.o
	rm -f ./executavel
	rm -f *.zip

cleanall:
	rm -f obj/*.o
	rm -f *.zip
	find . -maxdepth 1 -type f -not -name main.c -not -name Makefile -not -name in.in -delete

zip:
	zip zip1.zip ./src/* ./include/* Makefile main.c ./obj

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./executavel < in.in >OUT

teste:
	./executavel < in.in