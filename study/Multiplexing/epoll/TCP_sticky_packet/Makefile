.PHONY: all client server clean

all: client server MV

client:
	$(MAKE) -C client

server:
	$(MAKE) -C server

MV:
	-mkdir ./MIN
	-mv  ./USER/user.o ./MIN/
	-mv  ./server/server.o ./MIN/
	-mv  ./client/client.o ./MIN/
clean:
	$(MAKE) -C client clean
	$(MAKE) -C server clean
	-rm -rf ./MIN