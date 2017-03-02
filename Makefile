
CXX     = g++
RM      = rm -rf
SRCEXTS = .c .C .cc .cpp .CPP .c++ .cxx .cp
HRDEXTS = .h .H .hh .hpp .HPP .h++ .hxx .hp

## ========================================= ##
##               Configurable                ##
## ========================================= ##
CXXFLAGS   = -Wall -g -std=c++11 -fPIC
SRCDIR     = src
LIBS       = -luWS -luv -lz -lssl -lpthread -lmysqlcppconn
EXECUTABLE = app
INCLUDES   = 
LFLAGS     = -L/usr/local/lib


## ========================================= ##
##               Actual Build                ##
## ========================================= ##
SOURCES = $(foreach d,$(SRCDIR),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))
HEADERS = $(foreach d,$(SRCDIR),$(wildcard $(addprefix $(d)/*,$(HDREXTS))))

all:
	$(CXX) $(CXXFLAGS) -O0 $(LFLAGS) $(INCLUDES) $(SOURCES) -o $(EXECUTABLE) $(LIBS)
	$(RM) $(SRCDIR)/*.o

release:
	$(CXX) $(CXXFLAGS) -O2 $(LFLAGS) $(INCLUDES) $(SOURCES) -o $(EXECUTABLE) $(LIBS)
	$(RM) $(SRCDIR)/*.o

clean:
	$(RM) $(EXECUTABLE)