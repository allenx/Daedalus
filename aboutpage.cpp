#include "aboutpage.h"
#include <QPixmap>
#include <QHBoxLayout>
#include <QLabel>

AboutPage::AboutPage(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background-color: black");
    QPixmap logo(aboutPagePic);
    QHBoxLayout *layout = new QHBoxLayout;
    QLabel *logoLabel = new QLabel;
    logoLabel->setFixedSize(1184, 882);
    logoLabel->setPixmap(logo.scaled(logoLabel->width(), logoLabel->height(), Qt::KeepAspectRatio));

    layout->addWidget(logoLabel);
    this->setLayout(layout);
}
