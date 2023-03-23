#include "Ball.h"
#include "Tests/AutomationCommon.h"


/*              Black Box Testing (1)
*   Testing the ball bouncing from straight collision onto a flat surface
*/
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestClass1, "Test Ball Bouncing Back From Straight Collision",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool TestClass1::RunTest(FString const& Parameters) {
    ABall* testBall = NewObject<ABall>();

    //init a straight ball and non-moving paddle vector 
    FVector example_ball_velocity = FVector(1000.0f, 0.0f, 0.0f);
    FVector paddle_vector = FVector(0.0f,0.0f,0.0f);
    //bounces off flat surface
    FVector reflect = UKismetMathLibrary::GetReflectionVector(example_ball_velocity, FVector(-1000.0f,0.0f,0.0f));

    //Function arguments:
    //(FVector curr_reflect, FVector paddle_vector, bool enableRandom)
    FVector result = testBall->onPaddleHit(reflect, paddle_vector, false,false);

    //test if the ball does bounce as expected
    TestTrue("Ball Bounces Back Successfully", result == FVector(-1000.0f, 0.0f, 0.0f));

    //collecting garbage
    testBall->MarkAsGarbage();
    return true;
}


/*          Black Box Testing (2)
*   Testing at a 45 deg angle, it should calculate the bounce at a 90 deg angle on a flat surface
*/
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestClass2, "Test Ball Bouncing @ 45 Deg Angle",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

    bool TestClass2::RunTest(FString const& Parameters) {
    ABall* testBall = NewObject<ABall>();

    //setting example to 45 Deg angle velocity and non-moving paddle
    FVector example_ball_velocity = FVector(1000.0f, 1000.0f, 0.0f);
    FVector paddle_vector = FVector(0.0f, 0.0f, 0.0f);

    //calculate the expected result from 45 deg angle on a flat surface
    FVector reflect = UKismetMathLibrary::GetReflectionVector(example_ball_velocity, FVector(-1000.0f, 0.0f, 0.0f));

    //Function arguments:
    //(FVector curr_reflect, FVector paddle_vector, bool enableRandom)
    FVector result = testBall->onPaddleHit(reflect, paddle_vector, false,false);

    TestTrue("Ball Bounces Back Successfully (45 deg)", result == FVector(-1000.0f, 1000.0f, 0.0f));

    //collecting garbage
    testBall->MarkAsGarbage();
    return true;
}

/*          White Box Testing (3)
*   This tests the reflection while the paddle is moving
*   It's white box testing because I need to look into the code to see how strong the new angle is
*/
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestClass3, "Test Straight Ball Bouncing From Up Moving Paddle ",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

    bool TestClass3::RunTest(FString const& Parameters) {
    ABall* testBall = NewObject<ABall>();

    //setting example to 45 Deg angle velocity
    FVector example_ball_velocity = FVector(1000.0f, 0.0f, 0.0f);

    FVector paddle_vector = FVector(0.0f, 1.0f, 0.0f); //padding moving up 

    //calculate the expected result 
    FVector reflect = UKismetMathLibrary::GetReflectionVector(example_ball_velocity, FVector(-1000.0f, 0.0f, 0.0f));

    //Function arguments:
    //(FVector curr_reflect, FVector paddle_vector, bool enableRandom)
    FVector result = testBall->onPaddleHit(reflect, paddle_vector, false,false);

    // the "2000.0f" value is from (1 * 2000.0f) from the function
    //test to see if the ball bounces back but at an angle going up
    TestTrue("Ball Bounces Correctly with Up Moving Paddle", result == FVector(-1000.0f, 2000.0f, 0.0f));

    //collecting garbage
    testBall->MarkAsGarbage();
    return true;
}

/*      White Box Testing (4)
*   Testing while paddle is going down
* 
*/
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestClass4, "Test Straight Ball Bouncing From Down Moving Paddle",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

    bool TestClass4::RunTest(FString const& Parameters) {
    ABall* testBall = NewObject<ABall>();

    //setting example to 45 Deg angle velocity
    FVector example_ball_velocity = FVector(1000.0f, 0.0f, 0.0f);

    FVector paddle_vector = FVector(0.0f, -1.0f, 0.0f); //padding moving down

    //calculate the expected result 
    FVector reflect = UKismetMathLibrary::GetReflectionVector(example_ball_velocity, FVector(-1000.0f, 0.0f, 0.0f));

    //Function arguments:
    //(FVector curr_reflect, FVector paddle_vector, bool enableRandom)
    FVector result = testBall->onPaddleHit(reflect, paddle_vector, false,false);

    TestTrue("Ball Bounces Correctly with Down Moving Paddle", result == FVector(-1000.0f, -2000.0f, 0.0f));

    //collecting garbage
    testBall->MarkAsGarbage();
    return true;
}

