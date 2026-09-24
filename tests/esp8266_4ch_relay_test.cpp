#include "boards/esp8266_4ch_relay.h"
#include "core/output_sequencer.h"

#include <cassert>

using namespace osboard;

int main() {
	// Physical wiring already validated on the user's 221(5) installation.
	assert(RELAY4_STATION_COUNT == 4);
	assert(RELAY4_STATION_PINS[0] == 16);
	assert(RELAY4_STATION_PINS[1] == 14);
	assert(RELAY4_STATION_PINS[2] == 12);
	assert(RELAY4_STATION_PINS[3] == 13);
	assert(relay4_button_pressed(2, false) && !relay4_button_pressed(2, true));
	assert(relay4_button_pressed(15, true) && !relay4_button_pressed(15, false));
	assert(relay4_button_pressed(0, false) && !relay4_button_pressed(0, true));

	// Station 1 is the master; each of stations 2, 3 and 4 remains usable.
	// Feed sequenced bits to the relays, never the unsequenced request bits.
	for (uint8_t zone = 1; zone < 4; zone++) {
		OutputSequencer sequencer;
		uint8_t applied = 0;
		uint8_t desired = 1 | (1U << zone);
		uint8_t priority = 1;
		for (uint8_t i = 0; i < 4; i++) assert(!relay4_station_on(applied, true, i));
		sequencer.advance(&desired, &priority, &applied, 8, 1000);
		assert(relay4_station_on(applied, true, 0));
		assert(!relay4_station_on(applied, true, zone));
		sequencer.advance(&desired, &priority, &applied, 8, 1249);
		assert(!relay4_station_on(applied, true, zone));
		sequencer.advance(&desired, &priority, &applied, 8, 1250);
		assert(relay4_station_on(applied, true, 0));
		assert(relay4_station_on(applied, true, zone));
		for (uint8_t i = 1; i < 4; i++) {
			if (i != zone) assert(!relay4_station_on(applied, true, i));
		}
		// Disabling the controller masks even an outstanding ON request.
		for (uint8_t i = 0; i < 4; i++) assert(!relay4_station_on(applied, false, i));
		desired = 0;
		sequencer.advance(&desired, &priority, &applied, 8, 1251);
		for (uint8_t i = 0; i < 4; i++) assert(!relay4_station_on(applied, true, i));
	}

	// Logical stations 5..8 cannot activate a physical relay.
	for (uint8_t i = 0; i < 8; i++) assert(!relay4_station_on(0xF0, true, i));
	return 0;
}
