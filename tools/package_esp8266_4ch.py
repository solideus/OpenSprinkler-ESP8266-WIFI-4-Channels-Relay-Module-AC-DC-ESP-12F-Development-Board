"""Package only the custom four-relay image, with source identity and SHA-256."""

import hashlib
import os
from pathlib import Path
import re
import shutil
import subprocess

ROOT = Path(__file__).resolve().parents[1]
defines = (ROOT / "defines.h").read_text()


def define(name):
    return int(re.search(r"^#define\s+" + name + r"\s+(\d+)", defines, re.M)[1])


version = define("OS_FW_VERSION")
minor = define("OS_FW_MINOR")
tag = f"{version}({minor})-ESP12F-4CH"
display_version = ".".join(str(version)) + f"({minor})"
name = f"OpenSprinkler-{version}{minor}-ESP8266-4CH"
source = ROOT / ".pio/build/esp8266_4ch_relay/firmware.bin"
image = source.read_bytes()
# ESP8266 image, DIO, 4 MB flash, within the 1 MB application slot.
if len(image) < 1024 or len(image) > 1044464 or image[0] != 0xE9:
    raise SystemExit("Invalid ESP8266 firmware image or size")
if image[2] != 2 or image[3] >> 4 != 4:
    raise SystemExit("Expected DIO firmware configured for 4 MB flash")
if not (ROOT / "docs/releases" / f"{tag}.md").is_file():
    raise SystemExit(f"Missing release notes for {tag}")

out = ROOT / "dist/esp8266_4ch"
out.mkdir(parents=True, exist_ok=True)
if any(out.iterdir()):
    raise SystemExit("Output directory must be empty to avoid packaging old assets")
binary = out / f"{name}.bin"
binary.write_bytes(image)
shutil.copyfile(ROOT / "README_ESP8266_4CH_RELAY.md", out / "INSTALACION.md")
commit = subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=ROOT, text=True).strip()
dirty = subprocess.check_output(["git", "diff", "--name-only", "HEAD"], cwd=ROOT, text=True).strip()
info = (
    f"Firmware: OpenSprinkler {display_version}\n"
    f"Board: ESP-12F four-relay module, 4 MB flash, 2 MB LittleFS\n"
    f"PlatformIO environment: esp8266_4ch_relay\n"
    f"Source commit: {commit}\n"
    f"Working tree changes: {'yes' if dirty else 'no'}\n"
    f"Image: {binary.name}\n"
    f"Size: {len(image)} bytes\n"
    f"Relay GPIOs: 16, 14, 12, 13 (active HIGH)\n"
    f"Online official firmware updates: disabled; manual custom .bin upload supported\n"
    f"Validation: automated builds/tests; 221(6) device validation pending\n"
)
(out / "BUILD_INFO.txt").write_text(info)
checksums = "".join(
    f"{hashlib.sha256(p.read_bytes()).hexdigest()}  {p.name}\n"
    for p in sorted(out.iterdir()) if p.is_file()
)
(out / "SHA256SUMS.txt").write_text(checksums)
print(info + checksums)
if os.getenv("GITHUB_OUTPUT"):
    with open(os.environ["GITHUB_OUTPUT"], "a") as output:
        output.write(f"tag={tag}\nversion={display_version}\nartifact={name}\n")
