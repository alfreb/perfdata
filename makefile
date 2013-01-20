OBJPATH=./

all:	libperfdata
	g++ -L. -lperfdata perfdata.cpp -o perfdata

libperfdata: cpuDataPoint cpuSample
	g++ -shared cpuDataPoint.o cpuSample.o -o libperfdata.so

cpuDataPoint: cpuSample
	g++ -c -fPIC cpuDataPoint.cpp -o cpuDataPoint.o

cpuSample:
	g++ -c -fPIC cpuSample.cpp -o cpuSample.o

install:
	LD_LIBRARY_PATH=.
	export LD_LIBRARY_PATH

clean: 		
#Fjern alle binærfiler
#@ hindrer utskrift til konsoll		
#- i tilfelle OBJPATH er tom
	-rm -f $(OBJPATH)*.o 
	-rm -f $(OBJPATH)*.so	
	@rm -f *~	
	rm -f perfdata