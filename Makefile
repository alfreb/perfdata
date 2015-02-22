GPP=g++-4.9 -std=c++14 # -std=c++11
GPPOPT=-c

OBJ=cpusample.o stat.o pidstat.o
LIB=perfdata.a


all: lib procstat pidstat

lib: $(OBJ)
	ar rcs perfdata.a $(OBJ)
	$(RM) $(OBJ)

procstat: lib procstat.cpp
	$(GPP) $@.cpp $(LIB) -o $@

pidstat: lib pidstat_main.cpp
	$(GPP) pidstat_main.cpp $(LIB) -o $@

%.o: %.cpp %.hpp
	$(GPP) $(GPPOPT) $< -o $@


clean:
	$(RM) $(OBJ) $(LIB) procstat pidstat
