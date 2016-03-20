#include "gridsizedialog.h"
#include <QHBoxLayout>

GridSizeDialog::GridSizeDialog(QWidget *parent) :
    QDialog(parent)
{
    setFixedSize(200,80);
    setWindowTitle(trUtf8("Beállítások"));
    setModal(true);

    _label = new QLabel(trUtf8("Gombok száma: "));
    _spinBox = new QSpinBox();
    _spinBox->setRange(3, 7);
    _spinBox->setSingleStep(2);

    _okButton = new QPushButton(trUtf8("OK"));
    _okButton->setFixedSize(75, 23);
    _cancelButton = new QPushButton(trUtf8("Mégse"));
    _cancelButton->setFixedSize(75, 23);

    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    QHBoxLayout *upperLayout = new QHBoxLayout();
    upperLayout->addWidget(_label);
    upperLayout->addWidget(_spinBox);

    QHBoxLayout *lowerLayout = new QHBoxLayout();
    lowerLayout->addWidget(_okButton);
    lowerLayout->addWidget(_cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(lowerLayout);

    setLayout(mainLayout);
}
