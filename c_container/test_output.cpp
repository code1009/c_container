/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <stdio.h>

#include "test_output.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace test
{
    /////////////////////////////////////////////////////////////////////////
    //=======================================================================
    output out;
    text_endl tendl;





    /////////////////////////////////////////////////////////////////////////
    //=======================================================================
    text_endl::text_endl()
        : _value("\n")
    {
	}

    //=======================================================================
    text_index::text_index(size_t v)
        : _value(v)
    {
	}



    /////////////////////////////////////////////////////////////////////////
    //=======================================================================
    output::output()
    {
    }

    //=======================================================================
    output& output::operator<<(char v)
    {
        printf("%3d", static_cast<int>(v));
        return *this;
    }

    output& output::operator<<(short int v)
    {
        printf("%3hd", v);
        return *this;
    }

    output& output::operator<<(int v)
    {
        printf("%3d", v);
        return *this;
    }

    output& output::operator<<(long int v)
    {
        printf("%3ld", v);
        return *this;
    }

    output& output::operator<<(long long int v)
    {
        printf("%lld", v);
        return *this;
    }

    output& output::operator<<(unsigned char v)
    {
        printf("%u", static_cast<unsigned int>(v));
        return *this;
    }

    output& output::operator<<(unsigned short int v)
    {
        printf("%hu", v);
        return *this;
    }

    output& output::operator<<(unsigned int v)
    {
        printf("%u", v);
        return *this;
    }

    output& output::operator<<(unsigned long int v)
    {
        printf("%lu", v);
        return *this;
    }

    output& output::operator<<(unsigned long long int v)
    {
        printf("%llu", v);
        return *this;
    }

    output& output::operator<<(float v)
    {
        printf("%g", static_cast<double>(v));
        return *this;
    }

    output& output::operator<<(double v)
    {
        printf("%g", v);
        return *this;
    }

    output& output::operator<<(bool v)
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

    output& output::operator<<(const char* v)
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

    output& output::operator<<(const void* v)
    {
        printf("%p", v);

        return *this;
    }

    output& output::operator<<(const text_index& v)
    {
		// 64bit or 32bit 겸용시 %zu 사용
        printf("%zu", v._value);

        return *this;
    }

    output& output::operator<<(const text_endl& v)
    {
        printf(v._value);

        return *this;
    }
}