/*          Black Box Testing (5)
*   The Straight Test but with random calculation
*   The expected result should be no change since the random calculation should only occur if the paddle is moving
*/
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestClass5, "Test Straight Ball with random calc & paddle not moving",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

    bool TestClass5::RunTest(FString const& Parameters) {
    ABall* testBall = NewObject<ABall>();

    //setting example to 45 Deg angle velocity
    FVector example_ball_velocity = FVector(1000.0f, 0.0f, 0.0f);

    FVector paddle_vector = FVector(0.0f, 0.0f, 0.0f); //padding stationary

    //calculate the expected result 
    FVector reflect = UKismetMathLibrary::GetReflectionVector(example_ball_velocity, FVector(-1000.0f, 0.0f, 0.0f));

    //Function arguments:
    //(FVector curr_reflect, FVector paddle_vector, bool enableRandom)
    FVector result = testBall->onPaddleHit(reflect, paddle_vector, true,false);

    TestTrue("Ball Bounces Off Correctly with Random Enabled (no paddle movement)", result == FVector(-1000.0f, 0.0f, 0.0f));

    //collecting garbage
    testBall->MarkAsGarbage();
    return true;
}
/*          White Box Testing (6)
*   Testing calculation with moving paddle with ball at 45 deg angle
*   The expected result should be no change since the random calculation should only occur if the paddle is moving
*/
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestClass6, "Test 45 deg ball while paddle going up",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

    bool TestClass6::RunTest(FString const& Parameters) {
    ABall* testBall = NewObject<ABall>();

    //setting example to 45 Deg angle velocity
    FVector example_ball_velocity = FVector(1000.0f, 1000.0f, 0.0f);

    FVector paddle_vector = FVector(0.0f, 1.0f, 0.0f); //padding is moving up

    //calculate the expected result 
    FVector reflect = UKismetMathLibrary::GetReflectionVector(example_ball_velocity, FVector(-1000.0f, 0.0f, 0.0f));

    //Function arguments:
    //(FVector curr_reflect, FVector paddle_vector, bool enableRandom)
    FVector result = testBall->onPaddleHit(reflect, paddle_vector, false,false);

    // the "2000.0f" value is from (1 * 2000.0f) from the function
    TestTrue("Ball Bounces Off Correctly @ 45 Deg Angle and paddle moving", result == FVector(-1000.0f, 3000.0f, 0.0f));

    //collecting garbage
    testBall->MarkAsGarbage();
    return true;
}

/*          White Box Testing (7)
*   Testing calculation with moving paddle with ball at 45 deg angle
*   The expected result should be no change since the random calculation should only occur if the paddle is moving
*/
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestClass7, "Test 45 deg ball while paddle going down",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

    bool TestClass7::RunTest(FString const& Parameters) {
    ABall* testBall = NewObject<ABall>();

    //setting example to 45 Deg angle velocity
    FVector example_ball_velocity = FVector(1000.0f, 1000.0f, 0.0f);

    FVector paddle_vector = FVector(0.0f, -1.0f, 0.0f); //padding is moving down

    //calculate the expected result 
    FVector reflect = UKismetMathLibrary::GetReflectionVector(example_ball_velocity, FVector(-1000.0f, 0.0f, 0.0f));

    FVector result = testBall->onPaddleHit(reflect, paddle_vector, false,false);

    TestTrue("Ball Bounces Off Correctly @ 45 Deg Angle and paddle moving", result == FVector(-1000.0f, -1000.0f, 0.0f));

    //collecting garbage
    testBall->MarkAsGarbage();
    return true;
}
/*      Black Box Testing (8)
*  Testing the stationary of the ball 
*  I should expect no difference since the ball is not moving at all
*/
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestClass8, "Test Ball is Stationary",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

    bool TestClass8::RunTest(FString const& Parameters) {
    ABall* testBall = NewObject<ABall>();

    //setting example to be stationary
    FVector example_ball_velocity = FVector(0.0f, 0.0f, 0.0f);

    FVector paddle_vector = FVector(0.0f, 0.0f, 0.0f); //padding is stationary

    //calculate the expected result 
    FVector reflect = UKismetMathLibrary::GetReflectionVector(example_ball_velocity, FVector(-1000.0f, 0.0f, 0.0f));

    FVector result = testBall->onPaddleHit(reflect, paddle_vector, false,false);

    TestTrue("Ball Doesn't Bounce when Stationary, which is expected", result == FVector(0.0f, 0.0f, 0.0f));

    //collecting garbage
    testBall->MarkAsGarbage();
    return true;
}
/*      White Box Testing (9)
*  Test increasing speed after collision straight
*/

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestClass9, "Test straight ball increases speed ",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

    bool TestClass9::RunTest(FString const& Parameters) {
    ABall* testBall = NewObject<ABall>();

    //setting example to straight
    FVector example_ball_velocity = FVector(2000.0f, 0.0f, 0.0f);

    FVector paddle_vector = FVector(0.0f, 0.0f, 0.0f); 

    //calculate the expected result 
    FVector reflect = UKismetMathLibrary::GetReflectionVector(example_ball_velocity, FVector(-2000.0f, 0.0f, 0.0f));

    //last argument sets the increment to be true
    FVector result = testBall->onPaddleHit(reflect, paddle_vector, false, true);

    TestTrue("Ball Bounces back with greater velocity, which is expected", result == FVector(-2400.0f, 0.0f, 0.0f));

    //collecting garbage
    testBall->MarkAsGarbage();
    return true;
}

/*      White Box Testing (10)
*  Test increasing speed after collision while ball is at 45 deg angle
*/

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestClass10, "Test straight ball increases speed at 45 deg angle",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

    bool TestClass10::RunTest(FString const& Parameters) {
    ABall* testBall = NewObject<ABall>();

    //setting example to straight
    FVector example_ball_velocity = FVector(1000.0f, 1000.0f, 0.0f);

    FVector paddle_vector = FVector(0.0f, 0.0f, 0.0f); 

    //calculate the expected result 
    FVector reflect = UKismetMathLibrary::GetReflectionVector(example_ball_velocity, FVector(-1000.0f, -1000.0f, 0.0f));

    //last argument sets the increment to be true
    FVector result = testBall->onPaddleHit(reflect, paddle_vector, false, true);

    TestTrue("Ball Bounces at an angle with greater velocity", result == FVector(-1200.0f, -1200.0f, 0.0f));

    //collecting garbage
    testBall->MarkAsGarbage();
    return true;
}