all:program

program: mf1.o fields.o jrb.o jval.o
	gcc mf1.o fields.o jrb.o jval.o -o kripto
p1.o: p1.c
	gcc -c mf1.c
fields.o: libfdr/fields.c libfdr/fields.h
	gcc -c libfdr/fields.c
jrb.o: libfdr/jrb.c libfdr/jrb.h
	gcc -c libfdr/jrb.c
jval.o: libfdr/jval.c libfdr/jval.h
	gcc -c libfdr/jval.c	
clean:
	rm *.o kripto
cleanall:
	rm *.txt .kilit encripted decripted ornek_metin
run: clean program	
	./kripto -e ornek_metin encripted
	./kripto -d encripted decripted
