
f=open("testdump.txt");
i=0

print ""

for line in  f:
    i+=1
    print "Line ",i,":",len(line.split("\t")),"columns"
