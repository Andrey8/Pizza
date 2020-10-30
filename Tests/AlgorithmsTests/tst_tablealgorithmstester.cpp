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
            std::vector< CCData > data;
            Algorithms::TableAlgorithms::SplitTableIntoCrosses(
                        5, 3, data );
        }
    }
}



QTEST_APPLESS_MAIN( Tests::AlgorithmsTests::TableAlgorithmsTester )

#include "tst_tablealgorithmstester.moc"
