#include <QtTest>

// add necessary includes here

class DrinqTests : public QObject
{
    Q_OBJECT

public:
    DrinqTests();
    ~DrinqTests();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

DrinqTests::DrinqTests()
{

}

DrinqTests::~DrinqTests()
{

}

void DrinqTests::initTestCase()
{

}

void DrinqTests::cleanupTestCase()
{

}

void DrinqTests::test_case1()
{

}

//QTEST_APPLESS_MAIN(DrinqTests)

#include "tst_drinqtests.moc"
