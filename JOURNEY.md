# Orbit-Chroma-9 
# Devlog #1: Schematic Done, Moving to PCB Layout

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




# Devlog #2: Routing the PCB
Designing the schematic is one thing, but laying out the actual printed circuit board (PCB) was where hardware real estate, trace routing and physical tolerances collided. The goal was simple on paper: fit the 3x3 switch matrix, the rotary encoder, per-key RGB LEDs, the OLED screen header, and the Seeduino XIAO RP2040 onto a tight desktop footprint. In practice, every millimeter was a puzzle.

## Phase 1: Component Placement & Real Estate Strategy
The first hurdle on Orbit-Chroma-9 was component positioning. Because we were building a compact 9-key macropad, component clearance had to be exact:

**The XIAO RP2040 Footprint:** We positioned the XIAO MCU centrally on the underside to keep trace lengths balanced to all matrix corners while leaving top-side clearance clean for mechanical switches.

**Key Matrix Layout:** Aligning the 3x3 mechanical switch footprints on standard 19.05mm grid spacing so keycaps wouldn't collide during operation.

**Encoder & Screen Alignment:** Placing the rotary encoder knob and the 128x32 OLED header so they sit flush with the enclosure cutouts designed in Fusion 360 without overlapping underlying PCB components.

## Phase 2: PCB Routing Friction & The Errors We Hit
Once components were placed, routing the copper traces brought a wave of physical layout challenges:

### 1. Per-Key RGB LED Data Line Daisy-Chaining (SK6812MINI-E)
The Problem: The SK6812MINI-E LEDs require a continuous, single-wire serial data line running from DOUT of one LED into DIN of the next across all 9 keys. Crossing these high-speed data lines over the 3x3 matrix row/column power and key lines caused trace congestion and routing dead-ends on a 2-layer board.

The Fix: We isolated the bottom copper layer primarily for ground pours and cross-over vias, routing the LED data line in a strict "snake" path across the 3x3 grid on the top layer to eliminate line intersections.

### 2. Power Rail & Decoupling Stability
The Problem: Driving 9 SK6812MINI-E RGB LEDs alongside an OLED screen and the RP2040 MCU from the 5V USB rail created sudden current draw spikes, introducing potential noise into the I2C lines of the SSD1306 display.

The Fix: We widened the 5V power traces, added dedicated ground copper pours under high-current paths, and placed decoupling capacitors close to power input pins to stabilize line voltage.

### 3. I2C Bus Pull-Ups & Pin Pinout Constraints
The Problem: The XIAO RP2040 has a compact GPIO count. Routing SDA and SCL for the OLED display across the board while maintaining clean matrix row/col pin assignments meant carefully managing trace crossovers near the MCU header pins.

The Fix: We optimized pin assignments directly on the RP2040 footprint in the schematic editor prior to final trace lock to minimize long, wrapping traces on the PCB.

## Phase 3: Final Design Rule Check (DRC) & Manufacturing Prep
Before exporting manufacturing files, we ran through a strict verification process:

**Design Rule Check (DRC):** Verified trace clearances, minimum drill hole sizes, and annular rings against fabrication tolerances to ensure zero short circuits or unrouted nets.

**3D Clearance Inspection:** Imported the complete board 3D model (complete with switch sockets, encoder, OLED header, and XIAO RP2040 height profiles) back into Fusion 360 to verify that every component aligned with the Orbit-Chroma-9 enclosure walls.

**Gerber & Drill Export:** Generated final Gerber files, drill maps, and assembly layer outputs, ready for production.

## Current PCB Status
The PCB design for Orbit-Chroma-9 is completely routed, verified through DRC, and finalized for production!



# Devlog #3: Mechanical Integration & QMK Firmware — Bringing Orbit-Chroma-9 to Life
With the schematic routed and the PCB finalized, the true test of Orbit-Chroma-9 came down to two things: making sure everything fit inside a custom Fusion 360 enclosure, and writing QMK firmware that actually ran without crashing the OLED display.

Here is how the physical enclosure and the software engine came together to complete the macro pad.

## Part 1: Mechanical CAD Design in Fusion 360
Designing an enclosure isn't just about making a pretty shell—it’s about managing tight tolerances so mechanical switches, keycaps, and hardware headers don't bind or rattle.

1. **Key Matrix & Plate Clearance**
The Challenge: Mechanical switches require an exact 14.0mm x 14.0mm plate cutout on a 19.05mm grid. If the top plate flexes too much, switch retention pins slip out; if it’s too rigid, assembling hot-swap sockets becomes a nightmare.

The Solution: Modeled a 1.5mm integrated top plate in Fusion 360 with reinforced internal corner ribbing to support keypress force while maintaining structural stiffness.

2. **The OLED & Encoder Window**
The Challenge: The 128x32 OLED display and the rotary encoder sat at different Z-heights above the PCB relative to the low-profile Seeeduino XIAO RP2040 underneath.

The Solution: Used parameter-driven sketches to offset the OLED acrylic cutout flush with the top housing, while adding a recessed bevel around the rotary encoder knob so it rotates smoothly without scraping the enclosure wall.

3. **Exporting for Fabrication**
Once the multi-part assembly was modeled and verified against the PCB 3D clearance geometry, the parts were exported as high-precision STEP files ready for 3D printing and manufacturing.

## Part 2: QMK Firmware & The OLED Animation Battle
With the hardware specs locked, focus shifted to VS Code, GitHub Desktop, and compiling QMK firmware for the Seeeduino XIAO RP2040.

1. **Core Matrix & Encoder Setup**
Mapped the 3x3 key matrix across 3 functional layers (BASE, GAMING, MEDIA).

Configured ENCODER_CW_CCW to drive desktop volume controls on Layer 0 and track skipping on Layer 2 seamlessly alongside keypress events.

2. **The Great OLED Bug (And How It Was Fixed)**
The Problem: Initial attempts to display heavy multi-frame animated pixel art (like a Minecraft Steve sword swing) flooded the SSD1306 display buffer. The screen glitched, output continuous memory noise, or froze the RP2040.

The Fix: Shifted to a clean, lightweight layer-switched icon system. By using get_highest_layer(layer_state) and tiny 8x8 PROGMEM icon arrays (cat_pose_idle, cat_pose_left, cat_pose_right), the display now updates layer status text and swaps character poses instantly when switching layers—with zero memory buffer leaks, zero screen lag, and rock-solid stability.

## The Final Outcome
From drawing the first schematic wire to routing the PCB, modeling the enclosure in Fusion 360, and pushing error-free QMK code to GitHub, Orbit-Chroma-9 evolved from a rough concept into a fully realized, desktop-ready macro pad.

The enclosure fits like a glove, the encoder and keys operate smoothly across all layers, and the OLED screen delivers clean status feedback. The project is officially built, committed, and ready for action!
