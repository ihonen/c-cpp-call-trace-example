#pragma once

// -----------------------------------------------------------------------------

class Base
{
public:

    ~Base();

    virtual void virtual_foo();
};

class Derived : public Base
{
public:

    ~Derived();

    static void static_foo();

    void nonvirtual_foo();

    void virtual_foo() override;
};
