#include <Mainwindow.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), camera("192.168.2.25", 37260) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

// Move Camera Up
void MainWindow::on_upButton_clicked() {
    camera.send_ptz_command("up", 0.5); // Adjust speed as needed
}

// Move Camera Down
void MainWindow::on_downButton_clicked() {
    camera.send_ptz_command("down", 0.5);
}

// Move Camera Left
void MainWindow::on_leftButton_clicked() {
    camera.send_ptz_command("left", 0.5);
}

// Move Camera Right
void MainWindow::on_rightButton_clicked() {
    camera.send_ptz_command("right", 0.5);
}

// Zoom In
void MainWindow::on_zoomInButton_clicked() {
    camera.send_ptz_command("zoom_in", 0.5);
}

// Zoom Out
void MainWindow::on_zoomOutButton_clicked() {
    camera.send_ptz_command("zoom_out", 0.5);
}
