#include "WorkflowExecutor.h"

using namespace WorkflowExecutor;

class ReadFileCommand : public Command {
public:
	ReadFileCommand()  {
	}
	virtual void execute(std::string &context, std::vector<std::string>  &workspace) override {
		std::ifstream fin(context);
		if (!fin.is_open())
			throw std::runtime_error(" cannot find read file!");
		std::string cur;
		while (std::getline(fin, cur)) {
			workspace.push_back(cur);
		}
		fin.close();
	}
};

class ReadFileCommandCreator : public CommandCreator {
public:
	static ReadFileCommandCreator* getInstance() {
		static ReadFileCommandCreator c;
		return &c;
	}
	virtual Command *create() override {
		return new ReadFileCommand();
	}
private:
	ReadFileCommandCreator() = default;
};

namespace {
	bool a = CommandFactory::getInstance().registerCommand("readfile", ReadFileCommandCreator::getInstance());
}