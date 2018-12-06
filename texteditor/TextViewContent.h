#ifndef TextViewContent_H
#define TextViewContent_H

#include "SelectionData.h"
#include "TextDocument.h"
#include <SFML/Graphics.hpp>

class TextViewContent {
public:
    TextViewContent(const sf::String& fontPath);

    void setFontSize(int fontSize);
    void drawLines(sf::RenderTarget& window, TextDocument& document);

    void createNewSelection(int anclaLine, int anclaChar);
    void updateLastSelection(int lineN, int charN);

    void removeSelections();
    SelectionData::Selection getLastSelection();

    int getLineHeight();
    int getCharWidth();

    float getRightLimitPx();
    float getBottomLimitPx();

private:
    int fontSize;
    int lineHeight;
    int charWidth;

    float rightLimitPx;
    float bottomLimitPx;

    sf::Font font;

    sf::Color colorChar;
    sf::Color colorSelection;

    SelectionData selections;
};

#endif
