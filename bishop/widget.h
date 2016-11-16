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

#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <windows.h>


typedef struct {
    int x;
    int y;
    COLORREF hp;
} Man;

namespace Ui {
    class Widget;
}

class IWidget
{
public:
    virtual void show()=0;
    virtual void startHeal()=0;
    virtual void stopHeal()=0;
};


class Widget : public QWidget, public IWidget
{
    Q_OBJECT

private:
    Ui::Widget *ui;
    QTimer _healTmr;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void show();
    void startHeal();
    void stopHeal();

public slots:
     void updateTime();

private slots:
    void on_pushButton_clicked();   
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};

#endif
