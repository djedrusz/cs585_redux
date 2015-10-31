/*
	Dominik Jedruszczak

	test_event_bus.cpp
	Tests for the "EventBus" singleton.
*/

#include "../gtest/include/gtest/gtest.h"
#include "../src/engine/events/event_bus.hpp"

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

TEST(EventBus, General) {
	ATestEvent testEvent;
	ATestValueEvent testValueEvent(23);
	ATestListener testListener;
	std::function< void(const StevensDev::sgde::IEvent*) > testEventCallback =
		std::bind(&ATestListener::onTestEvent, &testListener, std::placeholders::_1);
	std::function< void(const StevensDev::sgde::IEvent*) > testValueEventCallback =
		std::bind(&ATestListener::onTestValueEvent, &testListener, std::placeholders::_1);

	StevensDev::sgde::EventBus::getDispatcher().addListener(&testEvent, &testEventCallback);
	StevensDev::sgde::EventBus::getDispatcher().preTick();
	StevensDev::sgde::EventBus::getDispatcher().tick(0);
	StevensDev::sgde::EventBus::getDispatcher().postTick();

	StevensDev::sgde::EventBus::getDispatcher().dispatch(&testEvent);
	EXPECT_EQ(testListener.getTestEventCount(), 1);

	StevensDev::sgde::EventBus::getDispatcher().preTick();
	StevensDev::sgde::EventBus::getDispatcher().tick(0);
	StevensDev::sgde::EventBus::getDispatcher().postTick();

	EXPECT_EQ(testListener.getTestEventCount(), 1);

	StevensDev::sgde::EventBus::getDispatcher().addListener(&testValueEvent, &testValueEventCallback);
	StevensDev::sgde::EventBus::getDispatcher().preTick();
	StevensDev::sgde::EventBus::getDispatcher().tick(0);
	StevensDev::sgde::EventBus::getDispatcher().postTick();

	StevensDev::sgde::EventBus::getDispatcher().dispatch(&testValueEvent);
	EXPECT_EQ(testListener.getTestEventCount(), 24);

	StevensDev::sgde::EventBus::getDispatcher().removeListener(&testEvent, &testEventCallback);
	StevensDev::sgde::EventBus::getDispatcher().removeListener(&testValueEvent, &testValueEventCallback);
	StevensDev::sgde::EventBus::getDispatcher().preTick();
	StevensDev::sgde::EventBus::getDispatcher().tick(0);
	StevensDev::sgde::EventBus::getDispatcher().postTick();
}

TEST(EventBus, AddListenerDispatch) {
	ATestEvent testEvent;
	ATestListener testListener;
	std::function< void(const StevensDev::sgde::IEvent*) > testEventCallback =
		std::bind(&ATestListener::onTestEvent, &testListener, std::placeholders::_1);

	StevensDev::sgde::EventBus::getDispatcher().addListener(&testEvent, &testEventCallback);
	StevensDev::sgde::EventBus::getDispatcher().preTick();
	StevensDev::sgde::EventBus::getDispatcher().tick(0);
	StevensDev::sgde::EventBus::getDispatcher().postTick();

	StevensDev::sgde::EventBus::getDispatcher().dispatch(&testEvent);

	EXPECT_EQ(testListener.getTestEventCount(), 1);

	StevensDev::sgde::EventBus::getDispatcher().removeListener(&testEvent, &testEventCallback);
	StevensDev::sgde::EventBus::getDispatcher().preTick();
	StevensDev::sgde::EventBus::getDispatcher().tick(0);
	StevensDev::sgde::EventBus::getDispatcher().postTick();
}

TEST(EventBus, RemoveListener) {
	ATestEvent testEvent;
	ATestListener testListener;
	std::function< void(const StevensDev::sgde::IEvent*) > testEventCallback =
		std::bind(&ATestListener::onTestEvent, &testListener, std::placeholders::_1);

	StevensDev::sgde::EventBus::getDispatcher().addListener(&testEvent, &testEventCallback);
	StevensDev::sgde::EventBus::getDispatcher().preTick();
	StevensDev::sgde::EventBus::getDispatcher().tick(0);
	StevensDev::sgde::EventBus::getDispatcher().postTick();

	StevensDev::sgde::EventBus::getDispatcher().removeListener(&testEvent, &testEventCallback);
	StevensDev::sgde::EventBus::getDispatcher().preTick();
	StevensDev::sgde::EventBus::getDispatcher().tick(0);
	StevensDev::sgde::EventBus::getDispatcher().postTick();

	StevensDev::sgde::EventBus::getDispatcher().dispatch(&testEvent);
	
	EXPECT_EQ(testListener.getTestEventCount(), 0);
}

TEST(EventBus, MultipleListenersMultipleDispatch) {
	ATestEvent testEvent;
	ATestValueEvent testValueEvent(23);
	ATestListener testListener;
	std::function< void(const StevensDev::sgde::IEvent*) > testEventCallback =
		std::bind(&ATestListener::onTestEvent, &testListener, std::placeholders::_1);
	std::function< void(const StevensDev::sgde::IEvent*) > testValueEventCallback =
		std::bind(&ATestListener::onTestValueEvent, &testListener, std::placeholders::_1);

	StevensDev::sgde::EventBus::getDispatcher().addListener(&testEvent, &testEventCallback);
	StevensDev::sgde::EventBus::getDispatcher().addListener(&testValueEvent, &testValueEventCallback);
	StevensDev::sgde::EventBus::getDispatcher().preTick();
	StevensDev::sgde::EventBus::getDispatcher().tick(0);
	StevensDev::sgde::EventBus::getDispatcher().postTick();

	StevensDev::sgde::EventBus::getDispatcher().dispatch(&testEvent);
	StevensDev::sgde::EventBus::getDispatcher().dispatch(&testValueEvent);
	
	EXPECT_EQ(testListener.getTestEventCount(), 24);

	StevensDev::sgde::EventBus::getDispatcher().removeListener(&testEvent, &testEventCallback);
	StevensDev::sgde::EventBus::getDispatcher().removeListener(&testValueEvent, &testValueEventCallback);
	StevensDev::sgde::EventBus::getDispatcher().preTick();
	StevensDev::sgde::EventBus::getDispatcher().tick(0);
	StevensDev::sgde::EventBus::getDispatcher().postTick();
}