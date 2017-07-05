# Change to the path of your Wine libraries
WINEPATH_32=/opt/wine-staging/lib
WINEPATH_64=/opt/wine-staging/lib64

CXXFLAGS=-Isrc
CXXFLAGS_32=-m32 $(CXXFLAGS)
CXXFLAGS_64=$(CXXFLAGS)

LDFLAGS=-shared -lopenvr_api
LDFLAGS_32=-Lopenvr/bin/linux32 -L$(WINEPATH_32) -L$(WINEPATH_32)/wine -m32 $(LDFLAGS)
LDFLAGS_64=-Lopenvr/bin/linux64 -L$(WINEPATH_64) -L$(WINEPATH_64)/wine $(LDFLAGS)

SOURCES= \
	wovr_exports.cpp \
	d3dproxy.cpp \
	ivrsystem.cpp \
	ivrapplications.cpp \
	ivrsettings.cpp \
	ivrchaperone.cpp \
	ivrchaperonesetup.cpp \
	ivrcompositor.cpp \
	ivrnotifications.cpp \
	ivroverlay.cpp \
	ivrrendermodels.cpp \
	ivrextendeddisplay.cpp \
	ivrtrackedcamera.cpp \
	ivrscreenshots.cpp \
	ivrresources.cpp

CC=winegcc
CXX=wineg++

DLL_32=bin32/openvr_api.dll.so
DLL_64=bin64/openvr_api.dll.so
SPECFILE=src/openvr_api.spec

###############################################################################

OBJECTS_32=$(SOURCES:%.cpp=bin32/%.o)
OBJECTS_64=$(SOURCES:%.cpp=bin64/%.o)

all: $(DLL_32) $(DLL_64)

clean:
	rm -rf bin32 bin64

$(DLL_32): $(OBJECTS_32) $(SPECFILE) bin32
	$(CXX) $(LDFLAGS_32) $(SPECFILE) -o $@ $(OBJECTS_32)

$(DLL_64): $(OBJECTS_64) $(SPECFILE) bin64
	$(CXX) $(LDFLAGS_64) $(SPECFILE) -o $@ $(OBJECTS_64)


$(OBJECTS_32): bin32/%.o: src/%.cpp bin32
	$(CXX) -c $(CXXFLAGS_32) -o $@ $<

$(OBJECTS_64): bin64/%.o: src/%.cpp bin64
	$(CXX) -c $(CXXFLAGS_64) -o $@ $<


bin32 bin64:
	mkdir -p $@
