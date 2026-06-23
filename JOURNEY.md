# 🚀 Orbit-Chroma-9 : Official Devlog #1
# **Date: June 22, 2026**
# **Status: Schematic Complete 🎛️⚡✅ | Moving to PCB Layout next 🛠️**

---

## 🌌 The Vision
I am building a high-spec, 9-key mechanical macro pad powered by a Seeeduino XIAO. The final build will feature an I2C OLED display screen (aiming for live Bongo Cat animations!), a rotary encoder knob for smooth scrolling/volume control, and an addressable daisy-chained RGB LED array for custom profile backlighting.

---

## 🛠️ The Journey So Far

### Step 1: Mapping the 3x3 Grid Matrix
Because the Seeeduino XIAO has a limited number of pins, I couldn't give all 9 switches their own direct connection. Instead, I learned how to wire them into an efficient **3x3 Keyboard Matrix** (3 rows and 3 columns). This allows the microcontroller to scan 9 distinct keys using only 6 GPIO pins total!

### Step 2: Adding the Electrical "One-Way Valves"
To ensure the macro pad registers clean inputs, I added a switching diode to every single key switch. These act as electrical one-way valves. Without them, pressing multiple keys simultaneously would cause electrical current to backflow, causing accidental ghost keypresses.

### Step 3: Integrating the Advanced Add-ons
To elevate this project from a basic keypad to a cutting-edge desk controller, I integrated three critical hardware features into the circuit:

* **The Rotary Encoder Dial (SW10):** This is an infinite spinning knob that also clicks down like a button. It uses two out-of-phase internal switches ('ENC_A' and 'ENC_B') to send pulses to the brain. By tracking which switch pulses first, the chip knows if I'm turning it clockwise (Volume Up) or counter-clockwise (Volume Down).
* **The I2C OLED Display Window (J1):** A crisp, tiny screen used for status updates and custom animations. Instead of using a bulky ribbon cable with dozens of wires, it uses the **I2C Communication Protocol**, which allows it to stream all of its visual data over just two smart lines: Data ('OLED_SDA') and Clock ('OLED_SCL').
* **The Addressable RGB LEDs (NeoPixels):** To give the macro pad an awesome ambient glow, I planned an under-keycap lighting system. These are smart "NeoPixels", meaning they pass data down a single sequential daisy-chain wire from one light to the next. The microcontroller only needs one data pin to control the color and brightness of every single light individually!

---

## ⚡ Challenges Faced, Overcoming Them & Lessons Learned

### 🔴 Roadblock 1: The Spaghetti Wire Disaster & Grid Alignment Annoyance
When I first tried routing the schematic connections, I tried drawing direct green wire lines across the entire sheet. It immediately turned into a messy "spiderweb" of overlapping lines. To make it worse, my grid settings were mismatched at first! Lines looked slightly crooked and completely refused to snap onto the component pins, making it incredibly confusing to read and triggering errors.

**The Solution:** I fixed my grid snap settings, wiped the messy wires clean, and discovered "Global Labels". Instead of physical wires, I attached matching labels (like 'ENC_A' and 'ENC_B') to the pins. KiCad instantly knows they are connected behind the scenes, keeping my sheet layout looking professional and pristine.

### 🔴 Roadblock 2: The Diode Direction Dilemma
Placing 9 diodes in a perfect grid is harder than it looks. I spent a solid chunk of time realizing I had mixed up the orientations on a few of them. If a diode faces the wrong way, the key switch completely breaks because electricity can't flow back to the row pins.

**The Solution:** I had to carefully inspect the symbols and make sure every single little red triangle faced the exact same direction toward the row nets so current flows flawlessly.

### 🔴 Roadblock 3: The Footprint Missing Link
When running the Electrical Rules Checker (ERC), KiCad threw a fit because it couldn't find the exact technical footprint library file for the physical 'Seeeduino XIAO' chip board.
 
**The Solution:** I did some hardware research, and after countless tries and annoying moments, swapped out the missing footprint for a standard 'Package_DIP:DIP-14_W7.62mm' suggested by Gemini. Because it shares the exact same mechanical spacing (pin pitch: 2.54 mm), the copper holes will align perfectly, allowing the XIAO hardware to interface directly with the layout!

---

## 🎯 What's Next?
Now that the structural blueprint is flawless, I am initializing the board transition layer by hitting 'F8' in KiCad. This will pull all 9 switch footprints and components into the physical 2D PCB editor canvas. Next up is tracing the actual physical copper lines without letting them cross!