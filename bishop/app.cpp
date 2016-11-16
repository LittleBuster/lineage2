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

#include "app.h"
#include <QApplication>


App::App(const shared_ptr<IWidget> &mainWnd): _mainWnd(move(mainWnd))
{
}

int App::start()
{
    _mainWnd->show();
    return 0;
}
