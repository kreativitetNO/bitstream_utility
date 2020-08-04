vpath %.cpp Program/src Tests
vpath %.h Program/include
vpath %.a Tests/lib

CXXFLAGS = -L Tests/lib
CPPFLAGS = -I Program/include -I Tests/include

all: BitstreamProgram
.PHONY: all

# $@ - Target
# $% - "The filename element of an archive member specification" ?
# $< - The first prequisite
# $? - The name of all prequisites newer than the targets with spaces
# $^ - The name of all prequisites without duplicates
# $+ - The name of all prequisites
# $* - The stem of the target filename (without suffix)
# Also:
# $(@D), $(<D) = dir part
# $(@F), $(<F) = file part

BitstreamProgram: Program.o Bitstream.o
	g++ $^ $(CXXFLAGS) -o $@

Tests: BitstreamTest
.PHONY: Tests

BitstreamTest: BitstreamTest.o Bitstream.o -lgtest -lgtest_main -lpthread
	g++ $(CXXFLAGS) $^ -o $@

Program.o: Program.cpp
	g++ -c $(CPPFLAGS) $<

Bitstream.o: Bitstream.cpp Bitstream.h
	g++ -c $(CPPFLAGS) $<

BitstreamTest.o: BitstreamTest.cpp
	g++ -c $(CPPFLAGS) $<

.PHONY: clean
clean:
	rm -f *.o BitstreamTest BitstreamProgram

#print: *.cpp
#	lpr $?
#	touch $@

