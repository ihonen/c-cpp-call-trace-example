# C/C++ function call trace example

This example demonstrates how to trace and log C/C++ function calls without
writing extra code in the traced functions themselves. This also provides us a
means of tracing the total number of function calls as well as the lengths
of function call chains.

Feel free to use the provided code as you please.

### Notes

* All functions **compiled as part of the program** are traced – even static and inline functions
* Static and inline function names can't be resolved via the method used in this example
* Calls to dynamic library functions are not traced
* C++ symbols are demangled if `trace.c` is compiled as C++

### Future improvements

Look into the following:
* Resolve static and inline function names
* Display source file names and line numbers

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
<TRACE> ---> main [0x55c2edee8270] 0

---------------------------------------------------------------
C LINKAGE
---------------------------------------------------------------

*** Static functions ***

<TRACE>  ---> ??? +0x28d0 [0x55c2edee88d0] 1
<TRACE>   ---> ??? +0x28a0 [0x55c2edee88a0] 2
<TRACE>   <--- ??? +0x28a0 [0x55c2edee88a0] 2
<TRACE>  <--- ??? +0x28d0 [0x55c2edee88d0] 1

*** Inline functions ***

<TRACE>  ---> ??? +0x2820 [0x55c2edee8820] 1
<TRACE>   ---> ??? +0x2870 [0x55c2edee8870] 2
<TRACE>   <--- ??? +0x2870 [0x55c2edee8870] 2
<TRACE>  <--- ??? +0x2820 [0x55c2edee8820] 1

*** Extern functions ***

<TRACE>  ---> extern_foo [0x55c2edee87d0] 1
<TRACE>   ---> extern_bar [0x55c2edee87a0] 2
<TRACE>   <--- extern_bar [0x55c2edee87a0] 2
<TRACE>  <--- extern_foo [0x55c2edee87d0] 1

---------------------------------------------------------------
C++ LINKAGE
---------------------------------------------------------------

*** Throwing functions ***

<TRACE>  ---> throwing_foo() [0x55c2edee8b10] 1
<TRACE>   ---> std::exception::exception() [0x55c2edee8b90] 2
<TRACE>   <--- std::exception::exception() [0x55c2edee8b90] 2
<TRACE>  <--- throwing_foo() [0x55c2edee8b10] 1

*** Template functions ***

<TRACE>  ---> void template_foo<int>() [0x55c2edee8910] 1
<TRACE>  <--- void template_foo<int>() [0x55c2edee8910] 1

*** Constructors ***

<TRACE>  ---> Derived::Derived() [0x55c2edee8980] 1
<TRACE>   ---> Base::Base() [0x55c2edee8940] 2
<TRACE>   <--- Base::Base() [0x55c2edee8940] 2
<TRACE>  <--- Derived::Derived() [0x55c2edee8980] 1

*** Static member functions ***

<TRACE>  ---> Derived::static_foo() [0x55c2edee8a50] 1
<TRACE>  <--- Derived::static_foo() [0x55c2edee8a50] 1

*** Member functions ***

<TRACE>  ---> Derived::nonvirtual_foo() [0x55c2edee8a80] 1
<TRACE>  <--- Derived::nonvirtual_foo() [0x55c2edee8a80] 1

*** Virtual member functions ***

<TRACE>  ---> Derived::virtual_foo() [0x55c2edee8a20] 1
<TRACE>  <--- Derived::virtual_foo() [0x55c2edee8a20] 1

*** Destructors ***

<TRACE>  ---> Derived::~Derived() [0x55c2edee8ab0] 1
<TRACE>   ---> Base::~Base() [0x55c2edee89f0] 2
<TRACE>   <--- Base::~Base() [0x55c2edee89f0] 2
<TRACE>  <--- Derived::~Derived() [0x55c2edee8ab0] 1

---------------------------------------------------------------

<TRACE> <--- main [0x55c2edee8270] 0
```
