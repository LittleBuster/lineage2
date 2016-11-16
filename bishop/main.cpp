/* Lineage2 auto bishop
 *
 * Copyright (C) 2016 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

#include "widget.h"
#include "app.h"
#include <memory>
#include <QApplication>

using namespace std;


int main(int argc, char *argv[])
{
    auto qapp = make_shared<QApplication>(argc, argv);
    auto mainWnd = make_shared<Widget>();
    auto app = make_shared<App>(mainWnd);

    app->start();
    return qapp->exec();
}
