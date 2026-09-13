#include "weather_sensor.h"

WeatherSensor::WeatherSensor(uint32_t interval, float min, float max, const char* name, SensorUnit unit, uint8_t flag, WeatherGetter weather_getter, WeatherAction action) :
	Sensor(interval, min, max, name, unit, flag),
	action(action),
	weather_getter(weather_getter) {
}

void WeatherSensor::emit_extra_json(BufferFiller* bfill) {
	bfill->emit_p(PSTR("{\"action\":$D}"), this->action);
}

void WeatherSensor::emit_description_json(BufferFiller* bfill) {
	bfill->emit_p(PSTR(
		"{\"n\":\"Weather Sensor\","
		"\"as\":["
			"{\"n\":\"Weather Information\","
			 "\"a\":\"action\","
			 "\"t\":\"enum::WeatherAction\","
			 "\"d\":\"0\"}"
		"]}"
	));
}


float WeatherSensor::_get_raw_value() {
	return this->weather_getter(this->action);
}

uint32_t WeatherSensor::_serialize_internal(char* buf) {
	uint32_t i = 0;
	buf[i++] = static_cast<uint8_t>(this->action);
	return i;
}

WeatherSensor::WeatherSensor(WeatherGetter weather_getter, char* buf, uint32_t len) {
	uint8_t subclass_len = 0;
	uint32_t i = Sensor::_deserialize(buf, len, &subclass_len);
	uint32_t end = i + subclass_len;

	this->action = WeatherAction::MAX_VALUE;
	if (i + 1 <= end) this->action = static_cast<WeatherAction>(buf[i]);
	this->weather_getter = weather_getter;
}
