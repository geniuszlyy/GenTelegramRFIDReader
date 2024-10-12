#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <MFRC522.h>
#include <EEPROM.h>
#include <ArduinoOTA.h>
#include <AsyncTelegram2.h>

// Конфигурация сети Wi-Fi и Telegram-бота
const char* wifi_ssid = "1234";        
const char* wifi_password = "6707870a"; 
const char* TELEGRAM_BOT_TOKEN = "token_your_bot"; 

// Аппаратные пины RFID-модуля
#define RFID_RST_PIN 5   
#define RFID_SS_PIN  4   

// Размер EEPROM для хранения UID
#define EEPROM_SIZE 512

// Объявление глобальных объектов
WiFiClientSecure wifi_client;
AsyncTelegram2 async_bot(wifi_client);
MFRC522 rfid_reader(RFID_SS_PIN, RFID_RST_PIN);
void geniuszly() {
    Serial.println("GenTelegramRFIDReader by geniuszly");
}

// Инициализация системы
void setup() {
    Serial.begin(9600);
    SPI.begin();
    rfid_reader.PCD_Init();        // Инициализация RFID
    connect_to_wifi_async();       // Асинхронное подключение к Wi-Fi
    setup_ota();                   // Поддержка OTA обновлений
    setup_power_saving();          // Включение энергосбережения
    EEPROM.begin(EEPROM_SIZE);     // Инициализация EEPROM для сохранения UID карт
    geniuszly();                   // Вызов авторской функции для уникализации
}

void loop() {
    handle_telegram();   // Обработка сообщений Telegram
    handle_ota();        // Обработка OTA запросов
    check_for_new_card();// Проверка на наличие новой карты
}

// Асинхронное подключение к Wi-Fi
void connect_to_wifi_async() {
    WiFi.onEvent(WiFiEvent);
    WiFi.begin(wifi_ssid, wifi_password);
    Serial.println("Подключение к Wi-Fi...");
}

// Обработка событий Wi-Fi
void WiFiEvent(WiFiEvent_t event) {
    switch (event) {
        case SYSTEM_EVENT_STA_CONNECTED:
            Serial.println("Wi-Fi подключён.");
            geniuszly(); // Вызов функции уникализации при подключении
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            Serial.println("Wi-Fi отключён. Попытка переподключения...");
            connect_to_wifi_async();
            break;
    }
}

// Проверка на наличие новой карты и вывод UID
void check_for_new_card() {
    if (!rfid_reader.PICC_IsNewCardPresent()) {
        delay(50);
        return;
    }
    if (!rfid_reader.PICC_ReadCardSerial()) {
        delay(50);
        return;
    }
    process_card(rfid_reader.uid.uidByte, rfid_reader.uid.size);
}

// Обработка и вывод UID карты через Telegram и сохранение в EEPROM
void process_card(byte* uid, byte uid_size) {
    if (!card_exists(uid, uid_size)) {
        save_card_uid(uid, uid_size);
        String uid_string = "Новая карта с UID: ";
        for (byte i = 0; i < uid_size; i++) {
            uid_string += (uid[i] < 0x10 ? " 0" : " ") + String(uid[i], HEX);
        }
        send_to_telegram(uid_string);
    } else {
        send_to_telegram("Карта уже сохранена в системе.");
    }
}

// Проверка, существует ли карта
bool card_exists(byte* uid, byte uid_size) {
    for (int address = 0; address < EEPROM_SIZE; address += uid_size) {
        bool found = true;
        for (int i = 0; i < uid_size; i++) {
            if (EEPROM.read(address + i) != uid[i]) {
                found = false;
                break;
            }
        }
        if (found) return true;
    }
    return false;
}

// Сохранение UID карты в EEPROM
void save_card_uid(byte* uid, byte uid_size) {
    int address = find_empty_eeprom_address();
    for (int i = 0; i < uid_size; i++) {
        EEPROM.write(address + i, uid[i]);
    }
    EEPROM.commit(); // Запись в EEPROM
    telegram_send_message("UID карты сохранён.");
}

// Поиск пустого адреса в EEPROM для записи
int find_empty_eeprom_address() {
    for (int address = 0; address < EEPROM_SIZE; address += 4) {
        if (EEPROM.read(address) == 255) {
            return address;
        }
    }
    return -1; // Нет свободного места
}

// Отправка сообщения в Telegram
void send_to_telegram(const String& message) {
    if (message != "") {
        async_bot.sendSimpleMessage(async_bot.messages[0].chat_id, message, "");
    }
}

// Инициализация OTA обновлений
void setup_ota() {
    ArduinoOTA.onStart([]() {
        String type = (ArduinoOTA.getCommand() == U_FLASH) ? "флеш-память" : "файловая система";
        Serial.println("Начало OTA обновления: " + type);
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("OTA обновление завершено.");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Прогресс: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Ошибка OTA: [%u] ", error);
    });
    ArduinoOTA.begin();
}

// Обработка OTA обновлений
void handle_ota() {
    ArduinoOTA.handle();
}

// Асинхронная обработка сообщений Telegram
void handle_telegram() {
    if (async_bot.getUpdates()) {
        String incoming_message = async_bot.messages[0].text;
        Serial.println("Сообщение: " + incoming_message);
    }
}

// Настройка энергосбережения
void setup_power_saving() {
    WiFi.setSleepMode(WIFI_LIGHT_SLEEP); // Включение режима энергосбережения
    Serial.println("Режим энергосбережения включён.");
}
