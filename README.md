# **Blue Pill + AS5600 Steering Wheel (USB HID Joystick)**

This firmware turns a **Blue Pill (STM32F103C8)** + **AS5600 magnetic encoder** into a USB HID joystick that works in racing games such as **F1 2025**.
The code reads the AS5600 angle (0–4095), maps it to joystick values (0–1023), and exposes it over USB using the **USBComposite HID Joystick** interface.

---

## **📌 Features**

* Reads **AS5600** angle through I2C.
* Converts raw angle into HID joystick X-axis.
* Appears in Windows as **“Maple” Game Controller**.
* Works in F1, Forza, Assetto Corsa, etc.
* No drivers required — pure USB HID.

---

## **📂 Files in This Project**

### **`stm32_as5600.ino`**

* Initializes AS5600 sensor
* Starts USB HID Joystick
* Maps angle → joystick X-axis
* Sends HID updates at 10ms intervals
---

## **🛠 Hardware Setup**

### **1. Wiring — Blue Pill → AS5600**

| AS5600 Pin    | Blue Pill Pin |
| ------------- | ------------- |
| VCC (5V/3.3V) | 3.3V          |
| GND           | GND           |
| SDA           | PB7           |
| SCL           | PB6           |

AS5600 works perfectly at **3.3V**, no level shifting needed.

### **2. Jumpers**

Set **BOOT0 = 1** (the second jumper behind RESET).
BOOT1 remains **0**.

This puts Blue Pill into serial bootloader mode for flashing.

---

## **💻 Software Setup**

### **1. Arduino IDE Setup**

1. Install the **STM32F1 (Blue Pill) Boards** package.
2. Select board:
   **Tools → Board → “Generic STM32F103C Series”**
3. Select sub-board:
   **“BluePill F103C8”**
4. Upload method:
   **Tools → Upload Method → Serial**
5. Port:
   Select your FT232 COM port (e.g., COM9).

---

## **📦 Required Libraries**

Install from Arduino Library Manager:

* **AS5600** by Rob Tillaart

* **USBComposite** (included with STM32 Arduino core)

---

## **⬆️ Flashing the Firmware**

1. Connect FT232 (3.3V) → Blue Pill via TX/RX/GND.
2. Set **BOOT0 = 1**.
3. Click **Upload** in Arduino IDE.
4. After upload, **set BOOT0 back to 0**.
5. Disconnect FT232.

At this point, your code is flashed.

If you open **Tools → Serial Monitor**, you should see changing values when rotating the magnet.

---

## **🎮 Using as Steering Wheel in Windows**

Once flashed:

1. Disconnect FT232.
2. Plug Blue Pill directly to the PC via USB.
3. Windows will detect **Maple USB Device**.
4. Open:

   ```
   Start → Game Controllers → Set up USB Game Controllers
   ```
5. Select **Maple** → **Properties**.
6. Rotate the magnet — the **crosshair (X-axis)** must move smoothly.

If it moves, the joystick driver is working correctly.

---

## **🎯 Setting It Up in F1 25**

1. Launch F1.
2. Go to **Controls → Create Custom Steering Profile**.
3. For “Steer Left”, rotate magnet left.
4. For “Steer Right”, rotate magnet right.
5. Apply settings.
6. Start any session — steering should work instantly.

---

## **⚠️ Notes / Improvements**

* Current HID range is **0–1023**.
  You can later upgrade to a **16-bit axis (−32767 to +32767)** for smoother steering (requires a custom HID descriptor).
* Add smoothing/filters if your AS5600 readings are noisy.
* Blue Pill needs a **good USB cable** — bad cables cause Maple not to appear.

---

## **✅ Summary**

After following this guide:

* Blue Pill acts as a USB joystick
* AS5600 angle controls steering
* Windows recognizes it
* F1 accepts it as a wheel axis
* No drivers or calibration tools required
