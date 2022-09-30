#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS
#include "CoreMinimal.h"

// HorizonUI.SuccessTest
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHorizinUITest, "Plugin.UnitTests.HorizonUI", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FHorizinUITest::RunTest(const FString& Parameters)
{

	bool bResult = true;

    

	if (ExecutionInfo.GetErrorTotal() > 0)
	{
		bResult = false;
	}

	return bResult;
}



#endif //WITH_DEV_AUTOMATION_TESTS