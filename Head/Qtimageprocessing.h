#pragma once
#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qtimageprocessing.h"

class Qtimageprocessing : public QMainWindow
{
    Q_OBJECT

public:
    Qtimageprocessing(QWidget* parent = nullptr);
    ~Qtimageprocessing();

private:
    Ui::QtimageprocessingClass ui;
};
