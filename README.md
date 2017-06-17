# WineOpenVR
Wrapper connecting Windows apps in Wine to native SteamVR

## C++ ABI differences
For 32bit i.e. x86, we can't rely solely on `__attribute__((thiscall))` for methods that return complex types due to what appears to be a bug in GCC.

In MSVC land (i.e. "thiscall"), when a member method returns a complex type, the caller allocates space on the stack for the return value and then pushes a pointer to that location onto the stack as a hidden first argument. Just like in methods returning primitives, the `ECX` register contains the `this` pointer. GCC gets this switched around, thinking the end of the stack contains the `this` pointer, and `ECX` contains the return value destination.

Our workaround is to pretend the method returns nothing, and make the first argument the return value pointer. That is, `FooMatrix_t GetFooMatrix(int index)` becomes `void GetFooMatrix(FooMatrix_t* ret, int index)`. GCC will treat the top of the stack as the first argument, which does what we *actually* want, and makes `ECX` once again the `this` pointer. Methods returning primitives work with `__attribute__((thiscall))` as-is, because the return value is passed via registers.

To avoid having to manually desecrate the vtable, we have a hidden "clone" class with the same virtual methods in the same order, except the methods returning complex types are replaced with modified versions using the explicit return pointer hack described above. Then our proxy class derives from the clone, not the real one.
