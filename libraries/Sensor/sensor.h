#ifndef SENS_h
#define SENS_h

#include "Arduino.h"
#include "text.h"
#include "settings.h"

#ifdef SENSOR_DHT_ENABLE

  #include "stDHT.h" // https://istarik.ru/blog/arduino/35.html

#endif

// Сюда добавляем типы датчиков
enum {
        DIGITAL_SENSOR,// датчик с одним цифровым выходом
        CHECK_DIGITAL_SENSOR,   // датчик с одним цифровым выходом, с проверкой от ложного срабатывания 10 сек
        ANALOG_SENSOR  // датчик с аналоговым выходом
//      ,DHT11,DHT21,DHT22       // датчики температуры и влажности DHT11, DHT21 или DHT22, объявлены в stDHT.h
};

class Sensor   // название класса
{
  public:

    // volatile означает указание компилятору не оптимизировать код её чтения,
    // поскольку её значение может изменяться внутри обработчика прерывания
    volatile uint8_t start_time;
    volatile uint8_t end_time;
    uint8_t count; // количество срабатываний
    uint8_t type;  // тип датчика
    uint8_t pin;   // пин
    bool level;    // высокий или низкий уровень пина
   
    Sensor(uint8_t _pin, uint8_t _type, char* sens_name, uint8_t pinLevel = LOW, uint8_t start_time_sec = 10, uint8_t alarm_val = ANALOG_SIGN_ALARM_VALUE);
    ~Sensor();
    
    uint16_t get_data();        // возвращает analogRead(pin)
    bool get_pin_state();       // возвращает state = digitalRead(pin). Если состояние изменилось, увеличивет счётчик срабатываний на 1.
    uint8_t get_count();        // возвращает счётчик срабатываний датчика.
    bool get_analog_count();
    void get_info(TEXT *str);   // возвращает строку с именем датчика и числом срабатываний
    void get_name_for_type(TEXT *str);  
    
  private:
    uint8_t alarm_value;    // значение срабатывания аналогового датчика
    bool prev_pin_state;    // предыдущее состояние пина
    const char *name;
#ifdef SENSOR_DHT_ENABLE
    DHT* dht; // датчик температуры и влажности   
#endif
};

#endif

