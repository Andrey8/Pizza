#pragma once



namespace Base
{
    template < typename T, int w, int h >
    class Matrix
    {
    public:
        Matrix( T ** data );
        Matrix() {}
        //Matrix( int width, int height );

        int GetWidth() const { return w; }
        int GetHeight() const { return h; }
    private:

    };

    void TestMatrix()
    {
        Matrix< int, 3, 4 > m1();
    }
}
