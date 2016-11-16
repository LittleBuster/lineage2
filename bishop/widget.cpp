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
#include "ui_widget.h"
#include <windows.h>
#include <QMessageBox>
#include <vector>

using namespace std;

IWidget *pMainWnd;

HHOOK hHook;

bool isFindWnd = true;
bool isFindPeople = false;
bool isRun = false;

HWND curWnd = NULL;
HDC desktop;
vector<Man> people;


int __stdcall KeyboardProc(int nCode, DWORD wParam, DWORD lParam)
{
    static bool KeyStroke;
    static KBDLLHOOKSTRUCT *p;

    if (nCode < 0)
        return (int)CallNextHookEx(NULL, nCode, wParam, lParam);

    KeyStroke = FALSE;
    if (nCode == HC_ACTION) {
        switch(wParam) {
            case WM_KEYDOWN: {
                p = (KBDLLHOOKSTRUCT *)lParam;

                // Escape pushed
                if ((p->vkCode == 27) && !isFindPeople && isRun) {
                    isRun = false;
                    pMainWnd->stopHeal();
                    Beep(2800, 500);
                    break;
                }

                // Escape pushed
                if ((p->vkCode == 27) && !isFindPeople && !isRun) {
                    isRun = true;
                    pMainWnd->startHeal();
                    Beep(3000, 500);
                    break;
                }

                // Escape pushed
                if ((p->vkCode == 27) && isFindPeople) {
                    isFindPeople = false;
                    Beep(2000, 500);
                    break;
                }

                // Ctrl pushed
                if ((p->vkCode == 162) && isFindPeople) {
                    POINT p;
                    Man man;
                    GetCursorPos(&p);
                    man.x = p.x;
                    man.y = p.y;
                    man.hp = GetPixel(desktop, man.x, man.y);

                    people.push_back(man);
                    Beep(1000, 200);
                    break;
                }

                // Ctrl pushed
                if ((p->vkCode == 162) && isFindWnd) {
                    char txt[1024];

                    curWnd = GetForegroundWindow();
                    isFindWnd = false;
                    isFindPeople = true;
                    GetWindowTextA(curWnd, txt, 1024);
                    desktop = GetDC(0);
                    pMainWnd->show();
                    QMessageBox::information(0, "Finded", QString("Окно найдено: ") + QString(txt), QMessageBox::Ok);
                }
                break;
            }
        }
    }
    if (KeyStroke)
        return 666;
    else
        return (int)CallNextHookEx(0, nCode, wParam, lParam);
}

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)&KeyboardProc, GetModuleHandle(NULL), 0);
    pMainWnd = this;
    connect(&_healTmr, SIGNAL(timeout()), this, SLOT(updateTime()));
}

Widget::~Widget()
{
    delete ui;
    UnhookWindowsHookEx(hHook);
}

void Widget::show()
{
    QWidget::show();
}

void Widget::startHeal()
{
    _healTmr.start(300);
}

void Widget::stopHeal()
{
    _healTmr.stop();
}

void Widget::on_pushButton_clicked()
{
    this->hide();
}

static void sendKey(size_t i)
{
    switch(i) {
        case 0: {
            SendMessage(curWnd, WM_KEYDOWN, VK_F1, 0);
            SendMessage(curWnd, WM_KEYUP, VK_F1, 0);
            break;
        }
        case 1: {
            SendMessage(curWnd, WM_KEYDOWN, VK_F2, 0);
            SendMessage(curWnd, WM_KEYUP, VK_F2, 0);
            break;
        }
        case 2: {
            SendMessage(curWnd, WM_KEYDOWN, VK_F3, 0);
            SendMessage(curWnd, WM_KEYUP, VK_F3, 0);
            break;
        }
        case 3: {
            SendMessage(curWnd, WM_KEYDOWN, VK_F4, 0);
            SendMessage(curWnd, WM_KEYUP, VK_F4, 0);
            break;
        }
        case 4: {
            SendMessage(curWnd, WM_KEYDOWN, VK_F5, 0);
            SendMessage(curWnd, WM_KEYUP, VK_F5, 0);
           break;
        }
    }
}

void Widget::updateTime()
{
    size_t i = 0;
    bool isHeal = false;

    for (const auto &man : people) {
        COLORREF curColor = GetPixel(desktop, man.x, man.y);
        if (curColor != man.hp) {
            sendKey(i);
            Sleep(100);
            isHeal = true;
        }
        i++;

    }
    if (!isHeal) {
        SendMessage(curWnd, WM_KEYDOWN, VK_F6, 0);
        SendMessage(curWnd, WM_KEYUP, VK_F6, 0);
    }
}

void Widget::on_pushButton_2_clicked()
{
    startHeal();
}

void Widget::on_pushButton_3_clicked()
{
    stopHeal();
}
