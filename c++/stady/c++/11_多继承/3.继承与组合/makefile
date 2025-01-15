CC:=g++

src:= main1.cpp 
obj:= $(src:.cpp=.o)
exec:= $(src:.cpp=) 

ALL:  $(exec)
$(exec):%:%.o
	$(CC)   $^ -o $@
%.o:%.cpp
	$(CC)  -c $^ -o $@

.PHONY: ALL clean
clean:
	-rm -r $(obj) $(exec)

