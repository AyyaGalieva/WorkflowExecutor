#include "WorkflowExecutor.h"
#include "WFE.h"
using namespace WorkflowExecutor;

int main(int argc, char* argv[])
{
	if (argc == 1) {
		std::cerr << "Please add a workflow filename";
		return -1;
	}
	if (argc > 2) return -1;
	WFE x (argv[1]) ;
	x.doWork();
	return 0;
}