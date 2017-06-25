# WineOpenVR
Wrapper connecting Windows apps in Wine to native SteamVR

## Installation and use

1. Install Wine, Steam, and Linux SteamVR. **Do not install Windows SteamVR in Wine.** Make sure SteamVR is working correctly (i.e. Home starts up okay and you get an image in the headset).
2. Clone repo and compile. (`cd src && make`)
3. Put `openvr/lib/linux32/libopenvr_api.so` in your `LD_LIBRARY_PATH` and `src/openvr_api.dll.so` in your `WINEDLLPATH`.
4. Run applications with `~/.local/share/Steam/ubuntu12_32/steam-runtime/run.sh wine vrapp.exe`

## C++ ABI differences
For 32bit i.e. x86, we can't rely solely on `__attribute__((thiscall))` for methods that return complex types due to what appears to be a bug in GCC.

In MSVC land (i.e. "thiscall"), when a member method returns a complex type, the caller allocates space on the stack for the return value and then pushes a pointer to that location onto the stack as a hidden first argument. Just like in methods returning primitives, the `ECX` register contains the `this` pointer. GCC gets this switched around, thinking the end of the stack contains the `this` pointer, and `ECX` contains the return value destination.

Our workaround is to pretend the method returns nothing, and make the first argument the return value pointer. That is, `FooMatrix_t GetFooMatrix(int index)` becomes `void GetFooMatrix(FooMatrix_t* ret, int index)`. GCC will treat the top of the stack as the first argument, which does what we *actually* want, and makes `ECX` once again the `this` pointer. Methods returning primitives work with `__attribute__((thiscall))` as-is, because the return value is passed via registers.

Interestingly, the same workaround is required in 64bit i.e. amd64/x86-64. It appears that MSVC and GCC disagree on which hidden argument comes first. MSVC puts the `this` pointer before the return value pointer, but GCC puts the return value pointer before the `this` pointer. This is *also* reconciled by making the return value pointer an explicit argument.

To avoid having to manually desecrate the vtable, we have a hidden "clone" class with the same virtual methods in the same order, except the methods returning complex types are replaced with modified versions using the explicit return pointer hack described above. Then our proxy class derives from the clone, not the real one.
