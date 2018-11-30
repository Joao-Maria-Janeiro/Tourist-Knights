#compiler used
CC = gcc

#flags for individual object file compilation
CFLAGS = -Wall -std=c99 -g
#RELEASE
# -Wall -std=c99 -O3
#DEVELOPMENT
# -Wall -std=c99 -g

#source .c files
SOURCE = $(wildcard src/*.c)
#object files created
OBJECTS = $(patsubst src/%.c,bin/%.o,$(SOURCE))

#file extentions
IEXT = cities
OEXT = walks
#resources to test
INPUTS = $(wildcard res/*.$(IEXT))
#output of tests
OUTPUTS = $(wildcard res/*.$(OEXT))
ORIGINALS = $(patsubst res/%.$(OEXT),org/%.$(OEXT),$(OUTPUTS))

#executable name
EXECUTABLE = tuktuk

############################################################

all: $(EXECUTABLE)

run: $(EXECUTABLE)
	@for file in $(INPUTS); do \
		echo $$file; \
		./$(EXECUTABLE) $$file; \
	done

cmp: FORCE $(ORIGINALS)

org/%.$(OEXT): res/%.$(OEXT)
	echo $<
	@diff -s $< $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm bin/*.o $(EXECUTABLE)
	rm res/*.$(OEXT)

FORCE:
