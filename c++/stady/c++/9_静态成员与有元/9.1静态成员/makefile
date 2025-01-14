CC:=g++

src:=main1.cpp
obj:=$(src:.cpp=.o)
exec:=$(src:.cpp=)

ALL: $(obj)  $(exec)
$(obj):%.o:%.cpp
	$(CC) -c $< -o $@ 
$(exec):%:%.o
	$(CC) $< -o $@ 

.PHNOY: ALL clean
clean: 
	-rm -r $(obj) $(exec)