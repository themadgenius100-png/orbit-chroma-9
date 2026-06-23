# Orbit-Chroma-9 Devlog #1: Schematic Done, Moving to PCB Layout

## The Vision
I'm building a 9-key mechanical macro pad powered by a Seeeduino XIAO. I'm planning to include an I2C OLED screen (hoping to get live Bongo Cat animations running on it!), a rotary encoder knob for volume control, and addressable RGB LEDs for underglow backlighting.

---

## The Journey So Far

### 1. Fixing the Matrix Math
Since the Seeeduino XIAO doesn't have a ton of GPIO pins, I couldn't connect all 9 switches directly. Instead, I wired them into a 3x3 keyboard matrix. This lets me scan all 9 keys using just 6 pins, which leaves the remaining pins open to run the OLED display screen without running out of IO.

### 2. Adding Diodes
To make sure the keys register properly when pressed at the same time, I added a switching diode to every switch. They act like one-way valves to prevent ghosting when holding down multiple keys. 

### 3. Hardware Add-ons
I'm adding three main features to the board:
* **Rotary Encoder (SW10):** An infinite spinning knob that handles volume control by tracking internal switch pulses.
* **OLED Screen (J1):** A tiny screen for animations that runs on I2C communication, meaning it only uses two lines (SDA and SCL) instead of a massive bundle of wires.
* **RGB LEDs:** Daisy-chained NeoPixels that share a single data pin to control color and brightness individually.

---

## Roadblocks & Lessons Learned

* **The Grid and Spaghetti Wire Mess:** When I first started drawing connections in KiCad, it turned into a massive spiderweb of overlapping green lines. To make it worse, my grid settings were mismatched, so wires looked crooked and wouldn't snap onto the component pins. I fixed it by resetting my grid snap, wiping the messy wires, and using Global Labels instead of drawing lines across the whole page. It looks way more professional now.
* **Diode Orientation:** Placing 9 diodes in a tight grid got confusing, and I realized halfway through that I mixed up the direction on a few of them. If they face the wrong way, the switch breaks because current can't flow back to the row pins. I had to look closely at the symbols and flip them so they all match.
* **Missing XIAO Footprint:** KiCad's Electrical Rules Checker threw an error because it couldn't find a built-in footprint for the Seeeduino XIAO. After doing some research, I swapped it for a standard DIP-14 footprint. Since it shares the exact same 2.54mm pin spacing, the physical board will line up perfectly and the XIAO can slide right in.

---

## What's Next
Now that the schematic is done, I'm hitting 'F8' to pull all the components over into the 2D PCB editor canvas. Next up is the hard part: routing the physical copper lines without letting them cross each other!