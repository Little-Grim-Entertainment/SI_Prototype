#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS
#include "CoreMinimal.h"

// HorizonUI.SuccessTest
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHorizonUISuccessTest, "Plugin.SmokeTest.HorizonUI.Success", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FHorizonUISuccessTest::RunTest(const FString& Parameters)
{

	bool bResult = true;

	if (ExecutionInfo.GetErrorTotal() > 0)
	{
		bResult = false;
	}

	return bResult;
}



// IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFailTest, "Project.Unit Tests.SmokeTest.Failed", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

// bool FFailTest::RunTest(const FString& Parameters)
// {

// 	return false;
// }



#endif //WITH_DEV_AUTOMATION_TESTS