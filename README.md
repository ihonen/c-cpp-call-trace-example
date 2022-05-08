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
<TRACE> ---> main [0x564e4b8f4270] 0

---------------------------------------------------------------
C LINKAGE
---------------------------------------------------------------

*** Static functions ***

<TRACE>  ---> ??? +0x2850 [0x564e4b8f4850] 1
<TRACE>   ---> ??? +0x2820 [0x564e4b8f4820] 2
<TRACE>   <--- ??? +0x2820 [0x564e4b8f4820] 2
<TRACE>  <--- ??? +0x2850 [0x564e4b8f4850] 1

*** Inline functions ***

<TRACE>  ---> ??? +0x27a0 [0x564e4b8f47a0] 1
<TRACE>   ---> ??? +0x27f0 [0x564e4b8f47f0] 2
<TRACE>   <--- ??? +0x27f0 [0x564e4b8f47f0] 2
<TRACE>  <--- ??? +0x27a0 [0x564e4b8f47a0] 1

*** Extern functions ***

<TRACE>  ---> extern_foo [0x564e4b8f4dd0] 1
<TRACE>   ---> extern_bar [0x564e4b8f4da0] 2
<TRACE>   <--- extern_bar [0x564e4b8f4da0] 2
<TRACE>  <--- extern_foo [0x564e4b8f4dd0] 1

---------------------------------------------------------------
C++ LINKAGE
---------------------------------------------------------------

*** Throwing functions ***

<TRACE>  ---> mynamespace::throwing_foo() [0x564e4b8f4f40] 1
<TRACE>   ---> std::exception::exception() [0x564e4b8f4fc0] 2
<TRACE>   <--- std::exception::exception() [0x564e4b8f4fc0] 2
<TRACE>  <--- mynamespace::throwing_foo() [0x564e4b8f4f40] 1

*** Template functions ***

<TRACE>  ---> void mynamespace::template_foo<int>() [0x564e4b8f4890] 1
<TRACE>  <--- void mynamespace::template_foo<int>() [0x564e4b8f4890] 1

*** Constructors ***

<TRACE>  ---> mynamespace::Derived::Derived() [0x564e4b8f4900] 1
<TRACE>   ---> mynamespace::Base::Base() [0x564e4b8f48c0] 2
<TRACE>   <--- mynamespace::Base::Base() [0x564e4b8f48c0] 2
<TRACE>  <--- mynamespace::Derived::Derived() [0x564e4b8f4900] 1

*** Static member functions ***

<TRACE>  ---> mynamespace::Derived::static_foo() [0x564e4b8f4e80] 1
<TRACE>  <--- mynamespace::Derived::static_foo() [0x564e4b8f4e80] 1

*** Member functions ***

<TRACE>  ---> mynamespace::Derived::nonvirtual_foo() [0x564e4b8f4eb0] 1
<TRACE>  <--- mynamespace::Derived::nonvirtual_foo() [0x564e4b8f4eb0] 1

*** Virtual member functions ***

<TRACE>  ---> mynamespace::Base::virtual_foo() [0x564e4b8f4e50] 1
<TRACE>  <--- mynamespace::Base::virtual_foo() [0x564e4b8f4e50] 1

*** Destructors ***

<TRACE>  ---> mynamespace::Derived::~Derived() [0x564e4b8f4ee0] 1
<TRACE>   ---> mynamespace::Base::~Base() [0x564e4b8f4e20] 2
<TRACE>   <--- mynamespace::Base::~Base() [0x564e4b8f4e20] 2
<TRACE>  <--- mynamespace::Derived::~Derived() [0x564e4b8f4ee0] 1

---------------------------------------------------------------

<TRACE> <--- main [0x564e4b8f4270] 0
```
