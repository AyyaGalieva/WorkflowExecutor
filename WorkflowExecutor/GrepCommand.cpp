#include "WorkflowExecutor.h"
#include <algorithm>
using namespace WorkflowExecutor;

class GrepCommand : public Command {
public:
	GrepCommand() {
	}
	virtual void execute(std::string &context, std::vector<std::string>  &workspace) override {
		for (auto it= workspace.begin(); it!=workspace.end();)  {
			if (it->find(context) == it->npos) {
				 it= workspace.erase(it);
			}
			else
				it++;
		}
	}
};

class GrepCommandCreator : public CommandCreator {
public:
	static GrepCommandCreator* getInstance() {
		static GrepCommandCreator c;
		return &c;
	}
	virtual Command *create() override {
		return new GrepCommand();
	}
private:
	GrepCommandCreator() = default;
};

namespace {
	bool a = CommandFactory::getInstance().registerCommand("grep", GrepCommandCreator::getInstance());
}