#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_Mainwindow.h"  // Include the UI header
#include "soapH.h"  // Include GSoap headers
#include "sdk.h"    // SIYI SDK

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow();

private slots:
    void on_up_clicked();  // PTZ Up
    void on_down_clicked(); // PTZ Down
    void on_left_clicked(); // PTZ Left
    void on_right_clicked(); // PTZ Right
    void on_zoomIn_clicked(); // Zoom In
    void on_zoomOut_clicked(); // Zoom Out

private:
    Ui::MainWindow *ui;
    SIYI_SDK camera;  
};

#endif // MAINWINDOW_H
