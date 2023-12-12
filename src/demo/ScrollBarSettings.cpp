#include "ScrollBarSettings.hpp"

#include <QtMaterialWidgets/scrollbar.hpp>

#include <QColorDialog>
#include <QTextEdit>
#include <QVBoxLayout>

ScrollBarSettings::ScrollBarSettings(QWidget* parent)
    : QWidget(parent)
    , ui_(new Ui::ScrollBarSettings)
    , vScrollbar_(new MaterialScrollBar)
    , hScrollbar_(new MaterialScrollBar)
{
    QVBoxLayout* layout = new QVBoxLayout;
    setLayout(layout);

    QWidget* widget = new QWidget;
    layout->addWidget(widget);

    QWidget* canvas = new QWidget;
    canvas->setStyleSheet("QWidget { background: white; }");
    layout->addWidget(canvas);

    ui_->setupUi(widget);
    layout->setContentsMargins(20, 20, 20, 20);

    layout = new QVBoxLayout;
    canvas->setLayout(layout);

    QTextEdit* edit = new QTextEdit;
    edit->setText("<p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p><p>The distinction between the subjects of syntax and semantics has its origin in the study of natural languages.</p>");
    edit->setLineWrapMode(QTextEdit::NoWrap);
    edit->update();

    edit->setVerticalScrollBar(vScrollbar_);
    edit->setHorizontalScrollBar(hScrollbar_);

    //vScrollbar_->setHideOnMouseOut(false);

    //hScrollbar_->setHideOnMouseOut(false);
    hScrollbar_->setOrientation(Qt::Horizontal);

    layout->addWidget(edit);
    layout->setAlignment(edit, Qt::AlignHCenter);

    setupForm();
}

ScrollBarSettings::~ScrollBarSettings()
{
    delete ui_;
}

void ScrollBarSettings::setupForm()
{
}

void ScrollBarSettings::updateWidget()
{
}
