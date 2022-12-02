//
// Created by twak on 07/10/2019.
//

#ifndef RESPONSIVELAYOUT_H
#define RESPONSIVELAYOUT_H

#include "responsive_label.h"

#include <QtGui>
#include <QList>
#include <QLayout>

const int kSmallSpacing = 4;
const int kLargeSpacing = 8;
const int kAllWidgetsThresholdX = 432;
const int kAllWidgetsThresholdY = 432;
const int ktinyThreshold = 432;

class ResponsiveLayout : public QLayout {
public:
    ResponsiveLayout(): QLayout() {}
    ~ResponsiveLayout();

    // standard functions for a QLayout
    void setGeometry(const QRect &rect);

    void addItem(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const;
    int count() const;
    QLayoutItem *itemAt(int) const;
    QLayoutItem *takeAt(int);

private:
    int spacing;

    int headerSize;
    int leftBorderSize;
    int rightBorderSize;

    int bodyHeight;

    int optionsHeight;
    int searchHeight;
    int rowHeight;
    int adHeight;

    //width of the search button, will be used to keep sizes of other buttons in ratio
    int fixedChunkWidth;
    int homeLinkWidth;
    int basketWidth;
    int signInWidth;

    bool splitHeader;
    bool cutRows;

    int getBodyWidth(const QRect &r);
    int getAdsAndSearchesStartY();
    int getNavTabWidth(const QRect &r);

    bool drawHeader(const QRect &r, ResponsiveLabel *label);
    void drawBody(const QRect &r, ResponsiveLabel *label, int& adCount, int& searchResultCount);

    //start with this
    void fullSizeConfig();
    void thinLandscapeConfig();
    void thinPortraitConfig();
    QList<QLayoutItem*> list_;
};
#endif // RESPONSIVELAYOUT_H
