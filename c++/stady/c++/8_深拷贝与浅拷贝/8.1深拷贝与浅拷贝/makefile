CC:= g++

src:=main1.cpp main2.cpp
obj:=$(src:.cpp=.o)
exec:=$(src:.cpp=)

ALL: $(exec) $(obj)

$(obj):%.o:%.cpp	
	$(CC) -c $^ -o $@
$(exec):%:%.o
	$(CC) $^ -o $@

.PHONY: ALL clean
clean:
	-rm -r $(obj) $(exec) 