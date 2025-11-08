# ESP8266 WiFi Web Server for Simple Room Control

A basic ESP8266 web server to control room devices. This code serves a simple HTML page over WiFi, allowing you to toggle a light (on pin D4) and a fan from your browser. Ideal for simple IoT or home automation projects.

## 🚀 Features

* **Web Interface:** Serves a simple HTML page with buttons.
* **WiFi Connected:** Connects to your local WiFi network.
* **Light Control:** Toggles an LED connected to pin `D4`.
* **Fan Control:** Includes a toggle for a fan (logic is implemented, physical connection is a placeholder).
* **Responsive:** The server updates the button text ("Turn On" / "Turn Off") based on the device's current state.

---

## 🛠️ Hardware Requirements

* An ESP8266-based board (like NodeMCU or Wemos D1 Mini).
* An LED.
* (Optional) A relay module to control an actual fan.
* A micro-USB cable.

---

## 🔧 How to Use

1.  **Clone/Download:** Get this code onto your local machine.
2.  **Open in Arduino IDE:** Open the `.ino` file in your Arduino IDE.
3.  **Install ESP8266 Core:** If you haven't already, add the ESP8266 board manager:
    * Go to **File > Preferences**.
    * Add this URL to **Additional Boards Manager URLs**: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
    * Go to **Tools > Board > Boards Manager...**, search for `esp8266`, and install it.
4.  **Select Your Board:** Go to **Tools > Board** and select your specific ESP8266 board (e.g., "NodeMCU 1.0 (ESP-12E Module)").
5.  **Update Credentials:** Change these two lines at the top of the code to match your WiFi network:
    ```cpp
    const char* ssid = "YOUR_WIFI_SSID";
    const char* password = "YOUR_WIFI_PASSWORD";
    ```
6.  **Upload:** Connect your ESP8266 board via USB, select the correct COM port, and click the **Upload** button.
7.  **Find IP Address:** Open the **Serial Monitor** (set baud rate to `9600`). After it connects to WiFi, it will print its IP address.
    ```
    Connecting to WiFi...
    ..
    WiFi connected
    IP address: 
    192.168.1.XX
    ```
8.  **Control:** Open a web browser on any device connected to the same WiFi network and enter the IP address (e.g., `http://192.168.1.XX`). You will see the control page.

---

## ⚙️ Customization

### Controlling the Fan

The code for the fan (`handleFan`) is a placeholder. To control a real fan, you would typically use a relay module.

1.  **Define the pin:**
    ```cpp
    #define led D4
    #define fanPin D5 // Example: Use pin D5 for the fan relay
    ```
2.  **Set pin in `setup()`:**
    ```cpp
    void setup() {
      // ... existing setup code ...
      pinMode(led, OUTPUT);
      pinMode(fanPin, OUTPUT); // Add this line
      // ...
    }
    ```
3.  **Update `handleFan()`:**
    ```cpp
    void handleFan() {
      fanState = !fanState; // Toggle the state of the fan
      digitalWrite(fanPin, fanState ? HIGH : LOW); // Control the fan relay
      handleRoot(); // Redirect to the main page
    }
    ```

### Adding More Devices

You can easily add more devices by following the pattern for the light and fan:

1.  Add a new state variable (e.g., `bool heaterState = false;`).
2.  Add a new pin define (e.g., `#define heaterPin D6`).
3.  Set the `pinMode` in `setup()`.
4.  Add a new server handler in `setup()` (e.g., `server.on("/heater", HTTP_GET, handleHeater);`).
5.  Add a new button section in `handleRoot()`.
6.  Create the new handler function (e.g., `void handleHeater() { ... }`).
