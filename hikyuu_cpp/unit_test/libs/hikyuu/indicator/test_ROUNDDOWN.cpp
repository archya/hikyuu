/*
 * test_ROUNDDOWN.cpp
 *
 *  Created on: 2019-4-14
 *      Author: fasiondog
 */

#ifdef TEST_ALL_IN_ONE
    #include <boost/test/unit_test.hpp>
#else
    #define BOOST_TEST_MODULE test_hikyuu_indicator_suite
    #include <boost/test/unit_test.hpp>
#endif

#include <fstream>
#include <hikyuu/StockManager.h>
#include <hikyuu/indicator/crt/ROUNDDOWN.h>
#include <hikyuu/indicator/crt/KDATA.h>
#include <hikyuu/indicator/crt/PRICELIST.h>

using namespace hku;

/**
 * @defgroup test_indicator_ROUNDDOWN test_indicator_ROUNDDOWN
 * @ingroup test_hikyuu_indicator_suite
 * @{
 */

/** @par 检测点 */
BOOST_AUTO_TEST_CASE( test_ROUNDDOWN ) {
    Indicator result;

    PriceList a;
    a.push_back(1.323);
    a.push_back(0.301);
    a.push_back(0.305);

    Indicator data = PRICELIST(a);

    result = ROUNDDOWN(data, 2);
    BOOST_CHECK(result.name() == "ROUNDDOWN");
    BOOST_CHECK(result.discard() == 0);
    BOOST_CHECK(result.size() == 3);
    BOOST_CHECK_CLOSE(result[0], 1.32, 0.001);
    BOOST_CHECK_CLOSE(result[1], 0.30, 0.001);
    BOOST_CHECK_CLOSE(result[2], 0.30, 0.001);

    result = ROUNDDOWN(-11.15, 1);
    BOOST_CHECK(result.size() == 1);
    BOOST_CHECK(result.discard() == 0);
    BOOST_CHECK_CLOSE(result[0], -11.1, 0.01);
}


//-----------------------------------------------------------------------------
// test export
//-----------------------------------------------------------------------------
#if HKU_SUPPORT_SERIALIZATION

/** @par 检测点 */
BOOST_AUTO_TEST_CASE( test_ROUNDDOWN_export ) {
    StockManager& sm = StockManager::instance();
    string filename(sm.tmpdir());
    filename += "/ROUNDDOWN.xml";

    Stock stock = sm.getStock("sh000001");
    KData kdata = stock.getKData(KQuery(-20));
    Indicator x1 = ROUNDDOWN(CLOSE(kdata));
    {
        std::ofstream ofs(filename);
        boost::archive::xml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP(x1);
    }

    Indicator x2;
    {
        std::ifstream ifs(filename);
        boost::archive::xml_iarchive ia(ifs);
        ia >> BOOST_SERIALIZATION_NVP(x2);
    }

    BOOST_CHECK(x2.name() == "ROUNDDOWN");
    BOOST_CHECK(x1.size() == x2.size());
    BOOST_CHECK(x1.discard() == x2.discard());
    BOOST_CHECK(x1.getResultNumber() == x2.getResultNumber());
    for (size_t i = 0; i < x1.size(); ++i) {
        BOOST_CHECK_CLOSE(x1[i], x2[i], 0.00001);
    }
}
#endif /* #if HKU_SUPPORT_SERIALIZATION */

/** @} */


