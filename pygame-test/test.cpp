#include "pch.h"
#include "../DataTypes.h"

TEST(Colors, CanBeNormalized) {
  Color start{255, 0, 128, ALPHA_OPAQUE};
  const auto [r, g, b, a] = start.normalize();
  EXPECT_FLOAT_EQ(r, 1.0f);
  EXPECT_FLOAT_EQ(g, 0.0f);
  EXPECT_NEAR(b, 0.5f, 0.002);
  EXPECT_FLOAT_EQ(a, 1.0);  
}

TEST(Colors, CanCorrectGamma) {
  Color start{255, 0, 128, ALPHA_OPAQUE};
  const auto result = start.correct_gamma(0.5f);
  //TODO: I don't know what a correct result should be. Read up on gamma I guess. 

}