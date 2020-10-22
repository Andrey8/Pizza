#include <QtTest>

#include "../../Base/Table.h"
#include "../../Base/TableCell.h"

#include <vector>



namespace Tests
{
    namespace BaseTests
    {
        class TableTester : public QObject
        {
            Q_OBJECT

        public:
            TableTester()
            {
                m_data = {
                    { 23, 7, 31, 17, 3 },
                    { 5, 24, 54, 2, 11 },
                    { 83, 41, 7, 9, 15 } };
                m_incorrectData = {
                    { 4, 5, 21, 53 },
                    { 3, 7, 45 },
                    { 25, 5, 78, 1 } };
            }

            ~TableTester() {}

        private slots:
            void TestDefaultConstructor();
            void TestNotFailedDataConstructor();
            void TestFailedDataConstructor();
            void TestConstAccessor();
            void TestModifyingAccessor();

        private:
            std::vector< std::vector< int > > m_data;
            std::vector< std::vector< int > > m_incorrectData;
        };
    }
}



void Tests::BaseTests::TableTester::TestDefaultConstructor()
{
    Base::Table< int > t( 5, 3 );

    QVERIFY( t.GetWidth() == 5 );
    QVERIFY( t.GetHeight() == 3 );
}

void Tests::BaseTests::TableTester::TestNotFailedDataConstructor()
{
    Base::Table< int > t( m_data );

    QVERIFY( t.GetWidth() == 5 );
    QVERIFY( t.GetHeight() == 3 );
}

void Tests::BaseTests::TableTester::TestFailedDataConstructor()
{
    QVERIFY_EXCEPTION_THROWN( { Base::Table< int > t( m_incorrectData ); }, std::invalid_argument );
}

void Tests::BaseTests::TableTester::TestConstAccessor()
{
    Base::Table< int > t( m_data );

    for ( int i = 1; i <= t.GetHeight(); ++i )
    {
        for ( int j = 1; j <= t.GetWidth(); ++j )
        {
            QVERIFY( t.GetItem( i, j ) == m_data[ i - 1 ][ j - 1 ] );
        }
    }
}

void Tests::BaseTests::TableTester::TestModifyingAccessor()
{
    Base::Table< int > t( m_data );

    int const value = 111;

    for ( int i = 1; i <= t.GetHeight(); ++i )
    {
        for ( int j = 1; j <= t.GetWidth(); ++j )
        {
            t.SetItem( i, j, value );

            QVERIFY( t.GetItem( i, j ) == value );
        }
    }
}



QTEST_APPLESS_MAIN( Tests::BaseTests::TableTester )

#include "tst_tabletester.moc"
