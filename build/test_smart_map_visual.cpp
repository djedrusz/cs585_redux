/*
	Dominik Jedruszczak

	Visual tests for the "SmartMap" class.
*/

#define SMART_MAP_DEBUG
#include "../src/engine/containers/smart_map.hpp"

int main(int argc, char** argv) {
	using namespace StevensDev::sgdc;
	bool working = true;

	SmartMap< int > smartMap;
	smartMap.print();

	smartMap.put("a", 1);
	smartMap.print();

	smartMap.put("ab", 2);
	smartMap.print();

	smartMap.put("abbb", 3);
	smartMap.print();

	smartMap.put("bbb", 4);
	smartMap.print();

	working & (smartMap.get("a") == 1);
	working & (smartMap.get("ab") == 2);
	working & (smartMap.get("abbb") == 3);
	working & (smartMap.get("bbb") == 4);

	smartMap.remove("a");
	smartMap.print();

	smartMap.remove("bbb");
	smartMap.print();

	smartMap.remove("abbb");
	smartMap.print();

	smartMap.remove("ab");
	smartMap.print();

	std::cout << "Working? -- " << working << std::endl;
	return 0;
}