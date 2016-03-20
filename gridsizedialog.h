#ifndef GRIDSIZEDIALOG_H
#define GRIDSIZEDIALOG_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
class GridSizeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GridSizeDialog(QWidget *parent = 0);
    int gridSize() { return _spinBox->value(); }

private:
    QLabel *_label;
    QSpinBox *_spinBox;
    QPushButton *_okButton;
    QPushButton *_cancelButton;
};

#endif // GRIDSIZEDIALOG_H
