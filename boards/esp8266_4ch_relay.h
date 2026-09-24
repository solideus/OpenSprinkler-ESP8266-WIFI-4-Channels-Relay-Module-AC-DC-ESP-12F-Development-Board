#pragma once

#include <stdint.h>

namespace osboard {

// ESP-12F AC/DC four-relay module: all four outputs are active HIGH.
constexpr uint8_t RELAY4_STATION_PINS[] = {16, 14, 12, 13};
constexpr uint8_t RELAY4_STATION_COUNT = sizeof(RELAY4_STATION_PINS);
constexpr uint8_t RELAY4_BUTTON_PINS[] = {2, 15, 0};

inline bool relay4_station_on(uint8_t applied_bits, bool enabled, uint8_t station) {
	return enabled && station < RELAY4_STATION_COUNT && (applied_bits & (1U << station));
}

inline bool relay4_button_pressed(uint8_t pin, bool high) {
	// GPIO15 has an external pull-down; B1 and B3 use internal pull-ups.
	return pin == RELAY4_BUTTON_PINS[1] ? high : !high;
}

} // namespace osboard
