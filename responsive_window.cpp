//
// Created by twak on 14/10/2019.
//

#include "responsive_window.h"
#include "responsive_layout.h"
#include "screenshot.h"
#include <iostream>
#include <QApplication>


ResponsiveWindow::ResponsiveWindow() {

    setWindowTitle("2811: Coursework 1");
    setMinimumSize(320, 320);
    setMaximumSize(1280, 720);

    createWidgets();
}

void ResponsiveWindow::createWidgets() {

    ResponsiveLayout * rl = new ResponsiveLayout();

    // add all the widgets we need to demonstrate all layouts
    rl->addWidget(new ResponsiveLabel(kHomeLink));
    rl->addWidget(new ResponsiveLabel(kNavTabs));
    rl->addWidget(new ResponsiveLabel(kSignIn));
    rl->addWidget(new ResponsiveLabel(kShoppingBasket));

    //adverts must be added before searchResults for my code to display Ads first
    rl->addWidget(new ResponsiveLabel(kAdvert));
    rl->addWidget(new ResponsiveLabel(kAdvert));

    rl->addWidget(new ResponsiveLabel(kSearchResult));
    rl->addWidget(new ResponsiveLabel(kSearchResult));
    rl->addWidget(new ResponsiveLabel(kSearchResult));
    rl->addWidget(new ResponsiveLabel(kSearchResult));
    rl->addWidget(new ResponsiveLabel(kSearchResult));
    rl->addWidget(new ResponsiveLabel(kSearchResult));
    rl->addWidget(new ResponsiveLabel(kSearchResult));
    rl->addWidget(new ResponsiveLabel(kSearchResult));

    rl->addWidget(new ResponsiveLabel(kSearchBackward));
    rl->addWidget(new ResponsiveLabel(kSearchForward));
    rl->addWidget(new ResponsiveLabel(kSearchOptions));

    rl->addWidget(new ResponsiveLabel(kSearchText));
    rl->addWidget(new ResponsiveLabel(kSearchButton));


    setLayout(rl);
}


