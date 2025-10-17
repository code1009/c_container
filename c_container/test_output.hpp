#ifndef test_output_hpp
#define test_output_hpp




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace test
{
    //=======================================================================
    class text_endl
    {
    public:
        const char* _value;
    public:
        explicit text_endl();
    };

    //=======================================================================
    class text_index
    {
    public:
        size_t _value;
    public:
        explicit text_index(size_t v);
    };

    //=======================================================================
    class output
    {
    public:

    public:
        explicit output();

    public:
        output& operator<<(char v);
        output& operator<<(short int v);
        output& operator<<(int v);
        output& operator<<(long int v);
        output& operator<<(long long int v);

        output& operator<<(unsigned char v);
        output& operator<<(unsigned short int v);
        output& operator<<(unsigned int v);
        output& operator<<(unsigned long int v);
        output& operator<<(unsigned long long int v);

        output& operator<<(float v);
        output& operator<<(double v);

        output& operator<<(bool v);
        output& operator<<(const char* v);
        output& operator<<(const void* v);

    public:
        output& operator<<(const text_index& v);
        output& operator<<(const text_endl& v);
    };

    //=======================================================================
    extern output out;
	extern text_endl tendl;

/////////////////////////////////////////////////////////////////////////////
//===========================================================================
} // namespace test





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#endif // test_output_hpp