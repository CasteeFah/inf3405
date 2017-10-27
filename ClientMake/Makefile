#################################
#################################
#	client0 Makefile		#

PROJECTNAME= client

PRJSRC= main.cpp

VPATH= src:./../Client

#other includes path
INC=

#lib incl Add the used boost library here
LIBS= -lstdc++

YR= -std=c++14 ##c++ version

#################################
OPTLEVEL=s

CC = gcc

REMOVE=rm -f

CFLAGS=-I. $(INC) -MMD -g -O$(OPTLEVEL) -Wall

CPPFLAGS=-static-libstdc++ $(YR)

LDFLAGS=

#################################

TRG=$(PROJECTNAME)

CFILES = 	$(filter %.c, $(PRJSRC))

CPPFILES = 	$(filter %.cpp, $(PRJSRC))

OBJDEPS = 	$(CFILES:.c=.o)\
			$(CPPFILES:.cpp=.o)


.PHONY: all clean

all: $(TRG)

$(TRG): $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) -lm $(LIBS)

%.o: 	%.c
	$(CC) $(CFLAGS) -c $<

%.o: 	%.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	$(REMOVE) $(TRG) $(OBJDEPS) *.d




############### EOF
