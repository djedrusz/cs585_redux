/*
	Dominik Jedruszczak

	test_event_dispatcher.cpp
	Tests for the "EventDispatcher" class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/events/event_dispatcher.hpp"

class TestEvent : public StevensDev::sgde::IEvent {
	private:
		const std::string type = "TEST";
	public:
		const std::string& getType() const { return type; }
};

class TestValueEvent : public StevensDev::sgde::IEvent {
	private:
		const std::string type = "TEST_VALUE";
		const unsigned int value;
	public:
		TestValueEvent(unsigned int value)
		:	value(value) {
			;
		}
		const std::string& getType() const {
			return type;
		}
		const unsigned int getValue() const {
			return value;
		}
};

class TestListener {
	private:
		unsigned int testEventCount = 0;	
	public:
		void onEvent(const StevensDev::sgde::IEvent& event) {
			if (event.getType() == "TEST") {
				testEventCount++;
			}
			if (event.getType() == "TEST_VALUE") {
				const TestValueEvent& tve = 
					dynamic_cast< const TestValueEvent& >(event);
					testEventCount += tve.getValue();
			}
		}
		unsigned int getTestEventCount() {
			return testEventCount;
		}
};

TEST(EventDispatcher, General) {
	TestEvent testEvent;
	TestValueEvent testValueEvent(23);
	TestListener testListener;
	StevensDev::sgde::EventDispatcher eventDispatcher;
	std::function< void(const StevensDev::sgde::IEvent&) > testCallback =
		std::bind(&TestListener::onEvent, &testListener, std::placeholders::_1);

	eventDispatcher.addListener(&testCallback);
	eventDispatcher.postTick();

	eventDispatcher.dispatch(testEvent);
	eventDispatcher.dispatch(testValueEvent);

	EXPECT_EQ(testListener.getTestEventCount(), 24);
}