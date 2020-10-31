#include <QtTest>

#include "../../Algorithms/TableAlgorithms.h"



namespace Tests
{
    namespace AlgorithmsTests
    {
        using CCData = Algorithms::TableAlgorithms::CrossCenterData;

        class TableAlgorithmsTester : public QObject
        {
            Q_OBJECT

        public:
            TableAlgorithmsTester() {}
            ~TableAlgorithmsTester() {}

        private slots:
            void TestSplitIntoCrossesAlgorithm_1();
            void TestSplitIntoCrossesAlgorithm_2();
            void TestSplitIntoCrossesAlgorithm_3();
            void TestSplitIntoCrossesAlgorithm_4();
            void TestSplitIntoCrossesAlgorithm_5();
        };



        void TableAlgorithmsTester::TestSplitIntoCrossesAlgorithm_1()
        {
            CCData ccd1( { 1, 1 }, 3 );

            CCData ccd2( { 2, 3 }, 1 );

            std::vector< CCData > data = { ccd1, ccd2 };
            Algorithms::TableAlgorithms::SplitTableIntoCrosses(
                        3, 2, data );

            QVERIFY( data[ 0 ].count == 3 );
            QVERIFY( data[ 0 ].rightCells.size() == 2 );
            QVERIFY( data[ 0 ].upperCells.size() == 1 );
            QVERIFY( data[ 1 ].count == 1 );
            QVERIFY( data[ 1 ].leftCells.size() == 1 );

        }

        void TableAlgorithmsTester::TestSplitIntoCrossesAlgorithm_2()
        {
            CCData ccd1( { 1, 2 }, 4 );
            CCData ccd2( { 2, 5 }, 3 );
            CCData ccd3( { 3, 1 }, 2 );
            CCData ccd4( { 3, 3 }, 2 );

            std::vector< CCData > data = { ccd1, ccd2, ccd3, ccd4 };
            Algorithms::TableAlgorithms::SplitTableIntoCrosses(
                        5, 3, data );

            QVERIFY( data[ 0 ].count == 4 );
            QVERIFY( data[ 1 ].count == 3 );
            QVERIFY( data[ 2 ].count == 2 );
            QVERIFY( data[ 3 ].count == 2 );
        }

        void TableAlgorithmsTester::TestSplitIntoCrossesAlgorithm_3()
        {
            CCData ccd1( { 1, 6 }, 4 );
            CCData ccd2( { 2, 2 }, 6 );
            CCData ccd3( { 3, 1 }, 2 );
            CCData ccd4( { 3, 6 }, 4 );
            CCData ccd5( { 4, 3 }, 3 );
            CCData ccd6( { 5, 1 }, 3 );
            CCData ccd7( { 5, 5 }, 1 );

            std::vector< CCData > data = { ccd1, ccd2, ccd3, ccd4, ccd5, ccd6, ccd7 };
            Algorithms::TableAlgorithms::SplitTableIntoCrosses(
                        6, 5, data );

            QVERIFY( data[ 0 ].count == 4 );
            QVERIFY( data[ 1 ].count == 6 );
            QVERIFY( data[ 2 ].count == 2 );
            QVERIFY( data[ 2 ].bottomCells.size() == 2 );
            QVERIFY( data[ 3 ].count == 4 );
            QVERIFY( data[ 3 ].leftCells.size() == 2 );
            QVERIFY( data[ 3 ].upperCells.size() == 2 );
            QVERIFY( data[ 4 ].count == 3 );
            QVERIFY( data[ 4 ].rightCells.size() == 2 );
            QVERIFY( data[ 4 ].bottomCells.size() == 1 );
            QVERIFY( data[ 5 ].count == 3 );
            QVERIFY( data[ 5 ].rightCells.size() == 2 );
            QVERIFY( data[ 5 ].bottomCells.size() == 1 );
            QVERIFY( data[ 6 ].count == 1 );
            QVERIFY( data[ 6 ].leftCells.size() == 1 );
        }

