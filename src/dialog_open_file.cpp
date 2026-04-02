#include "./dialog_open_file.hpp"
#include <QtWidgets/qwidget.h>

OpenFileDialog::OpenFileDialog(QWidget *widget, QString path, QString ext) : QDialog(widget), path(path), ext(ext) {
    setWindowModality(Qt::WindowModality::NonModal);

    setAttribute(Qt::WA_DeleteOnClose); // Super important, it's what makes windows delete themselves.
    setAttribute(Qt::WA_QuitOnClose, false);

    auto vbox = new QVBoxLayout();
    auto buttonBox = new QDialogButtonBox(Qt::Vertical);

    auto okButton = new QPushButton("OK");

    vbox->addWidget(buttonBox);

    buttonBox->addButton(okButton, QDialogButtonBox::AcceptRole);

    setLayout(vbox);
}
