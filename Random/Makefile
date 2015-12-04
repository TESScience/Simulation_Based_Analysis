LIBOBJS=calrissian.o randa.o squafib.o squarissian.o warpspeed.o

random : random.o $(LIBOBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean : 
	rm -f *.o random
