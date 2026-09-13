# OpenSprinkler 2.2.1(5) para la placa ESP-12F de cuatro relés

Esta variante adapta el firmware oficial de OpenSprinkler para ESP8266 a la
placa `ESP8266-WIFI-4-Channels-Relay-Module-AC-DC-ESP-12F-Development-Board`.

## Obtener el binario desde GitHub Actions

El repositorio incluye el flujo **Build ESP8266 four-relay firmware**. Se puede
ejecutar desde la pestaña **Actions**, pulsando **Run workflow**. Cuando termine,
el archivo aparecerá en la sección **Artifacts** con el nombre
`OpenSprinkler-2215-ESP8266-4CH`.

## Compilar con PlatformIO

Desde el directorio del proyecto:

```bash
pio run --environment esp8266_4ch_relay
```

El archivo que se debe cargar en el ESP8266 se genera en:

```text
.pio/build/esp8266_4ch_relay/firmware.bin
```

## Asignación de pines

| Función | GPIO del ESP8266 | Comportamiento eléctrico |
|---|---:|---|
| Estación 1 / relé 1 | 16 | HIGH = activado |
| Estación 2 / relé 2 | 14 | HIGH = activado |
| Estación 3 / relé 3 | 12 | HIGH = activado |
| Estación 4 / relé 4 | 13 | HIGH = activado |
| I2C SDA | 4 | OLED y RTC opcional |
| I2C SCL | 5 | OLED y RTC opcional |
| Sensor 1 | 1 | Entrada con pull-up |
| Sensor 2 | 3 | Entrada con pull-up |
| Botón 1 | 2 | Activo en LOW |
| Botón 2 | 15 | Activo en HIGH; usa el pull-down externo de la placa |
| Botón 3 | 0 | Activo en LOW |

El modelo de datos de OpenSprinkler muestra ocho estaciones en la primera
placa. En este hardware solo las estaciones 1 a 4 tienen una salida física; las
estaciones 5 a 8 deben dejarse sin utilizar.

GPIO0, GPIO2 y GPIO15 son pines de selección del modo de arranque del ESP8266.
No se debe cambiar el cableado documentado de los botones ni mantener un botón
pulsado al encender. GPIO1 y GPIO3 también son TX/RX de la UART, por lo que el
uso de los dos sensores impide utilizar simultáneamente el registro serie
normal.

La placa no tiene el circuito de medición de corriente de OpenSprinkler, booster
para solenoides, controlador de válvulas biestables, radiofrecuencia, Ethernet
cableada ni compatibilidad con expansores de estaciones.

## Prueba segura inicial

Antes de conectar las electroválvulas, se recomienda alimentar únicamente la
placa y comprobar los cuatro relés desde la ejecución manual de estaciones. Los
relés deben permanecer apagados durante el arranque y solo debe activarse el
relé correspondiente a cada una de las estaciones 1 a 4.
