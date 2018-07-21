#include "WorkflowExecutor.h"

using namespace WorkflowExecutor;

class WriteFileCommand : public Command {
public:
	WriteFileCommand() {
	}
	virtual void execute(std::string &context, std::vector<std::string>  &workspace) override {
		std::ofstream fout(context);
		//todo proverka na fout
		for (std::string& cur : workspace)
			fout << cur<<std::endl;
		fout.close();
	}
};

class WriteFileCommandCreator : public CommandCreator {
public:
	static WriteFileCommandCreator* getInstance() {
		static WriteFileCommandCreator c;
		return &c;
	}
	virtual Command *create() override {
		return new WriteFileCommand();
	}
private:
	WriteFileCommandCreator() = default;
};

namespace {
	bool a = CommandFactory::getInstance().registerCommand("writefile", WriteFileCommandCreator::getInstance());
}