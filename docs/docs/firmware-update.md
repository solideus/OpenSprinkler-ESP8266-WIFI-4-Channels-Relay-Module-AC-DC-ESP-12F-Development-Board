# Firmware Update

## OpenSprinkler v3 {: .hltitle}

Supports **OTA (over-the-air)** updates - you can upload firmware directly through the web UI. The update page must be accessed locally using the controller's IP address; it is **NOT** available through an OpenThings Cloud (OTC) connection.

!!! warning "Back Up Before Updating"
    Before update, please back up your configurations (Sidebar → **Export Configuration**) so you can quickly restore programs and settings if needed.

    * A **Dotted Version Update**, e.g. 2.2.0→2.2.1, triggers a factory reset and **erases all programs, settings, and logs**.
    * A **Build Number Update**, e.g. 2.2.1(2)→2.2.1(5), **preserves all settings**.

1. [**Download** the firmware file](https://raysfiles.com/os_compiled_firmware/v3.x/) (`.bin` format). The latest is `os_221_rev5.bin`.
2. **Open the Firmware Update page:** At the controller's homepage, swipe from left to right to open the side menu, then choose **Update Firmware**.
3. **Upload the firmware:** Select the `.bin` file downloaded in Step 1, enter your device password, and click **Submit**.
4. **Wait for completion:** The controller will reboot automatically when the update finishes.

---

### Alternative Methods to Open the Firmware Update Page

* **Direct IP address:** Open `http://os-ip/update` in a browser, where `os-ip` is the controller's IP address. Click button **B1** on the controller to display its IP address.
* **WiFi AP mode:** If your controller is currently in WiFi AP mode, connect your computer or phone to the AP SSID shown on the controller's LCD, then open `http://192.168.4.1/update` in a browser.

---

### Troubleshooting

* **Blank Homepage:** If the device homepage is blank or showing an error, and you need to export configuration before updating, see [Blank Page Troubleshooting](troubleshooting.md#ui-app-time-and-lcd).
* **Upload Connection Failure:** The firmware upload uses port `8080`. Make sure this port is not blocked by your computer, router, or firewall, then retry the upload.
* **Controller Stops Responding:** Unplug and reconnect power, then retry the update.
* **Update via Wired Ethernet:** If your controller is connected via wired Ethernet:
    * If it runs firmware `2.2.0` or newer, follow the same steps as WiFi.
    * If it runs `2.1.9` or earlier, update must be done in WiFi mode:
        1. Power off the controller.
        2. Remove the Ethernet module.
        3. Power on - it will boot into WiFi AP mode.
        4. Follow the AP-mode update instructions above.
* **AP Mode Password Issues on Legacy Firmware:** Some older AP-mode update pages do not hash the password before submitting it. If your plaintext password fails, try its **MD5 hash** instead (e.g. the MD5 hash of `opendoor` is `a6d82bced638de3def1e9bbb4983225c`).
* **Firmware Corruption / Device Not Booting**: If device fails to boot after an update, you'll need to re-flash the firmware using a [USB-Serial Programmer](https://opensprinkler.com/product/usb-programmer/).

<hr class="double">

## OpenSprinkler v2.3 {: .hltitle}

Requires a USB cable for firmware update. Follow the legacy [v2.3 Firmware Update Instructions](https://openthings.freshdesk.com/a/solutions/articles/5000832311).

<hr class="double">

## OpenSprinkler Pi (OSPi) {: .hltitle}

Update is done directly on the RPi. Follow [OSPi Firmware Update Instructions](https://openthings.freshdesk.com/a/solutions/articles/5000631599).

<hr class="double">
