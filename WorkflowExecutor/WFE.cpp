#include "WFE.h"

using namespace WorkflowExecutor;

WFE::WFE(const std::string& descFileName) {
	std::ifstream descFile(descFileName);

	if (!descFile.is_open()) {
		throw std::runtime_error("desc file doesnot exist in this directory");
	}
	std::string cur;
	std::string arguments;
	descFile >> cur;
	if (cur!= "desc")
		throw std::runtime_error("not WFE file!!!");
	int blockNumber;
	descFile >> cur;

	while (cur != "csed") {
		blockNumber = std::stoi(cur);
		descFile >> cur;
		if (cur!= "=")
			throw std::runtime_error("invlaid desc format");
		descFile >> cur;
		std::getline(descFile, arguments);
		arguments = arguments.substr(1, arguments.length()-1);
		blocks[blockNumber] = std::move(std::pair<Command*, std::string>(CommandFactory::getInstance().getCommand(cur), arguments));
		descFile >> cur;
	}
	std::getline(descFile,cur);
	while (descFile >> cur) {
		blockNumber = std::stoi(cur);
		commandOrder.push_back(blockNumber);
		descFile >> arguments;
		if (arguments!= "->")
			throw std::runtime_error("invalid desc format");
	}
	descFile.close();
}

void WFE::doWork() {
	std::vector<std::string>  workspace;
	for (auto idCommand : commandOrder) {
		std::get<0>(blocks[idCommand])->execute(std::get<1>(blocks[idCommand]), workspace);
	}
}

WFE::~WFE() {
	for (auto& x : blocks) {
		delete x.second.first;
	}
}