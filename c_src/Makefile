CC=gcc

FLAGS=-fPIC -shared
ERL_ROOT=/usr/local/lib/erlang
 
all:
	$(CC) $(FLAGS) -o ../ebin/clif.so clif.c -I $(ERL_ROOT)/usr/include/ -lOpenCL
