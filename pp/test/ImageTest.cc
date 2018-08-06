#include "gtest/gtest.h"
#include "pp/Image.h"

using pp::Image;

TEST(ImageTest, Basics) {
    Image img(1, 1);

    EXPECT_EQ(pp::Color{0.f}, img(0, 0));
    EXPECT_THROW(img(1, 0), std::out_of_range);
    EXPECT_THROW(img(0, 1), std::out_of_range);
}

TEST(ImageTest, GetChannels) {
    Image img(1, 1);
    img(0, 0) = pp::Color{-1.f, 0.f, 0.9999f};

    EXPECT_EQ(0, img.GetR(0, 0));
    EXPECT_EQ(128, img.GetG(0, 0));
    EXPECT_EQ(255, img.GetB(0, 0));
}


TEST(ImageTest, GetRow) {
    Image img(2, 2);

    img(0, 1) = pp::Color{0.1f};
    img(1, 1) = pp::Color{0.2f};

    auto row0 = img.GetRow(0);
    auto row1 = img.GetRow(1);
    EXPECT_THROW(img.GetRow(2), std::out_of_range);

    EXPECT_EQ(pp::Color{0.f}, row0[0]);
    EXPECT_EQ(pp::Color{0.f}, row0[1]);
    EXPECT_EQ(pp::Color{0.1f}, row1[0]);
    EXPECT_EQ(pp::Color{0.2f}, row1[1]);
}

TEST(ImageTest, ToRGBA) {
    Image img(1, 1);
    img(0, 0) = pp::Color{-1.f, 0.f, 0.9999f};

    auto rgba = img.ToRGBA();
    EXPECT_EQ(0,   rgba[0]);
    EXPECT_EQ(128, rgba[1]);
    EXPECT_EQ(255, rgba[2]);
    EXPECT_EQ(255, rgba[3]);
}