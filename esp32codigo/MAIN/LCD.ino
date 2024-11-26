#include <LcdMenu.h>
#include <ItemCommand.h>
#include <ItemInput.h>
#include <ItemInputCharset.h>
#include <ItemSubMenu.h>
#include <MenuScreen.h>
#include <display/LiquidCrystal_I2CAdapter.h>
#include <renderer/CharacterDisplayRenderer.h>
#include <SimpleRotary.h>
#include <input/SimpleRotaryAdapter.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
LiquidCrystal_I2CAdapter lcdAdapter(&lcd);
CharacterDisplayRenderer renderer(&lcdAdapter, 20, 4);
LcdMenu menu(renderer);
SimpleRotary encoder(2, 3, 4);
SimpleRotaryAdapter rotaryInput(&menu, &encoder);


#include "WIFI.ino"
#include "SD.ino"
void colorsCallback(uint8_t pos);
extern String colors[];
String colors[] = {"Red", "Green", "Blue", "Orange", "Aqua", "Yellow", "Purple", "Pink"};
MENU_SCREEN(mainScreen, mainItems,
    ITEM_SUBMENU("SD", SDScreen),
    ITEM_SUBMENU("INFO", INFOScreen),
    ITEM_SUBMENU("WIFI", WIFIScreen),
    ITEM_SUBMENU("CONFIGURACIÓN", configScreen),
    );
    ///////////////////////////////////////////////////////////
    extern MenuScreen* SDCreen;
    extern MenuScreen* SDLocalesScreen;
    extern MenuScreen* SDServidorScreen;
MENU_SCREEN(SDScreen, SDItems,
    ITEM_SUBMENU("Locales", SDLocalesScreen),
    ITEM_SUBMENU("Servidor", SDServidorScreen),
    );
  MENU_SCREEN(SDLocalesScreen, SDLocalesItems,
    ITEM_BASIC("Archivos Locales"),
    ITEM_STRING_LIST("ARCH", colors, 8, colorsCallback)
    );
    MENU_SCREEN(SDServidorScreen, SDServidorItems,
    ITEM_BASIC("Archivos Servidor"),
    ITEM_STRING_LIST("ARCH", colors, 8, colorsCallback)
    );
    ////////////////////////////////////////////////////////////
    extern MenuScreen* INFOScreen;
MENU_SCREEN(INFOScreen, INFOItems,
    ITEM_BASIC("Actualemente conectado a :"),
    
    );
    ////////////////////////////////////////////////////////////
    extern MenuScreen* WIFIScreen;
MENU_SCREEN(WIFIScreen, WIFIItems,
    ITEM_BASIC("Actualemente conectado a:"),
    ITEM_STRING_LIST("ARCH", colors, 8, colorsCallback),
    );
    ////////////////////////////////////////////////////////////
    extern MenuScreen* configScreen;
MENU_SCREEN(configScreen, configItems,
    ITEM_BASIC("Todos los archivos:"),
    );
    
void colorsCallback(uint8_t pos) {
    // do something with the index
    Serial.println(colors[pos]);
}
