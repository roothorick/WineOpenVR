CXX = x86_64-w64-mingw32-g++

CXXFLAGS = -I../openvr/headers
LDFLAGS = -L../openvr/lib/win64

dx11_submit.exe:
	$(CXX) -o dx11_submit.exe dx11_submit.cpp $(CXXFLAGS) $(LDFLAGS) -ldxgi -ld3d11 -lopenvr_api
