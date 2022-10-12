#include<Servo.h>
class YokoServo
{
public:
	uint16_t newMicroseconds;
	bool stopIfTrue;
private:
	Servo servo;
	const uint8_t pinNumber;
	const uint16_t bootMicroseconds;
	const uint16_t stopMicroseconds;
	const uint16_t minimumMicroseconds;
	const uint16_t maximumMicroseconds;
	uint16_t lastMicroseconds;
	bool filterIfTrue;
public:
	YokoServo(uint8_t _pin,uint16_t _boot,uint16_t _stop,uint16_t _min,uint16_t _max,bool _filter)
	:
		pinNumber(_pin),
		bootMicroseconds(_boot),
		stopMicroseconds(_stop),
		minimumMicroseconds(_min),
		maximumMicroseconds(_max),
		lastMicroseconds(_boot),
		newMicroseconds(_boot),
		stopIfTrue(false),
		filterIfTrue(_filter)
	{
		servo.attach(pinNumber);
		servo.writeMicroseconds(bootMicroseconds);
	}
	uint16_t outputMicroseconds(uint16_t microseconds)
	{
		if(stopIfTrue==true)
		{
			servo.writeMicroseconds(stopMicroseconds);
			return stopMicroseconds;
		}
		if(filterIfTrue)_filter();
		servo.writeMicroseconds(_constrain(newMicroseconds));
		lastMicroseconds=newMicroseconds;
		return newMicroseconds;
	}
private:
	void _filter()
	{
		newMicroseconds=newMicroseconds*0.05f+lastMicroseconds*0.95f;
	}
	uint16_t _constrain(uint16_t microseconds)
	{
		return constrain(microseconds,minimumMicroseconds,maximumMicroseconds);
	}
};
void setup(){}
void loop(){}
