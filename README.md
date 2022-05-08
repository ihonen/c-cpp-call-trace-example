# C/C++ function call trace example

This example demonstrates how to trace and log C/C++ function calls without
writing extra code in the traced functions themselves. This also gives us a way of tracing the total number of function calls as well as the lengths of function call chains.

Feel free to use the provided code as you please.

### Notes

* All functions **compiled as part of the program** are traced – even static and inline functions
* Static and inline function names can't be resolved via the method used in this example
* Calls to dynamic library functions are not traced
* C++ symbols are mangled – they could be demangled, but that would likely incur a significant performance penalty

### Future improvements

Look into the following:
* Resolve static and inline function names
* Display source file names and line numbers
* Demangle C++ symbols

The `addr2line` utility could be useful for this if the source code is available
in the runtime environment. It is very slow, though.

### Compile and run (Linux + GCC only)

Commands:
```
make example
./example.out
```

Possible output:
```
<TRACE> ---> main [0x55e92881b210] 0

---------------------------------------------------------------
C LINKAGE
---------------------------------------------------------------

*** Static functions ***

<TRACE>  ---> ??? +0x2870 [0x55e92881b870] 1
<TRACE>   ---> ??? +0x2840 [0x55e92881b840] 2
<TRACE>   <--- ??? +0x2840 [0x55e92881b840] 2
<TRACE>  <--- ??? +0x2870 [0x55e92881b870] 1

*** Inline functions ***

<TRACE>  ---> ??? +0x27c0 [0x55e92881b7c0] 1
<TRACE>   ---> ??? +0x2810 [0x55e92881b810] 2
<TRACE>   <--- ??? +0x2810 [0x55e92881b810] 2
<TRACE>  <--- ??? +0x27c0 [0x55e92881b7c0] 1

*** Extern functions ***

<TRACE>  ---> extern_foo [0x55e92881b770] 1
<TRACE>   ---> extern_bar [0x55e92881b740] 2
<TRACE>   <--- extern_bar [0x55e92881b740] 2
<TRACE>  <--- extern_foo [0x55e92881b770] 1

---------------------------------------------------------------
C++ LINKAGE
---------------------------------------------------------------

*** Throwing functions ***

<TRACE>  ---> _Z12throwing_foov [0x55e92881bab0] 1
<TRACE>   ---> _ZNSt9exceptionC1Ev [0x55e92881bb30] 2
<TRACE>   <--- _ZNSt9exceptionC1Ev [0x55e92881bb30] 2
<TRACE>  <--- _Z12throwing_foov [0x55e92881bab0] 1

*** Template functions ***

<TRACE>  ---> _Z12template_fooIiEvv [0x55e92881b8b0] 1
<TRACE>  <--- _Z12template_fooIiEvv [0x55e92881b8b0] 1

*** Constructors ***

<TRACE>  ---> _ZN7DerivedC1Ev [0x55e92881b920] 1
<TRACE>   ---> _ZN4BaseC1Ev [0x55e92881b8e0] 2
<TRACE>   <--- _ZN4BaseC1Ev [0x55e92881b8e0] 2
<TRACE>  <--- _ZN7DerivedC1Ev [0x55e92881b920] 1

*** Static member functions ***

<TRACE>  ---> _ZN7Derived10static_fooEv [0x55e92881b9f0] 1
<TRACE>  <--- _ZN7Derived10static_fooEv [0x55e92881b9f0] 1

*** Member functions ***

<TRACE>  ---> _ZN7Derived14nonvirtual_fooEv [0x55e92881ba20] 1
<TRACE>  <--- _ZN7Derived14nonvirtual_fooEv [0x55e92881ba20] 1

*** Virtual member functions ***

<TRACE>  ---> _ZN7Derived11virtual_fooEv [0x55e92881b9c0] 1
<TRACE>  <--- _ZN7Derived11virtual_fooEv [0x55e92881b9c0] 1

*** Destructors ***

<TRACE>  ---> _ZN7DerivedD2Ev [0x55e92881ba50] 1
<TRACE>   ---> _ZN4BaseD1Ev [0x55e92881b990] 2
<TRACE>   <--- _ZN4BaseD1Ev [0x55e92881b990] 2
<TRACE>  <--- _ZN7DerivedD2Ev [0x55e92881ba50] 1

---------------------------------------------------------------

<TRACE> <--- main [0x55e92881b210] 0
```
