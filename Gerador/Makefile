
# ---------------------------------------------------------------------
# Compiler selection 
# ---------------------------------------------------------------------

CCC       = g++ -O0
EXECNAME  = execfile


CFLAGS    = -c -Wall  -std=c++11
LNFLAGS   =  -lrt

INCLUDE   = . 
SRCDIR    = .
SRCLIST   = $(shell find $(SRCDIR) -name '*.cpp')
OBJDIR    = obj/
OBJLIST   = $(patsubst $(SRCDIR)%.cpp, $(OBJDIR)%.o, $(SRCLIST))

# ---------------------------------------------------------------------
# COMPILATION
# ---------------------------------------------------------------------
all:$(EXECNAME)

$(EXECNAME): $(OBJLIST) 
	$(CCC)  $(OBJLIST) -o $@ $(LNFLAGS)

$(OBJLIST): $(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CCC) $(CFLAGS) $? -o $@ $(INCLUDE)

clean:
	rm -rf $(OBJDIR)*.o
