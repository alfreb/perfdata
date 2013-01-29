perfdata
========

Collect performance data, while impacting the system as little as possible

Usage:
------------
Print performance data with column names
./perfdata -T

print performance data without column names
./perfdata

Example:
--------------
./perfdata -T > testdump.txt
./perfdata >> testdump.txt
./perfdata >> testdump.txt
./perfdata >> testdump.txt

This will add column headers and 4 (four) lines of performance data to testdump.txt
