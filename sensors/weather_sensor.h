#pragma once

#include "sensor.h"

class WeatherSensor : public Sensor {
	public:
	WeatherSensor(uint32_t interval, float min, float max, const char *name, SensorUnit unit, uint8_t flag, WeatherGetter weather_getter, WeatherAction action);
	WeatherSensor(WeatherGetter weather_getter, char *buf, uint32_t len);

	void emit_extra_json(BufferFiller *bfill);
	static void emit_description_json(BufferFiller *bfill);

	SensorType get_sensor_type() {
		return SensorType::Weather;
	}

	WeatherAction action;

	private:
	float _get_raw_value();
	uint32_t _serialize_internal(char *buf);

	WeatherGetter weather_getter;
};
