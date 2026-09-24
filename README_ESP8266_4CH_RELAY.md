# OpenSprinkler 2.2.1(6) para ESP-12F de cuatro relés

Adaptación de la versión oficial `221(6)` (commit
`097114c26fd7d26044a84bc4ef74d079f5c2c0a5`) para la placa
`ESP8266-WIFI-4-Channels-Relay-Module-AC-DC-ESP-12F-Development-Board`,
con **4 MB de flash**. Conserva el mapa de pines comprobado en la versión 221(5).

## Descargar e instalar desde 221(5)

1. Abre [Releases](https://github.com/solideus/OpenSprinkler-ESP8266-WIFI-4-Channels-Relay-Module-AC-DC-ESP-12F-Development-Board/releases/latest)
   y descarga **`OpenSprinkler-2216-ESP8266-4CH.bin`**, dentro de **Assets**.
   Los archivos automáticos «Source code» contienen código fuente, no firmware instalable.
2. En OpenSprinkler, exporta una copia de la configuración. Si quieres conservar
   el historial de riego, descárgalo antes: **221(6) elimina los registros antiguos
   al pasar al nuevo formato de almacenamiento**. La actualización de 221(5) a
   221(6) normalmente conserva programas, ajustes y Wi-Fi; no necesita un reset.
3. Detén el riego. Desde la misma red local, entra en
   `http://IP-DE-TU-PLACA/update`, o abre «Actualizar firmware» en el menú.
   Selecciona el `.bin` de esta release, introduce la contraseña del dispositivo
   y carga el archivo. Mantén la alimentación hasta que termine y reinicie.
4. Comprueba que aparece **2.2.1(6)**. Revisa la configuración existente:
   estación 1 como maestra y estaciones 2, 3 y 4 como zonas. No hace falta cambiar
   el cableado. Ejecuta una prueba breve por zona y verifica el cierre al finalizar,
   la pantalla, los botones y la hora con RTC.

El puerto HTTP principal debe ser distinto de **8080**, reservado para las
transferencias de actualización. Si usas 8080 para la interfaz, cámbialo antes.

**Usa únicamente el binario adaptado de este repositorio.** La actualización
automática desde el catálogo oficial está desactivada, porque sus imágenes no
incluyen el soporte de nuestros cuatro relés. La carga manual con contraseña
continúa disponible en 221(6). No se necesita conectar la placa al ordenador
para la actualización normal por Wi-Fi.

La release incluye `SHA256SUMS.txt` y `BUILD_INFO.txt` para comprobar el archivo
y conocer el commit exacto de origen. En Linux/macOS, usa `sha256sum`/`shasum -a 256`;
en PowerShell, `Get-FileHash .\OpenSprinkler-2216-ESP8266-4CH.bin -Algorithm SHA256`.
La suma del `.bin` debe coincidir con la publicada.

## Qué cambia y qué se conserva

- Integra el código oficial 221(6), incluidos el nuevo almacenamiento acotado de
  registros, estaciones agrupadas («Bundle»), sensores meteorológicos y correcciones
  de programación, red y MQTT descritas en la release oficial.
- Usa un perfil de placa propio; evita detectar o accionar el hardware de salidas
  del OpenSprinkler oficial. Los relés se inicializan en LOW.
- Aplica las salidas ya secuenciadas por 221(6), con prioridad para la estación
  maestra. Conserva el uso simultáneo de maestra + zona y las cuatro salidas.
- Conserva OLED SSD1306, RTC opcional y bus I2C a 100 kHz, botones con B2 activo
  en HIGH y las dos entradas de sensores.
- No incluye medición de corriente, booster, válvulas biestables, RF, Ethernet
  ni expansores físicos de estaciones, que esta placa no incorpora.

La versión **221(5) fue probada físicamente por el propietario** con los cuatro
relés, maestra + tres zonas, OLED, botones y RTC. Para **221(6)** se realizan
compilaciones y pruebas automatizadas; la comprobación en la placa después de
instalar sigue pendiente. Las entradas de sensores conservan sus pines, pero no
se certifica ningún sensor físico nuevo.

## Asignación de pines

| Función | GPIO | Comportamiento |
|---|---:|---|
| Estación 1 / maestra | 16 | HIGH = activado |
| Estación 2 / zona 1 | 14 | HIGH = activado |
| Estación 3 / zona 2 | 12 | HIGH = activado |
| Estación 4 / zona 3 | 13 | HIGH = activado |
| I2C SDA | 4 | OLED y RTC opcional |
| I2C SCL | 5 | OLED y RTC opcional, 100 kHz |
| Sensor 1 | 1 | Entrada con pull-up |
| Sensor 2 | 3 | Entrada con pull-up |
| Botón 1 | 2 | Activo en LOW |
| Botón 2 | 15 | Activo en HIGH; pull-down externo de la placa |
| Botón 3 | 0 | Activo en LOW |

La función maestra depende de la configuración guardada; no se fuerza al
actualizar. El modelo de datos muestra ocho estaciones en la primera placa;
solo las estaciones 1 a 4 tienen salida física. Deja las estaciones 5 a 8 sin uso.

GPIO0, GPIO2 y GPIO15 determinan el arranque del ESP8266: conserva el cableado
de botones y no los mantengas pulsados al encender. GPIO1 y GPIO3 son también
TX/RX de la UART; no utilices simultáneamente sensores en esos pines y el
registro serie normal.

## Compilar y publicar en GitHub

El flujo **Build ESP8266 four-relay firmware** ejecuta las pruebas nativas y API,
compila esta placa y el ESP8266 oficial como comprobación de compatibilidad,
y guarda **solo el binario adaptado** en el artefacto `OpenSprinkler-2216-ESP8266-4CH`.

Para publicar una nueva versión ya integrada: **Actions → Build ESP8266
four-relay firmware → Run workflow**, selecciona **master** y marca
**publish_release**. Tras superar las pruebas y la compilación crea la etiqueta
correspondiente a `OS_FW_VERSION`/`OS_FW_MINOR`, sube los archivos y marca la
release como Latest. Requiere sus notas en `docs/releases/<etiqueta>.md`.
Una release existente se conserva sin sobrescribirla. Si solo existe su etiqueta,
se detiene para que se revise antes de publicar.
Como parte de esta actualización, la primera integración de **221(6)** en
`master` también publica su release automáticamente después de superar todas
las comprobaciones. Esta excepción se limita a `221(6)-ESP12F-4CH`.
Las pull requests solo comprueban/compilan; otras versiones requieren la opción
explícita `publish_release`.

Compilación local (Python 3.12, Node.js 20, PlatformIO 6.2.0):

```bash
git submodule update --init --recursive
python3 -m pip install platformio==6.2.0
npm ci
pio run --environment esp8266_4ch_relay
```

El resultado es `.pio/build/esp8266_4ch_relay/firmware.bin`.
La configuración usa DIO, CPU a 160 MHz, flash a 80 MHz y
`eagle.flash.4m2m.ld` (4 MB de flash, 2 MB LittleFS), igual que 221(5).

Con `g++`, `libmosquitto-dev` y `libssl-dev` instalados, `make test-api` ejecuta
las pruebas. `python3 tools/package_esp8266_4ch.py` prepara los archivos de la
release en un directorio vacío `dist/esp8266_4ch/`.
