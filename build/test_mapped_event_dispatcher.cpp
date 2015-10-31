/*
	Dominik Jedruszczak

	test_mapped_event_dispatcher.cpp
	Tests for the "MappedEventDispatcher" class.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/events/mapped_event_dispatcher.hpp"

class ATestEvent : public StevensDev::sgde::IEvent {
	private:
		const std::string type = "test";
	public:
		const std::string& getType() const { return type; }
};

class ATestValueEvent : public StevensDev::sgde::IEvent {
	private:
		const std::string type = "testvalue";
		const unsigned int value;
	public:
		ATestValueEvent(unsigned int value)
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

class ATestListener {
	private:
		unsigned int testEventCount = 0;	
	public:
		void onTestEvent(const StevensDev::sgde::IEvent* event) {
			testEventCount++;
		}
		void onTestValueEvent(const StevensDev::sgde::IEvent* event) {
			const ATestValueEvent* tve = 
				dynamic_cast< const ATestValueEvent* >(event);
			testEventCount += tve->getValue();
		}
		unsigned int getTestEventCount() {
			return testEventCount;
		}
};

TEST(MappedEventDispatcher, General) {
	StevensDev::sgde::MappedEventDispatcher mappedEventDispatcher;
	ATestEvent testEvent;
	ATestValueEvent testValueEvent(23);
	ATestListener testListener;
	std::function< void(const StevensDev::sgde::IEvent*) > testEventCallback =
		std::bind(&ATestListener::onTestEvent, &testListener, std::placeholders::_1);
	std::function< void(const StevensDev::sgde::IEvent*) > testValueEventCallback =
		std::bind(&ATestListener::onTestValueEvent, &testListener, std::placeholders::_1);

	mappedEventDispatcher.addListener(&testEvent, &testEventCallback);
	mappedEventDispatcher.addEvent(&testEvent);

	mappedEventDispatcher.preTick();
	mappedEventDispatcher.tick(0);
	mappedEventDispatcher.postTick();

	EXPECT_EQ(testListener.getTestEventCount(), 1);

	mappedEventDispatcher.preTick();
	mappedEventDispatcher.tick(0);
	mappedEventDispatcher.postTick();

	EXPECT_EQ(testListener.getTestEventCount(), 1);

	mappedEventDispatcher.addListener(&testValueEvent, &testValueEventCallback);
	mappedEventDispatcher.addEvent(&testValueEvent);

	mappedEventDispatcher.preTick();
	mappedEventDispatcher.tick(0);
	mappedEventDispatcher.postTick();

	EXPECT_EQ(testListener.getTestEventCount(), 24);
}

TEST(MappedEventDispatcher, AddListenerEvent) {
	StevensDev::sgde::MappedEventDispatcher mappedEventDispatcher;
	ATestEvent testEvent;
	ATestListener testListener;
	std::function< void(const StevensDev::sgde::IEvent*) > testEventCallback =
		std::bind(&ATestListener::onTestEvent, &testListener, std::placeholders::_1);
}