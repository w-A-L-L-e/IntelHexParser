LNAME = IntelHexParser

# Source Files
SRC = \
	src/IntelHexFile.cpp \
	src/IntelHexFileEntry.cpp \
	src/Program.cpp \
	src/ProgramPage.cpp \
	src/hexconvert.cpp

OBJ = $(SRC:.cpp=.o)
TOOL = hexconvert


# Include Directories
INCLUDES = -I./include/

CCFLAGS = -O2 -fPIC
CCC = g++
 
.SUFFIXES: .cpp
 
all: build

build: $(TOOL)
 
$(TOOL): $(OBJ)
	$(CCC) -Wall -O2 -o $(TOOL) $(OBJ) 

.cpp.o:
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@ 


#install: build
#	#mkdir -p /usr/include/$(LNAME)/
#	#cp include/* /usr/include/$(LNAME)/
#	#cp $(REALNAME) /usr/lib/
#	ln -sf /usr/lib/$(REALNAME) /usr/lib/$(LIBNAME)

clean:
	rm -f $(OBJ) $(TOOL)

