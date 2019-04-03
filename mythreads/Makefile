CFLAGS= #-Isrc -g -ggdb -IARM/lib/hwlib/include -IARM/lib/hwlib/include/soc_cv_av -Dsoc_cv_av -Inios2_bsp 
DEPS= $(wildcard main.c) $(wildcard src/*.c) 
HEADERS=
FILE= mypthread

mypthread: $(DEPS) $(HEADERS)
	$(CC) -o $@ $(DEPS) $(CFLAGS)

clean:
	-rm $(FILE)
	@echo "You just removed $(FILE)"
	
	
