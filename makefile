OBJPATH=./

static: libperfdata remove_objects
	g++ perfdata.cpp libperfdata.so -o perfdata

totals:	cpuSample2 memDataPoint
	g++ perftotals.cpp cpuSample.o memDataPoint.o -o perftotals

test:	cpuSample2 memDataPoint
	g++ perfSampler.cpp cpuSample.o memDataPoint.o -o test_perfsampler

mini: cpuSample
	g++ perfdata_mini.cpp cpuSample.o -o perfdata_mini

dynamic: libperfdata remove_objects
	g++ -L. -lperfdata perfdata.cpp -o perfdata


libperfdata: cpuDataPoint cpuSample memDataPoint
	g++ -shared -o libperfdata.so *.o

cpuDataPoint: cpuSample
	g++ -c -fPIC cpuDataPoint.cpp -o cpuDataPoint.o

cpuSample:
	g++ -c -fPIC cpuSample.cpp -o cpuSample.o

cpuSample2:
	g++ -c -fPIC cpuSample2.cpp -o cpuSample.o

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
