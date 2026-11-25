#include <gtest/gtest.h>
#include "../include/shape2D_collection.h"
#include "../include/shapes.h"
#include <fstream>

TEST(Shapes2DCreationTests, Shapes2DCreationTestBase)
{
    Circle c(2);
    Ellipse e(2, 5);
    Sector s(3, M_PI);
    EXPECT_NEAR(4 * M_PI, c.metric(), 1e-5);
    EXPECT_NEAR(10 * M_PI, e.metric(), 1e-5);
    EXPECT_NEAR(4.5 * M_PI, s.metric(), 1e-5);
}

TEST(Shapes2DCreationTests, Shapes2DCreationTestDefault)
{
    Circle c;
    Ellipse e;
    Sector s;
    EXPECT_NEAR(0, c.metric(), 1e-5);
    EXPECT_NEAR(0, e.metric(), 1e-5);
    EXPECT_NEAR(0, s.metric(), 1e-5);
}

TEST(Shapes2DCreationTests, Shapes2DCreationTestIncorrectParam)
{
    EXPECT_THROW(Circle(-4), std::invalid_argument);
    EXPECT_THROW(Ellipse(-4, 2), std::invalid_argument);
    EXPECT_THROW(Ellipse(4, -2), std::invalid_argument);
    EXPECT_THROW(Sector(4, 20), std::invalid_argument);
    EXPECT_THROW(Sector(-4, 2), std::invalid_argument);
    EXPECT_THROW(Sector(4, -2), std::invalid_argument);
}

TEST(Shapes2DSpecMethodsTests, Shapes2DSpecMethodsTestCircle)
{
    Circle c(2);
    EXPECT_NEAR(2, c.radius(), 1e-5);
}

TEST(Shapes2DSpecMethodsTests, Shapes2DSpecMethodsTestEllipse)
{
    Ellipse e1(2,5);
    ASSERT_TRUE(!e1.isCircle(1e-6));
    Ellipse e2(2,2);
    ASSERT_TRUE(e2.isCircle(1e-6));
}

TEST(Shapes2DSpecMethodsTests, Shapes2DSpecMethodsTestSector)
{
    Sector s1(2,M_1_PI);
    ASSERT_TRUE(!s1.isSemicircle(1e-6));
    Sector s2(2,M_PI);
    ASSERT_TRUE(s2.isSemicircle(1e-6));
}

TEST(Shapes2DDynamicCastTests, Shapes2DDynamicCastTestCorrectType)
{
    Sector s(2,M_PI);
    Shape2D* s_= s.copy();
    ASSERT_TRUE(dynamic_cast<Sector*>(s_) != nullptr);
    delete s_;
}

TEST(Shapes2DDynamicCastTests, Shapes2DDynamicCastTestIncorrectType)
{
    Sector s(2,M_PI);
    Shape2D* s_ = s.copy();
    ASSERT_TRUE(dynamic_cast<Circle*>(s_) == nullptr);
    delete s_;
}

TEST(Shapes2DCollectionCreationTests, Shapes2DCollectionCreationTestBase)
{
    Shape2DCollection sc;
    Ellipse el(1,2);
    sc.add(el);
    ASSERT_TRUE(sc.size() == 1);
    ASSERT_TRUE(sc.remove(el));
}

TEST(Shapes2DCollectionCreationTests, Shapes2DCollectionCreationTestCopy)
{
    Shape2DCollection sc1;
    Ellipse el(1,2);
    sc1.add(el);
    Shape2DCollection sc2 = sc1;
    ASSERT_TRUE(sc2.remove(el));
    ASSERT_TRUE(sc1.remove(el));
}

TEST(Shapes2DCollectionCreationTests, Shapes2DCollectionCreationTestMove)
{
    Shape2DCollection sc1;
    Ellipse el(1,2);
    sc1.add(el);
    Shape2DCollection sc2 = std::move(sc1);
    ASSERT_TRUE(sc2.remove(el));
    ASSERT_TRUE(!sc1.remove(el));
    ASSERT_TRUE(sc1.size() == 0);
}

TEST(Shapes2DCollectionMetricTests, Shapes2DCollectionMetricTestBase)
{
    Shape2DCollection sc;
    Circle c(2);
    Ellipse e(2, 5);
    Sector s(3, M_PI);
    sc.add(c); sc.add(e); sc.add(s);
    EXPECT_NEAR(18.5 * M_PI, sc.metric(), 1e-5);
}

TEST(Shape2DReadWriteTests, Shape2DReadWriteTestCircle)
{
    Circle c_;
    std::ofstream f1("1.txt", std::ios::trunc);
    f1 << "2";
    f1.close();
    std::ifstream f2("1.txt");
    f2 >> c_;
    f2.close();
    EXPECT_NEAR(c_.metric(), 4 * M_PI, 1e-5);
    std::ofstream f3("1.txt", std::ios::trunc);
    f3 << c_;
    f3.close();
    std::ifstream f4("1.txt");
    std::string res;
    char c;
    while (f4.get(c))
    {
        res += c;
    }
    f4.close();
    ASSERT_TRUE(res == "Circle: r=2");
}

TEST(Shape2DReadWriteTests, Shape2DReadWriteTestEllipse)
{
    Ellipse e_;
    std::ofstream f1("1.txt", std::ios::trunc);
    f1 << "2 5";
    f1.close();
    std::ifstream f2("1.txt");
    f2 >> e_;
    f2.close();
    EXPECT_NEAR(e_.metric(), 10 * M_PI, 1e-5);
    std::ofstream f3("1.txt", std::ios::trunc);
    f3 << e_;
    f3.close();
    std::ifstream f4("1.txt");
    std::string res;
    char c;
    while (f4.get(c))
    {
        res += c;
    }
    f4.close();
    ASSERT_TRUE(res == "Ellipse: a=2 b=5");
}

TEST(Shape2DReadWriteTests, Shape2DReadWriteTestSector)
{
    Sector s_;
    std::ofstream f1("1.txt", std::ios::trunc);
    f1 << "2 2";
    f1.close();
    std::ifstream f2("1.txt");
    f2 >> s_;
    f2.close();
    EXPECT_NEAR(s_.metric(), 4, 1e-5);
    std::ofstream f3("1.txt", std::ios::trunc);
    f3 << s_;
    f3.close();
    std::ifstream f4("1.txt");
    std::string res;
    char c;
    while (f4.get(c))
    {
        res += c;
    }
    f4.close();
    ASSERT_TRUE(res == "Sector: r=2 angle=2");
}

TEST(Shape2DMetricTests, Shape2DMetricTestEquality)
{
    Circle c(2);
    Ellipse e(1,4);
    Sector s(0,0);
    ASSERT_TRUE(e == c);
    ASSERT_TRUE(e != s);
}

TEST(Shape2DMetricTests, Shape2DMetricTestToDouble)
{
    Circle c(2);
    Ellipse e(2, 5);
    Sector s(3, M_PI);
    EXPECT_NEAR((double)c, c.metric(), 1e-5);
    EXPECT_NEAR((double)e, e.metric(), 1e-5);
    EXPECT_NEAR((double)s, s.metric(), 1e-5);
}