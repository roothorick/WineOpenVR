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
	\
	ivrsystem/ivrsystem_009.cpp \
	ivrsystem/ivrsystem_010.cpp \
	ivrsystem/ivrsystem_011.cpp \
	ivrsystem/ivrsystem_012.cpp \
	ivrsystem/ivrsystem_014.cpp \
	ivrsystem/ivrsystem_015.cpp \
	ivrsystem/ivrsystem_016.cpp \
	\
	ivrapplications/ivrapplications_002.cpp \
	ivrapplications/ivrapplications_003.cpp \
	ivrapplications/ivrapplications_004.cpp \
	ivrapplications/ivrapplications_005.cpp \
	ivrapplications/ivrapplications_006.cpp \
	\
	ivrsettings/ivrsettings_001.cpp \
	ivrsettings/ivrsettings_002.cpp \
	\
	ivrchaperone/ivrchaperone_003.cpp \
	\
	ivrchaperonesetup/ivrchaperonesetup_004.cpp \
	ivrchaperonesetup/ivrchaperonesetup_005.cpp \
	\
	ivrcompositor/ivrcompositor_011.cpp \
	ivrcompositor/ivrcompositor_012.cpp \
	ivrcompositor/ivrcompositor_013.cpp \
	ivrcompositor/ivrcompositor_014.cpp \
	ivrcompositor/ivrcompositor_015.cpp \
	ivrcompositor/ivrcompositor_016.cpp \
	ivrcompositor/ivrcompositor_018.cpp \
	ivrcompositor/ivrcompositor_019.cpp \
	ivrcompositor/ivrcompositor_020.cpp \
	\
	ivrnotifications/ivrnotifications_002.cpp \
	\
	ivroverlay/ivroverlay_008.cpp \
	ivroverlay/ivroverlay_010.cpp \
	ivroverlay/ivroverlay_011.cpp \
	ivroverlay/ivroverlay_012.cpp \
	ivroverlay/ivroverlay_013.cpp \
	ivroverlay/ivroverlay_014.cpp \
	ivroverlay/ivroverlay_016.cpp \
	\
	ivrrendermodels/ivrrendermodels_002.cpp \
	ivrrendermodels/ivrrendermodels_004.cpp \
	ivrrendermodels/ivrrendermodels_005.cpp \
	\
	ivrextendeddisplay/ivrextendeddisplay_001.cpp \
	\
	ivrtrackedcamera/ivrtrackedcamera_002.cpp \
	ivrtrackedcamera/ivrtrackedcamera_003.cpp \
	\
	ivrscreenshots/ivrscreenshots_001.cpp \
	\
	ivrresources/ivrresources_001.cpp \
	\
	ivrdrivermanager/ivrdrivermanager_001.cpp

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
	rm -rf $(OBJECTS_32) $(OBJECTS_64) $(DLL_32) $(DLL_64)

$(wildcard bin*/ivrsystem/*.o):          src/ivrsystem/ivrsystem.h
$(wildcard bin*/ivrapplications/*.o):    src/ivrapplications/ivrapplications.h
$(wildcard bin*/ivrsettings/*.o):        src/ivrsettings/ivrsettings.h
$(wildcard bin*/ivrchaperone/*.o):       src/ivrchaperone/ivrchaperone.h
$(wildcard bin*/ivrchaperonesetup/*.o):  src/ivrchaperonesetup/ivrchaperonesetup.h
$(wildcard bin*/ivrcompositor/*.o):      src/ivrcompositor/ivrcompositor.h
$(wildcard bin*/ivrnotifications/*.o):   src/ivrnotifications/ivrnotifications.h
$(wildcard bin*/ivroverlay/*.o):         src/ivroverlay/ivroverlay.h
$(wildcard bin*/ivrrendermodels/*.o):    src/ivrrendermodels/ivrrendermodels.h
$(wildcard bin*/ivrextendeddisplay/*.o): src/ivrextendeddisplay/ivrextendeddisplay.h
$(wildcard bin*/ivrtrackedcamera/*.o):   src/ivrtrackedcamera/ivrtrackedcamera.h
$(wildcard bin*/ivrscreenshots/*.o):     src/ivrscreenshots/ivrscreenshots.h
$(wildcard bin*/ivrresources/*.o):       src/ivrresources/ivrresources.h
$(wildcard bin*/ivrdrivermanager/*.o):   src/ivrdrivermanager/ivrdrivermanager.h

$(DLL_32): $(OBJECTS_32) $(SPECFILE)
	$(CXX) $(SPECFILE) -o $@ $(OBJECTS_32) $(LDFLAGS_32)

$(DLL_64): $(OBJECTS_64) $(SPECFILE)
	$(CXX) $(SPECFILE) -o $@ $(OBJECTS_64) $(LDFLAGS_64)

$(OBJECTS_32): bin32/%.o: src/%.cpp src/*.h
	@mkdir -p bin32
	$(CXX) -c $(CXXFLAGS_32) -o $@ $<

$(OBJECTS_64): bin64/%.o: src/%.cpp src/*.h
	@mkdir -p bin64
	$(CXX) -c $(CXXFLAGS_64) -o $@ $<
