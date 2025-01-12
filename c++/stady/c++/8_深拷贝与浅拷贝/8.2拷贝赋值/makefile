CC:=g++

src:=main1.cpp
obj:=$(src:.cpp=.o)
exec:=$(src:.cpp=)

ALL:$(exec) $(obj) 
$(exec):%:%.o
	$(CC) $^ -o $@
$(obj):%.o:%.cpp
	$(CC) -c $^ -o $@

.PHONY:ALL clean
clean:
	-rm -r $(exec) $(obj)
	