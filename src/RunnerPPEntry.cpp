/**
 * This file contains the bada application entry point.
 */
#include "RunnerPP.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

_EXPORT_ int OspMain(int argc, char *pArgv[]);

/**
 * The entry function of bada application called by the operating system.
 */
int
OspMain(int argc, char *pArgv[])
{
	result r = E_SUCCESS;

	AppLog("Application started.");
	ArrayList* pArgs = new ArrayList();
	pArgs->Construct();
	for (int i = 0; i < argc; i++)
		pArgs->Add(*(new String(pArgv[i])));

	r = Tizen::App::Application::Execute(RunnerPP::CreateInstance, pArgs);
	if (IsFailed(r))
	{
		AppLogException("Application execution failed-[%s].", GetErrorMessage(r));
		r &= 0x0000FFFF;
	}

	pArgs->RemoveAll(true);
	delete pArgs;
	AppLog("Application finished.");

	return static_cast<int>(r);
}
#ifdef __cplusplus
}
#endif // __cplusplus
