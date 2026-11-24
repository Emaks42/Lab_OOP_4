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