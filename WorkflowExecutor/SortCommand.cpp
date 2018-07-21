#include "WorkflowExecutor.h"
#include <algorithm>
using namespace WorkflowExecutor;
class SortCommand : public Command {
public:
	SortCommand() = default;
	virtual void execute(std::string &context, std::vector<std::string>  &workspace) override {

		std::sort(workspace.begin(), workspace.end());
	}
};

class SortCommandCreator : public CommandCreator {
public:
	static SortCommandCreator* getInstance() {
		static SortCommandCreator c;
		return &c;
	}
	virtual Command *create() override {
		return new SortCommand();
	}
private:
	SortCommandCreator() = default;
};

namespace {
	bool a = CommandFactory::getInstance().registerCommand("sort", SortCommandCreator::getInstance());
}