# IC Tester using Arduino UNO

This project is a simple IC (Integrated Circuit) testing tool built using an Arduino UNO. It verifies the functionality of logic gate ICs like the 7400 series by applying logic levels and checking outputs automatically and display the functionality of each gates.

## 📌 Features

- Automatically tests standard logic ICs like 7400 (NAND), 7486 (XOR), 7408 (AND), 7432 (OR), etc.
- Displays status messages on an LCD
- Input control via an I2C keypad
- Clear pass/fail feedback using LCD
- It tests each gates and displays good/bad for individual gates
- Functionality of each gate is displayed so that user can use identify the good gate and use it

---

## 🕹️ Control

- Use keypad to enter the ic number(eg: 7400)
- Click 'A' for the testing and result
- Click 'C' for clearing and testing new ic

## 🔧 Components Used

| Component             | Quantity |
|-----------------------|----------|
| Arduino UNO           | 1        |
| Breadboard            | 1        |
| Jumper Wires          | Many     |
| 16x2 LCD Display (I2C)| 1        |
| I2C Keypad (PCF8574)  | 1        |
| Logic ICs (7400, etc.)| As needed|

---

## 📚 Libraries Used

This project uses the following Arduino libraries:

- [`LiquidCrystal`](https://www.arduino.cc/en/Reference/LiquidCrystal) – For standard LCD control
- [`Wire`](https://www.arduino.cc/en/Reference/Wire) – I2C communication
- [`LiquidCrystal_I2C`](https://github.com/johnrickman/LiquidCrystal_I2C) – For I2C-enabled LCDs
- [`I2CKeyPad`](https://github.com/joeyoung/arduino_keypads) – For reading I2C keypad inputs

> You can install these libraries via the **Library Manager** in the Arduino IDE (`Sketch → Include Library → Manage Libraries`).

---

## ⚙️ How It Works

1. User selects the IC number via the keypad.
2. The Arduino sets HIGH/LOW values to the IC input pins.
3. It reads the output and compares it to the expected result.
4. Displays the result ("PASS"/"FAIL") on the LCD or Serial Monitor.

---

## 🔌 Circuit Diagram

Please refer to the datasheets of each IC for pin configuration.  
Connect the LCD and keypad using I2C ports (SDA/SCL), and IC test pins to Arduino digital pins accordingly.

---

## 🧾 File Info

- `IC_Tester.ino` — Arduino sketch containing the main code logic
- `README.md` — Project documentation
- `LICENSE` — Open-source license (MIT)

---

## 📝 License

This project is licensed under the MIT License – see the [LICENSE](../LICENSE) file for details.

© 2025 Shamil K
