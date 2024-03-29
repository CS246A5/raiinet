CXX = g++-11 -std=c++20
CXXFLAGS = -Wall -g -MMD -Werror=vla  # use -MMD to generate dependencies
SOURCES = ${wildcard *.cc ability/*.cc}     # list of all .cc files in the current directory
SOURCES += ${wildcard *.cc}
OBJECTS = ${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=raiinet

# First target in the makefile is the default taårget.
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) -lX11

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS)

-include ${DEPENDS}

.PHONY: clean 
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
