// Grafok beolvasasara szolgalo klassz

#pragma once

#include <fstream>
#include <sstream>
#include <unordered_map>

template <class A, class B>
using list = std::unordered_map<A, std::unordered_map<A, B>>;

class graphReader {
public:
	template <typename A, typename B>
	static list<A, B> adjacencyList(const char * const fileName, const bool& undirectedGraph = false) {
		std::ifstream inputFile(fileName);

		unsigned numOfNodes;
		inputFile >> numOfNodes;

		A kezdoPont;
		A vegPont;

		char colon;
		std::string line;

		list<A, B> graph;

		while(getline(inputFile, line)) {
			std::istringstream iss(line);

			iss >> kezdoPont;
			iss >> colon;

			while(iss >> vegPont) {
				graph[kezdoPont][vegPont] = static_cast<B>(1);

				if(undirectedGraph) {
					graph[vegPont][kezdoPont] = static_cast<B>(1);
				}
			}
		}

		return graph;
	}
};
