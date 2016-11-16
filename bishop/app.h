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

#ifndef __APP_H__
#define __APP_H__

#include "widget.h"
#include <memory>

using namespace std;


class App
{
private:
    const shared_ptr<IWidget> _mainWnd;

public:
    App(const shared_ptr<IWidget> &mainWnd);

    int start();
};


#endif
