#include "WorkflowExecutor.h"
#include <algorithm>
using namespace WorkflowExecutor;

class ReplaceCommand : public Command {
public:
	ReplaceCommand() {
	}
	virtual void execute(std::string &context, std::vector<std::string>  &workspace) override {
		int space = context.find_first_of(" ", 0);
			if (space == context.npos)
					throw std::runtime_error("invalid Replace format");
				std::string word1 = context.substr(0, space);
				std::string word2 = context.substr(space+1, context.length() - space-1);
				int replacePosition;
				for (std::string& cur : workspace) {
					replacePosition = cur.find(word1);
					if (replacePosition != cur.npos)
						cur.replace(replacePosition,word1.length(), word2);
				}
	}

};

class ReplaceCommandCreator : public CommandCreator {
public:
	static ReplaceCommandCreator* getInstance() {
		static ReplaceCommandCreator c;
		return &c;
	}
	virtual Command *create() override {
		return new ReplaceCommand();
	}
private:
	ReplaceCommandCreator() = default;
};

namespace {
	bool a = CommandFactory::getInstance().registerCommand("replace", ReplaceCommandCreator::getInstance());
}