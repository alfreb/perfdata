OBJPATH=./

static: libperfdata remove_objects
	g++ perfdata.cpp libperfdata.so -o perfdata


dynamic: libperfdata remove_objects
	g++ -L. -lperfdata perfdata.cpp -o perfdata


libperfdata: cpuDataPoint cpuSample memDataPoint
	g++ -shared -o libperfdata.so *.o

cpuDataPoint: cpuSample
	g++ -c -fPIC cpuDataPoint.cpp -o cpuDataPoint.o

cpuSample:
	g++ -c -fPIC cpuSample.cpp -o cpuSample.o

memDataPoint: 
	g++ -c -fPIC memDataPoint.cpp -o memDataPoint.o

install:
	LD_LIBRARY_PATH=.
	export LD_LIBRARY_PATH

remove_objects:
	-rm -f $(OBJPATH)*.o 
	@rm -f *~

clean: remove_objects	
	-rm -f $(OBJPATH)*.so
	-rm -f $(OBJPATH)*.out
	rm -f perfdata
