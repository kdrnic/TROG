OBJDIR=build/obj/
DBGOBJDIR=build/objdbg/
CFLAGS2=$(CFLAGS)
CFLAGS2+=-Wall -Wuninitialized

ifeq ($(CC),clang)
	ifeq ($(OS),Windows_NT)
		CFLAGS2+=-target i686-pc-windows-gnu
	endif
endif

SRCDIRS=src src/enemies src/items src/libs src/miscEntities
CFILES=$(wildcard $(addsuffix /*.c,$(SRCDIRS)))
CPPFILES=$(wildcard  $(addsuffix /*.cpp,$(SRCDIRS)))
HEADERFILES=$(wildcard $(addsuffix /*.hpp,$(SRCDIRS)) $(addsuffix /*.h,$(SRCDIRS)))
OFILES=$(patsubst %.c,%.o,$(CFILES)) $(patsubst %.cpp,%.o,$(CPPFILES))
DFILES=$(patsubst %.c,%.d,$(CFILES)) $(patsubst %.cpp,%.d,$(CPPFILES))
DEPDIRS=$(addprefix deps/,$(SRCDIRS))
EXISTING_DFILES=$(wildcard  $(addsuffix /*.d,$(DEPDIRS)))
TOBUILD_DFILES=$(addprefix deps/,$(DFILES))

OBJECTS=$(addprefix $(OBJDIR),$(OFILES))
OBJECTS_DBG=$(addprefix $(DBGOBJDIR),$(OFILES))

ifeq ($(USE_LOADPNG),1)
	LDPNG_LIBS=-lloadpng -lpng -lz
	CFLAGS2+=-DUSE_LOADPNG
else
	LDPNG_LIBS=
endif

ifeq ($(STATIC_LIBGCC),1)
	LINK_FLAGS=-static -static-libgcc
else
	LINK_FLAGS=
endif

INCLUDE_PATHS=$(addprefix -I,$(SRCDIRS))
LINK_PATHS=

ifeq ($(OS),Windows_NT)
	INCLUDE_PATHS+=-I$(ALLEGRO_PATH)include -I$(LDPNG_PATH)include
	LINK_PATHS+=-L$(ALLEGRO_PATH)lib
	ifeq ($(USE_LOADPNG),1)
		LINK_PATHS+=-L$(LDPNG_PATH)lib
	endif
endif

include $(EXISTING_DFILES)

deps/%.d: %.c
	$(CC) $(INCLUDE_PATHS) -MM $< > $@

deps/%.d: %.cpp
	$(CC) $(INCLUDE_PATHS) -MM $< > $@

$(OBJDIR)%.o: %.c $(HEADERFILES)
	$(CC) $(INCLUDE_PATHS) $(CFLAGS2) $< -c -o $@

$(DBGOBJDIR)%.o: %.c $(HEADERFILES)
	$(CC) $(INCLUDE_PATHS) -g $(CFLAGS2) $< -c -o $@

$(OBJDIR)%.o: %.cpp $(HEADERFILES)
	$(CXX) $(INCLUDE_PATHS) $(CFLAGS2) $< -c -o $@

$(DBGOBJDIR)%.o: %.cpp $(HEADERFILES)
	$(CXX) $(INCLUDE_PATHS) -g $(CFLAGS2) $< -c -o $@

clean:
	rm -f -r $(OBJDIR)
	rm -f -r $(DBGOBJDIR)

build/obj/src:
	mkdir build\obj\src
	xcopy /t /e src build\obj\src\

build/objdbg/src:
	mkdir build\objdbg\src
	xcopy /t /e src build\objdbg\src\

build/obj:
	mkdir build\obj

build/objdbg:
	mkdir build\objdbg

build:
	mkdir build

deps:
	xcopy /t /e src deps\src\

objs: build/obj build/obj/src $(OBJECTS)
objsdbg: build/objdbg build/objdbg/src $(OBJECTS_DBG)

regular: build objs
	$(CXX) $(LINK_PATHS) $(LINK_FLAGS) $(CFLAGS2) $(OBJECTS) -o build/game.exe $(LDPNG_LIBS) -lalleg -lm

debug: build objsdbg
	$(CXX) $(LINK_PATHS) $(LINK_FLAGS) -g $(CFLAGS2) $(OBJECTS_DBG) -o build/game_dbg.exe $(LDPNG_LIBS) -lalleg -lm

depend: deps $(TOBUILD_DFILES)
