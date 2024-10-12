
# EN
**GenTelegramRFIDReader** is a unique project that integrates Telegram bot functionality with RFID card reading. The program works with the ESP8266 microcontroller, an RFID module, and the Telegram API, allowing you to scan NFC tags and send their data to a Telegram chat. This project includes unique optimizations, asynchronous work, and OTA (over-the-air) updates for ease of use and real-time operation.

## Features
- **RFID Card Reading**: Scan and process NFC tags using the RC522 RFID module.
- **Telegram Bot Integration**: Send scanned card data directly to a Telegram bot.
- **Multi-Card Processing**: Detect and store multiple unique RFID cards in EEPROM.
- **Asynchronous Operations**: Wi-Fi and Telegram API integration run asynchronously for efficient operation.
- **Wi-Fi Auto-Reconnect**: Automatically reconnects to Wi-Fi if the connection is lost.
- **OTA Updates**: Supports firmware updates over the air.
- **Power Saving**: Optimized for low power consumption with light sleep mode.

## Requirements
- ESP8266 microcontroller
- RC522 RFID Module
- Telegram Bot (created via `@botfather`)
- Arduino IDE with the following libraries:
  - `ESP8266WiFi`
  - `WiFiClientSecure`
  - `MFRC522`
  - `UniversalTelegramBot`
  - `EEPROM`
  - `ArduinoOTA`
  - `AsyncTelegram2`

## How to Use
1. **Setup Telegram Bot**: 
   - Create a bot using Telegram’s `@botfather` and get the API token.
   - Set up your Wi-Fi credentials and bot token in the code.

2. **Load the Code**:
   - Use the Arduino IDE to compile and upload the provided code to your ESP8266.

3. **Connect the Hardware**:
   - Connect the RC522 RFID module to your ESP8266 microcontroller following the pin configuration:
     - SDA -> GPIO2
     - RST -> GPIO15

4. **Scan Cards**:
   - Once the device is powered on, you can start scanning RFID cards. The card's UID will be sent to the Telegram bot chat.

5. **Update Firmware**:
   - Use the OTA functionality to update the firmware wirelessly without reconnecting the device.


## Example output
1. Connecting to Wi-Fi
```
Подключение к Wi-Fi...
........
Wi-Fi подключён
IP адрес: 192.168.1.100
```
2. Initializing a Telegram bot
```
Telegram бот инициализирован.
```
3. Scanning a new card
```
Обнаружена новая карта.
UID карты: 04 7A 86 B2
UID сохранён в EEPROM.
Сообщение отправлено в Telegram: "Новая карта с UID: 04 7A 86 B2"
```
4. Rescanning an existing card
```
Карта уже существует в системе.
Сообщение отправлено в Telegram: "Карта уже сохранена в системе."
```
5. OTA Update
```
Начало OTA обновления: флеш-память
Прогресс: 45%
OTA обновление завершено успешно.
```
6. Reconnect to Wi-Fi when connection is lost
```
Wi-Fi отключён. Попытка переподключения...
........
Wi-Fi переподключён
```


# RU
**GenTelegramRFIDReader** — это уникальный проект, который объединяет функциональность Telegram-бота с чтением RFID-карт. Программа работает с микроконтроллером ESP8266, RFID-модулем и API Telegram, позволяя сканировать NFC-метки и отправлять их данные в Telegram-чат. Проект включает уникальные оптимизации, асинхронную работу и обновления по воздуху (OTA) для удобства использования и работы в реальном времени.

## Возможности
- **Чтение RFID-карт**: Сканирование и обработка NFC-меток с помощью RFID-модуля RC522.
- **Интеграция с Telegram-ботом**: Отправка данных о считанных картах напрямую в Telegram-бот.
- **Обработка нескольких карт**: Обнаружение и сохранение нескольких уникальных RFID-карт в EEPROM.
- **Асинхронные операции**: Интеграция Wi-Fi и API Telegram работает асинхронно для повышения эффективности.
- **Автоматическое переподключение Wi-Fi**: Автоматически переподключается к Wi-Fi при обрыве соединения.
- **OTA Обновления**: Поддержка обновлений прошивки по воздуху.
- **Энергосбережение**: Оптимизация потребления энергии с использованием режима легкого сна.

## Требования
- Микроконтроллер ESP8266
- RFID-модуль RC522
- Telegram-бот (созданный через `@botfather`)
- Arduino IDE с установленными библиотеками:
  - `ESP8266WiFi`
  - `WiFiClientSecure`
  - `MFRC522`
  - `UniversalTelegramBot`
  - `EEPROM`
  - `ArduinoOTA`
  - `AsyncTelegram2`

## Как использовать
1. **Настройка Telegram-бота**:
   - Создайте бота с помощью Telegram `@botfather` и получите API-токен.
   - Установите ваши Wi-Fi учетные данные и токен бота в коде.

2. **Загрузка кода**:
   - Используйте Arduino IDE для компиляции и загрузки кода на ваш ESP8266.

3. **Подключение оборудования**:
   - Подключите модуль RC522 RFID к микроконтроллеру ESP8266 по следующей схеме:
     - SDA -> GPIO2
     - RST -> GPIO15

4. **Сканирование карт**:
   - После включения устройства можно начать сканировать RFID-карты. UID карты будет отправлен в чат Telegram-бота.

5. **Обновление прошивки**:
   - Используйте функцию OTA для обновления прошивки по воздуху без повторного подключения устройства.


## Пример вывода
1. Подключение к Wi-Fi
```
Подключение к Wi-Fi...
........
Wi-Fi подключён
IP адрес: 192.168.1.100
```
2. Инициализация Telegram-бота
```
Telegram бот инициализирован.
```
3. Сканирование новой карты
```
Обнаружена новая карта.
UID карты: 04 7A 86 B2
UID сохранён в EEPROM.
Сообщение отправлено в Telegram: "Новая карта с UID: 04 7A 86 B2"
```
4. Повторное сканирование уже существующей карты
```
Карта уже существует в системе.
Сообщение отправлено в Telegram: "Карта уже сохранена в системе."
```
5. OTA Обновление
```
Начало OTA обновления: флеш-память
Прогресс: 45%
OTA обновление завершено успешно.
```
6. Переподключение к Wi-Fi при потере соединения
```
Wi-Fi отключён. Попытка переподключения...
........
Wi-Fi переподключён
```
