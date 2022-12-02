//
// Created by twak on 07/10/2019.
//

// Most of the functions in this file have been implemented by Fardin Fahim

#include "responsive_layout.h"
#include "responsive_label.h"
#include <iostream>

using namespace std;

void ResponsiveLayout::setGeometry(const QRect &r /* our layout should always fit inside r */ ) {
    QLayout::setGeometry(r);

    // decide which configuration to use based on window size
    fullSizeConfig();
    if(r.width() <=640)
        thinPortraitConfig();
    if(r.height() <= 400)
        thinLandscapeConfig();

    int adCount = 0;
    int searchResultCount = 0;
    // for all the Widgets added in ResponsiveWindow.cpp
    for (int i = 0; i < list_.size(); i++) {

        QLayoutItem *o = list_.at(i);

        try {
            // cast the widget to one of our responsive labels
            ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());

            if (label == NULL) // null: cast failed on pointer
                cout << "warning, unknown widget class in layout" << endl;
            else{
                if(drawHeader(r, label))
                    continue;
                else
                    drawBody(r, label, adCount, searchResultCount);
            }

        }
        catch (bad_cast) {
            // bad_case: cast failed on reference...
            cout << "warning, unknown widget class in layout" << endl;
        }
    }
}

// the three Config functions that follow will readjust the numbers for spacing, positioning and sizing based on
void ResponsiveLayout::fullSizeConfig(){
    cutRows = false;
    splitHeader = false;
    spacing = kLargeSpacing;

    headerSize = 90;

    rowHeight = 60;
    searchHeight = rowHeight;
    fixedChunkWidth = rowHeight;
    optionsHeight = rowHeight;
    adHeight = rowHeight;
    homeLinkWidth = 2 * fixedChunkWidth;
    basketWidth = 2 * fixedChunkWidth;
    signInWidth = 2 * fixedChunkWidth;
    leftBorderSize = 2 * fixedChunkWidth;
    rightBorderSize = leftBorderSize;
}

void ResponsiveLayout::thinLandscapeConfig()
{
    cutRows = true;
    headerSize = 75;
    rowHeight = 50;
    searchHeight = 2.0 / 3.0 * rowHeight;
    spacing = kSmallSpacing;
}

void ResponsiveLayout::thinPortraitConfig()
{
    splitHeader = true;
    spacing = kSmallSpacing;
    leftBorderSize = 0;
    rightBorderSize = 0;
    basketWidth = fixedChunkWidth;
    signInWidth = fixedChunkWidth;
    homeLinkWidth = 2 * fixedChunkWidth;
}

int ResponsiveLayout::getBodyWidth(const QRect &r)
{
    return r.width() - leftBorderSize - rightBorderSize - spacing;
}

int ResponsiveLayout::getAdsAndSearchesStartY()
{
    return spacing + headerSize + searchHeight * 2;
}

int ResponsiveLayout::getNavTabWidth(const QRect &r)
{
    return r.width() - (splitHeader ? 0 : homeLinkWidth + basketWidth + signInWidth) - spacing;
}

bool ResponsiveLayout::drawHeader(const QRect &r, ResponsiveLabel *label)
{
    if (label -> text() == kHomeLink){
        label -> setGeometry(spacing, spacing, homeLinkWidth - spacing,
                             (splitHeader ? 0.5 : 1 )*headerSize - spacing);
    }
    else if (label -> text() == kNavTabs ){ // headers go at the top
        label -> setGeometry(spacing + (splitHeader ? 0 : homeLinkWidth),
                             spacing + (splitHeader ? 0.5 * headerSize : 0),
                             getNavTabWidth(r) - spacing,
                             (splitHeader ? 0.5 : 1 ) * headerSize - spacing);
    }
    else if (label -> text() == kSignIn){
        label -> setGeometry(r.width() - basketWidth - signInWidth, spacing,
                             signInWidth - spacing,
                             (splitHeader ? 0.5 : 1) * headerSize - spacing);
    }
    else if (label -> text() == kShoppingBasket){
        label -> setGeometry(r.width() - basketWidth, spacing, basketWidth - spacing,
                             (splitHeader ? 0.5 : 1) * headerSize - spacing);
    }
    else{ // otherwise: disappear label by moving out of bounds
        label -> setGeometry (-1, -1, 0, 0);
        return false;
    }
    return true;
}

// arrange the size and position of the labels based on their type
void ResponsiveLayout::drawBody(const QRect &r, ResponsiveLabel *label, int& adCount, int& searchResultCount)
{
    if (label -> text() == kSearchBackward){
        label -> setGeometry(leftBorderSize + spacing, (spacing + headerSize),
                             fixedChunkWidth - spacing, searchHeight - spacing);
    }
    else if (label -> text() == kSearchForward){
        label->setGeometry(spacing + leftBorderSize + fixedChunkWidth,
                           (spacing + headerSize), fixedChunkWidth - spacing,
                           searchHeight - spacing);
    }
    else if (label -> text() == kSearchOptions){
        label -> setGeometry(spacing + leftBorderSize + 2 * fixedChunkWidth, spacing + headerSize,
                             getBodyWidth(r) - 2 * fixedChunkWidth - spacing, searchHeight-spacing);
    }
    else if (label -> text() == kSearchText){
        label -> setGeometry(spacing + leftBorderSize, spacing + headerSize + searchHeight,
                             getBodyWidth(r) - fixedChunkWidth - spacing, searchHeight - spacing);
    }
    else if (label -> text() == kSearchButton){
        label -> setGeometry(r.width() - rightBorderSize - fixedChunkWidth,
                             spacing + headerSize + searchHeight, fixedChunkWidth - spacing,
                             searchHeight - spacing);
    }
    else if (label -> text() == kAdvert){
        if(!cutRows){
             label -> setGeometry(leftBorderSize + spacing,
                                 getAdsAndSearchesStartY() + adCount * (adHeight),
                                 getBodyWidth(r) - spacing, adHeight - spacing);
            adCount++;
        }
        else
            label -> setGeometry(-1, -1, 0, 0);

    }
    else if (label -> text() == kSearchResult){
        if(getAdsAndSearchesStartY() + adCount * adHeight
           + (searchResultCount+1) * (rowHeight) > r.height())
            label->setGeometry(-1, -1, 0, 0);
        else
            label -> setGeometry(leftBorderSize + spacing,
                                 getAdsAndSearchesStartY() + adCount * adHeight
                                 + searchResultCount * (rowHeight),
                                 getBodyWidth(r) - spacing, rowHeight - spacing);
        searchResultCount++;
    }
    else // otherwise: disappear label by moving out of bounds
        label -> setGeometry (-1, -1, 0, 0 );
}

// following methods provide a trivial list-based implementation of the QLayout class
int ResponsiveLayout::count() const {
    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {
    list_.append(item);
}

QSize ResponsiveLayout::sizeHint() const {
    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {
    return QSize(320,320);
}

ResponsiveLayout::~ResponsiveLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
