#include "pch.h"
#include <iostream>

class ISwitchable
{
public:
	virtual void Off() = 0;
	virtual void On() = 0;
};

class MySwitch {
private:
	ISwitchable& switchable;
	bool state{ false };
public:
	MySwitch(ISwitchable& switchable) : switchable(switchable) {}
	void Toggle() {
		if (state) {
			state = false;
			switchable.Off();
		}
		else {
			state = true;
			switchable.On();
		}
	}
};

class Lamp : public ISwitchable
{
public:
	void On() override {
		std::cout << "Lamp On" << std::endl;
	}
	void Off() override {
		std::cout << "Lamp Off" << std::endl;
	}
};

class Fan : public ISwitchable
{
public:
	void On() override {
		std::cout << "Fan On" << std::endl;
	}
	void Off() override {
		std::cout << "Fan Off" << std::endl;
	}
};

int main()
{
	Lamp lamp;
	Fan fan;
	
	MySwitch mySwitch1(lamp);
	mySwitch1.Toggle();

	MySwitch mySwitch2(fan);
	mySwitch2.Toggle();
}
