#include <gtest/gtest.h>
#include <math.h>

#include "test.hpp"


TEST(Simple_test, plus){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("2+2").Calculate();

    ASSERT_EQ(ans.result, 4);
}

TEST(Simple_test, minus){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("2-2").Calculate();

    ASSERT_EQ(ans.result, 0);
}

TEST(Simple_test, mult){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("2*2").Calculate();

    ASSERT_EQ(ans.result, 4);
}
TEST(Simple_test, pow){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("2^3").Calculate();

    ASSERT_EQ(ans.result, 8);
}
TEST(Simple_test, mod){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("4mod3").Calculate();

    ASSERT_EQ(ans.result, 1);
}
TEST(Simple_test, unar_minus){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("2+-3").Calculate();

    ASSERT_EQ(ans.result, -1);
}
TEST(Simple_test, unar_plus){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("2-+3").Calculate();

    ASSERT_EQ(ans.result, -1);
}

TEST(Complex, plus_mult){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("2+2*2").Calculate();

    ASSERT_EQ(ans.result, 6);
}
TEST(Complex, plus_div){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("2+2/2").Calculate();

    ASSERT_EQ(ans.result, 3);
}
TEST(Complex, plus_mult_div){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("6/2+2*2").Calculate();

    ASSERT_EQ(ans.result, 7);
}
TEST(Functions, cos){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("cos(3)").Calculate();

    ASSERT_EQ(ans.result, cos(3));
   
}
TEST(Functions, sin){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("sin(3)").Calculate();

    ASSERT_EQ(ans.result, sin(3));
   
}
TEST(Functions, tan){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("tan(3)").Calculate();

    ASSERT_EQ(ans.result, tan(3));
   
}
TEST(Functions, asin){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("asin(0.3)").Calculate();

    ASSERT_EQ(ans.result, asin(0.3));
   
}

TEST(Functions, acos){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("acos(0.3)").Calculate();

    ASSERT_EQ(ans.result, acos(0.3));
   
}


TEST(Functions, tanx){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("tan(x)").Calculate(3);

    ASSERT_EQ(ans.result, tan(3));
   
}
TEST(Functions, sinx){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("sin(x)").Calculate(3);

    ASSERT_EQ(ans.result, sin(3));  
}
TEST(Functions, tanx_plot){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("tan(x)").PlotEnable().Calculate(3);
    
    double step = double(ans.x_max-ans.x_min)/ans.dot_count;
    for(int i =0;i<ans.x.size();i++){
        ASSERT_EQ(ans.x[i], ans.x_min+step*i);
        ASSERT_EQ(ans.y[i], tan(ans.x_min+step*i));
    }
   
}
TEST(Functions, sinx_plot){
    Evaluator eval;
    Stage ans = eval.ToReversePolish("sin(x)").PlotEnable().Calculate(3);
    double step = double(ans.x_max-ans.x_min)/ans.dot_count;
    for(int i =0;i<ans.x.size();i++){
        ASSERT_EQ(ans.x[i], ans.x_min+step*i);
        ASSERT_EQ(ans.y[i], sin(ans.x_min+step*i));
    }  
}



