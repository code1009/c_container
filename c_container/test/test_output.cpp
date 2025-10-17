/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <stdio.h>

#include "test_output.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
test_output test_out;
test_text_endl test_tendl;
test_text_index test_tindex;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
test_text_endl::test_text_endl() : _value("\n") {}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
test_text_index::test_text_index() : _value(0) {}
test_text_index& test_text_index::operator()(size_t v)
{ 
    _value = v; 
    return *this; 
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
test_output& test_output::operator<<(char v)
{
    printf("%3d", static_cast<int>(v));
    return *this;
}

test_output& test_output::operator<<(short int v)
{
    printf("%3hd", static_cast<int>(v));
    return *this;
}

test_output& test_output::operator<<(int v)
{
    printf("%3d", static_cast<int>(v));
    return *this;
}

test_output& test_output::operator<<(long int v)
{
    printf("%3ld", static_cast<int>(v));
    return *this;
}

test_output& test_output::operator<<(long long int v)
{
    printf("%3lld", v);
    return *this;
}

test_output& test_output::operator<<(unsigned char v)
{
    printf("%3u", static_cast<unsigned int>(v));
    return *this;
}

test_output& test_output::operator<<(unsigned short int v)
{
    printf("%3hu", static_cast<unsigned int>(v));
    return *this;
}

test_output& test_output::operator<<(unsigned int v)
{
    printf("%3u", static_cast<unsigned int>(v));
    return *this;
}

test_output& test_output::operator<<(unsigned long int v)
{
    printf("%3lu", static_cast<unsigned int>(v));
    return *this;
}

test_output& test_output::operator<<(unsigned long long int v)
{
    printf("%3llu", v);
    return *this;
}

test_output& test_output::operator<<(float v)
{
    printf("%g", static_cast<double>(v));
    return *this;
}

test_output& test_output::operator<<(double v)
{
    printf("%g", v);
    return *this;
}

test_output& test_output::operator<<(bool v)
{
    if (v)
    {
        printf("true");
    }
    else
    {
        printf("false");
    }

    return *this;
}

test_output& test_output::operator<<(const char* v)
{
    if (!v)
    {
        printf("(null)");
    }
    else
    {
        printf(v);
    }

    return *this;
}

test_output& test_output::operator<<(const void* v)
{
    printf("%p", v);

    return *this;
}

test_output& test_output::operator<<(const test_text_index& v)
{
	// 64bit or 32bit 겸용시 %zu 사용
    printf(" [%3zu] ", v._value);

    return *this;
}

test_output& test_output::operator<<(const test_text_endl& v)
{
    printf(v._value);

    return *this;
}