        void TableAlgorithmsTester::TestSplitIntoCrossesAlgorithm_4()
        {
            CCData ccd0( { 1, 2 }, 5 );
            CCData ccd1( { 1, 6 }, 3 );
            CCData ccd2( { 2, 3 }, 5 );
            CCData ccd3( { 2, 9 }, 1 );
            CCData ccd4( { 3, 8 }, 8 );
            CCData ccd5( { 4, 1 }, 4 );
            CCData ccd6( { 4, 5 }, 2 );
            CCData ccd7( { 5, 3 }, 5 );
            CCData ccd8( { 5, 7 }, 2 );
            CCData ccd9( { 6, 1 }, 1 );
            CCData ccd10( { 6, 7 }, 3 );
            CCData ccd11( { 6, 9 }, 3 );

            std::vector< CCData > data = {
                ccd0, ccd1, ccd2, ccd3, ccd4, ccd5, ccd6, ccd7, ccd8, ccd9, ccd10, ccd11 };
            Algorithms::TableAlgorithms::SplitTableIntoCrosses(
                        9, 6, data );

            QVERIFY( data[ 0 ].count == 5 );
            QVERIFY( data[ 1 ].count == 3 );
            QVERIFY( data[ 2 ].count == 5 );
            QVERIFY( data[ 3 ].count == 1 );
            QVERIFY( data[ 4 ].count == 8 );
            QVERIFY( data[ 5 ].count == 4 );
            QVERIFY( data[ 6 ].count == 2 );
            QVERIFY( data[ 7 ].count == 5 );
            QVERIFY( data[ 8 ].count == 2 );
            QVERIFY( data[ 9 ].count == 1 );
            QVERIFY( data[ 10 ].count == 3 );
            QVERIFY( data[ 11 ].count == 3 );
        }

        void TableAlgorithmsTester::TestSplitIntoCrossesAlgorithm_5()
        {
            std::vector< CCData > data = {
                CCData( { 3, 1 }, 2 ),
                CCData( { 1, 2 }, 4 ),
                CCData( { 5, 2 }, 4 ),
                CCData( { 3, 3 }, 5 ),
                CCData( { 2, 5 }, 2 ),
                CCData( { 4, 5 }, 2 )
            };

            Algorithms::TableAlgorithms::SplitTableIntoCrosses(
                        5, 5, data );

            QVERIFY( data[ 0 ].count == 2 );
            QVERIFY( data[ 0 ].upperCells.size() == 1 );
            QVERIFY( data[ 0 ].bottomCells.size() == 1 );
            QVERIFY( data[ 1 ].count == 4 );
            QVERIFY( data[ 1 ].upperCells.size() == 1 );
            QVERIFY( data[ 1 ].rightCells.size() == 2 );
            QVERIFY( data[ 1 ].leftCells.size() == 1 );
            QVERIFY( data[ 2 ].count == 4 );
            QVERIFY( data[ 2 ].bottomCells.size() == 1 );
            QVERIFY( data[ 2 ].rightCells.size() == 2 );
            QVERIFY( data[ 2 ].leftCells.size() == 1 );
            QVERIFY( data[ 3 ].count == 5 );
            QVERIFY( data[ 3 ].bottomCells.size() == 1 );
            QVERIFY( data[ 3 ].rightCells.size() == 2 );
            QVERIFY( data[ 3 ].leftCells.size() == 1 );
            QVERIFY( data[ 3 ].upperCells.size() == 1 );
            QVERIFY( data[ 4 ].count == 2 );
            QVERIFY( data[ 4 ].leftCells.size() == 1 );
            QVERIFY( data[ 4 ].bottomCells.size() == 1 );
            QVERIFY( data[ 5 ].count == 2 );
            QVERIFY( data[ 5 ].leftCells.size() == 1 );
            QVERIFY( data[ 5 ].upperCells.size() == 1 );
        }


    }
}



QTEST_APPLESS_MAIN( Tests::AlgorithmsTests::TableAlgorithmsTester )

#include "tst_tablealgorithmstester.moc"
