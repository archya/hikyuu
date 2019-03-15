/*
 * test_Parameter.cpp
 *
 *  Created on: 2013-2-28
 *      Author: fasiondog
 */


#ifdef TEST_ALL_IN_ONE
    #include <boost/test/unit_test.hpp>
#else
    #define BOOST_TEST_MODULE test_hikyuu_utilities
    #include <boost/test/unit_test.hpp>
#endif

#include <hikyuu/Log.h>
#include <hikyuu/utilities/Parameter.h>
#include <hikyuu/StockManager.h>

#if HKU_SUPPORT_SERIALIZATION
#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#endif

using namespace hku;

/**
 * @defgroup test_hikyuu_Parameter test_hikyuu_Parameter
 * @ingroup test_hikyuu_utilities
 * @{
 */

/** @par 检测点 */
BOOST_AUTO_TEST_CASE( test_Parameter ) {
    Parameter param;

    /** @arg 正常添加、读取、修改参数 */
    param.set<int>("n", 1);
    param.set<bool>("bool", true);
    param.set<double>("double", 10);
    param.set<string>("string", "test");
    BOOST_CHECK(param.get<int>("n") == 1);
    BOOST_CHECK(param.get<bool>("bool") == true);
    BOOST_CHECK(param.get<double>("double") == 10.0);
    BOOST_CHECK(param.get<string>("string") == "test");
    param.set<int>("n", 10);
    param.set<bool>("bool", false);
    param.set<double>("double", 10.01);
    param.set<string>("string", "test2");
    BOOST_CHECK(param.get<int>("n") == 10);
    BOOST_CHECK(param.get<bool>("bool") == false);
    BOOST_CHECK(param.get<double>("double") == 10.01);
    BOOST_CHECK(param.get<string>("string") == "test2");

    /** @arg 添加不支持的参数类型 */
    BOOST_CHECK_THROW(param.set<size_t>("n", 10), std::logic_error);
    BOOST_CHECK_THROW(param.set<float>("n", 10.0), std::logic_error);

    /** @arg 修改参数时，指定的类型和原有类型不符 */
    BOOST_CHECK_THROW(param.set<float>("n", 10.0), std::logic_error);
    BOOST_CHECK_THROW(param.set<float>("bool", 10.0), std::logic_error);
    BOOST_CHECK_THROW(param.set<float>("double", 10.0), std::logic_error);

    /** @arg 测试相等比较 */
    Parameter p1, p2;
    p1.set<string>("string", "test");
    p1.set<bool>("bool", true);
    p1.set<double>("double", 0.01);
    p1.set<string>("test", "test2");

    p2.set<double>("double", 0.01);
    p2.set<string>("test", "test2");
    p2.set<string>("string", "test");
    p2.set<bool>("bool", true);

    BOOST_CHECK(p1==p2);

    /** @arg 测试使用 Stock 做为参数 */
    Stock stk = getStock("sh600000");
    Parameter p;
    p.set<Stock>("stk", stk);
    Stock stk2 = p.get<Stock>("stk");
    BOOST_CHECK(stk == stk2);

    /** @arg 测试使用 KQuery 做为参数 */
    KQuery query(10, 20);
    p = Parameter();
    p.set<KQuery>("query", query);
    KQuery q2;
    q2 = p.get<KQuery>("query");
    BOOST_CHECK(query == q2);

    /** @arg 测试使用 KData 做为参数 */
    KData k = stk.getKData(query);
    p = Parameter();
    p.set<KData>("k", k);
    KData k2 = p.get<KData>("k");
    BOOST_CHECK(k.size() == k2.size());
    BOOST_CHECK(k.getStock() == k2.getStock());
    BOOST_CHECK(k.getQuery() == k2.getQuery());

    k = KData();
    p = Parameter();
    p.set<KData>("k", k);
    k2 = p.get<KData>("k");
    BOOST_CHECK(k.size() == k2.size());
    BOOST_CHECK(k.getStock() == k2.getStock());
    BOOST_CHECK(k.getQuery() == k2.getQuery());
}


#if HKU_SUPPORT_SERIALIZATION
/** @par 检测点 */
BOOST_AUTO_TEST_CASE( test_Parameter_serialize ) {
    string filename(StockManager::instance().tmpdir());
    filename += "/Parameter.xml";

    Parameter p1;
    p1.set<int>("n", 10);
    p1.set<bool>("bool", true);
    p1.set<double>("p", 0.101);
    p1.set<string>("string", "This is string!");
    Stock stk = getStock("sh600000");
    KQuery q = KQueryByDate(Datetime(200001041025), Datetime(200001041100), KQuery::MIN5);
    KData k = stk.getKData(q);
    p1.set<Stock>("stk", stk);
    p1.set<KQuery>("query", q);
    p1.set<KData>("kdata", k);
    {
        std::ofstream ofs(filename);
        boost::archive::xml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP(p1);
    }

    Parameter p2;
    {
        std::ifstream ifs(filename);
        boost::archive::xml_iarchive ia(ifs);
        ia >> BOOST_SERIALIZATION_NVP(p2);
    }

    BOOST_CHECK(p2.get<int>("n") == 10);
    BOOST_CHECK(p2.get<bool>("bool") == true);
    BOOST_CHECK(p2.get<double>("p") == 0.101);
    BOOST_CHECK(p2.get<string>("string") == "This is string!");
    BOOST_CHECK(p2.get<Stock>("stk") == stk);
    BOOST_CHECK(p2.get<KQuery>("query") == q);
    KData k2 = p2.get<KData>("kdata");
    BOOST_CHECK(k.size() == k2.size());
    BOOST_CHECK(k.getStock() == k2.getStock());
    BOOST_CHECK(k.getQuery() == k2.getQuery());
}
#endif /* HKU_SUPPORT_SERIALIZATION */

/** @} */
