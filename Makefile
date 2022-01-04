CC = g++
CFLAGS = -g3 -Wall -lm
LDFLAGS = -lglut -lGLU -lGL
SOURCES = main.cpp world.cpp abot.cpp genes/changeDirAbs.cpp genes/changeDirRel.cpp genes/createBot.cpp genes/eatAbsDir.cpp genes/eatRelDir.cpp genes/flattenedHor.cpp genes/fullAround.cpp genes/giveAbsDir.cpp genes/giveRelDir.cpp genes/isHealthGrow.cpp genes/isMineralGrow.cpp genes/lookAbsDir.cpp genes/lookRelDir.cpp genes/mineralToEnergy.cpp genes/mutate.cpp genes/myHealth.cpp genes/myLevel.cpp genes/myLifeTime.cpp genes/myMineral.cpp genes/photosynthesis.cpp genes/stepAbsDir.cpp genes/stepRelDir.cpp
OBJECTS = $(addprefix obj/, $(SOURCES:.cpp=.o))
EXE = _lab

all: obj $(SOURCES) $(EXE)

obj:
	mkdir obj
	mkdir obj/genes

$(EXE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) $(CFLAGS) -o $@

obj/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj $(EXE)
