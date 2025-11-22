#include <Wire.h>    // For AS5600 I2C communication
#include <AS5600.h>  // For AS5600 sensor library

#include <USBComposite.h> // Core USB Composite library
// USBHID.h is likely pulled in by USBComposite.h or HIDJoystick.h, but if you get errors,
// you might need to add #include <USBHID.h> explicitly.
// For now, let's stick to what simplejoystick.ino showed.

// Declare the USBHID object, which is the base for our HID device.
// This is the common way to create a generic HID device in this framework.
USBHID HID;

// Declare the HIDJoystick object, which is a specific type of HID device (joystick).
// It takes the USBHID object as an argument during construction.
HIDJoystick Joystick(HID);

AS5600 as5600;

// Define the range for your steering input
const int MIN_ANALOG_READ = 0;
const int MAX_ANALOG_READ = 4095; // AS5600 reads up to 4095 (4096 steps)

// The simplejoystick example uses 0-1023 for its X-axis.
// Let's first map to this range to ensure it works with the example's implicit descriptor.
// If your game needs -32767 to 32767, we might need a custom HID report descriptor later,
// but let's get 0-1023 working first as a proof of concept.
const int MIN_JOYSTICK_OUTPUT = 0;
const int MAX_JOYSTICK_OUTPUT = 1023; // Max value used in simplejoystick example

void setup() {
  // Initialize the AS5600 sensor
  Wire.begin(); // Initializes I2C using PB6 (SCL) and PB7 (SDA)

  if (as5600.begin()) {
    // You can optionally use USB Serial for debugging if you add USBCompositeSerial
    // and USBComposite.add(&Serial_usb) etc., but for now, let's keep it simple.
    // Serial_usb.println("AS5600 detected!");
  } else {
    // Handle AS5600 not found error
    // Serial_usb.println("AS5600 not found!");
    while (1); // Halt if AS5600 not found
  }

  // Initialize the HID (Joystick) device.
  // HID_JOYSTICK is a predefined type in the library.
  HID.begin(HID_JOYSTICK);

  // Wait for the USB Composite device to be ready.
  // This ensures the host PC has enumerated the device.
  while (!USBComposite);
}

void loop() {
  float angle = as5600.readAngle();

  // Map the AS5600 angle (0-4095) to the joystick's X-axis range (0-1023).
  // Adjust MIN_ANALOG_READ and MAX_ANALOG_READ if your physical steering has a smaller effective range.
  int joystickXValue = map(angle, MIN_ANALOG_READ, MAX_ANALOG_READ, MIN_JOYSTICK_OUTPUT, MAX_JOYSTICK_OUTPUT);

  // Set the X-axis value for the joystick.
  Joystick.X(joystickXValue);

  // You might not need this much delay for smooth steering,
  // but a small delay (e.g., 5-20ms) is often good to avoid
  // overwhelming the USB bus and for debouncing.
  delay(10);
}
