#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

namespace WorkflowExecutor
{
	class Command  {
	public:
		virtual void execute(std::string &context, std::vector<std::string>  &workspace) = 0;
	};

	class CommandCreator {
	public:
		virtual Command* create() = 0;
	};

	class CommandFactory {
	public:
		static CommandFactory& getInstance() {
			static CommandFactory f;
			return f;
		}
		Command* getCommand(const std::string& name) {
			auto c = commands.find(name);
			if (c == commands.end()) {
				throw std::runtime_error("unknown command");
			}
			return commands[name]->create();
		}
		bool registerCommand(const std::string& name, CommandCreator* creator) {
			auto c = commands.find(name);
			if (c == commands.end()) {
				commands[name] = creator;
				return true;
			}
			else
				throw std::runtime_error("name already registered");
		}

	private:
		CommandFactory() = default;
		std::map<std::string, CommandCreator*> commands;
	};

	class iWFE {
	public:
		 virtual void doWork() = 0;
	};

	
}