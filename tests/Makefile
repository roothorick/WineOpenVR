CXX = i686-w64-mingw32-g++

CXXFLAGS = -I../openvr/headers -m32 -static
LDFLAGS = -L../openvr/lib/win32

dx11_submit.exe: dx11_submit.cpp
	$(CXX) -o dx11_submit.exe dx11_submit.cpp $(CXXFLAGS) $(LDFLAGS) -ldxgi -ld3d11 -lopenvr_api
