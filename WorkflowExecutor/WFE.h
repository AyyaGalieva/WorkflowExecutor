#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include "WorkflowExecutor.h"
using namespace WorkflowExecutor;
class WFE : public iWFE {
public:
	~WFE();
	WFE(const WFE& a) = delete;
	void doWork() override;
	explicit WFE(const std::string& descFile);
private:
	std::map<int, std::pair<Command*, std::string>> blocks;
	std::vector<int> commandOrder;
	std::vector<std::string> data;
};