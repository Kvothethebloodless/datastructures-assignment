

CC = gcc
CFLAGS = -std=gnu11 -s -c -g3 -time -Wall -ggdb -pg
WARNINGS = -Werror -Wall -Wextra -pedantic-errors -Wformat=2 -Wno-import -Wimplicit -Wmain -Wchar-subscripts -Wsequence-point -Wmissing-braces -Wparentheses -Winit-self -Wswitch-enum -Wstrict-aliasing=2 -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-qual -Wcast-align -Wwrite-strings -Wstrict-prototypes -Wold-style-definition -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline -Wdisabled-optimization -Wunused-macros -Wno-unused
LDFLAGS = -pg
LIBRARIES = -lcurl -lm
SOURCEDIR = src
#SOURCES = $(wildcard $(addprefix $SOURCEDIR/,*.c))
SOURCES = $(shell find $(SOURCEDIR) -name '*.c')
OBJECTDIR = build
ONAMES = $(subst .c,.o, $(SOURCES))
OBJECTNAMES = $(subst $(SOURCEDIR), $(OBJDIR), $(ONAMES))
OBJECTS = $(addprefix $(OBJECTDIR)/, $(OBJECTNAMES))
EXECUTABLE = $(addprefix $(OBJECTDIR)/, main)

INCLUDE = -I./include

all: $(SOURCES) $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS) | $(OBJECTDIR)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBRARIES)

$(OBJECTS): $(addprefix $(OBJECTDIR)/, %.o) : $(addprefix $(SOURCEDIR)/,%.c) | $(OBJECTDIR)
	$(CC) $(INCLUDE) $(CFLAGS) $< -o $@


$(OBJECTDIR):
	mkdir -p $(OBJECTDIR)

.PHONY: doc clean

debug:
	ddd ./$(EXECUTABLE)

clean:
	rm -rf $(EXECUTABLE) $(OBJECTDIR)/$(OBJECTS)
	rm -rf prof*

.ONESHELL:
profile:
	./$(EXECUTABLE); gprof -f -b ./$(EXECUTABLE) gmon.out > profout ;	gedit profout ;

