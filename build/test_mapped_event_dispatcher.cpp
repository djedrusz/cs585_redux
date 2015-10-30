/*
	Dominik Jedruszczak

	test_mapped_event_dispatcher.cpp
	Tests for the "MappedEventDispatcher" class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/events/mapped_event_dispatcher.hpp"

class TestEvent : public StevensDev::sgde::IEvent {
	private:
		const std::string type = "TEST";
	public:
		const std::string& getType() const { return type; }
};

class TestListener {
	private:
		unsigned int testEventCount = 0;	
	public:
		void onTestEvent(const StevensDev::sgde::IEvent* event) {
			testEventCount++;
		}
		unsigned int getTestEventCount() {
			return testEventCount;
		}
};

/* TODO
Change mapping from string to IEvent*
Change from pointer to dynarr to just dynarr.
Remove listener map if size = 0 after removal.
*/

TEST(MappedEventDispatcher, General) {
	StevensDev::sgde::MappedEventDispatcher mappedEventDispatcher;
	TestEvent testEvent;
	TestListener testListener;
	std::function< void(const StevensDev::sgde::IEvent*) > testEventCallback =
		std::bind(&TestListener::onTestEvent, &testListener, std::placeholders::_1);

	mappedEventDispatcher.addListener(&testEvent, &testEventCallback);
	mappedEventDispatcher.addEvent(&testEvent);

	mappedEventDispatcher.preTick();
	mappedEventDispatcher.tick(0);
	mappedEventDispatcher.postTick();

	EXPECT_EQ(testListener.getTestEventCount(), 1);
}