/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the QtDataVisualization module.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#include "volumetric.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGroupBox>
#include <QtGui/QScreen>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Q3DScatter *graph = new Q3DScatter();
    QWidget *container = QWidget::createWindowContainer(graph);

    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 3, screenSize.height() / 3));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QWidget *widget = new QWidget();
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    QVBoxLayout *vLayout2 = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    hLayout->addLayout(vLayout2);

    widget->setWindowTitle(QStringLiteral("Volumetric object example - 3D terrain"));

    QCheckBox *sliceXCheckBox = new QCheckBox(widget);
    sliceXCheckBox->setText(QStringLiteral("Slice volume on X axis"));
    sliceXCheckBox->setChecked(false);
    QCheckBox *sliceYCheckBox = new QCheckBox(widget);
    sliceYCheckBox->setText(QStringLiteral("Slice volume on Y axis"));
    sliceYCheckBox->setChecked(false);
    QCheckBox *sliceZCheckBox = new QCheckBox(widget);
    sliceZCheckBox->setText(QStringLiteral("Slice volume on Z axis"));
    sliceZCheckBox->setChecked(false);

    QSlider *sliceXSlider = new QSlider(Qt::Horizontal, widget);
    sliceXSlider->setMinimum(0);
    sliceXSlider->setMaximum(1024);
    sliceXSlider->setValue(512);
    sliceXSlider->setEnabled(true);
    QSlider *sliceYSlider = new QSlider(Qt::Horizontal, widget);
    sliceYSlider->setMinimum(0);
    sliceYSlider->setMaximum(1024);
    sliceYSlider->setValue(512);
    sliceYSlider->setEnabled(true);
    QSlider *sliceZSlider = new QSlider(Qt::Horizontal, widget);
    sliceZSlider->setMinimum(0);
    sliceZSlider->setMaximum(1024);
    sliceZSlider->setValue(512);
    sliceZSlider->setEnabled(true);

    QCheckBox *fpsCheckBox = new QCheckBox(widget);
    fpsCheckBox->setText(QStringLiteral("Show FPS"));
    fpsCheckBox->setChecked(false);
    QLabel *fpsLabel = new QLabel(QStringLiteral(""), widget);

    QGroupBox *textureDetailGroupBox = new QGroupBox(QStringLiteral("Texture detail"));

    QRadioButton *lowDetailRB = new QRadioButton(widget);
    lowDetailRB->setText(QStringLiteral("Low (128x64x128)"));
    lowDetailRB->setChecked(true);

    QRadioButton *mediumDetailRB = new QRadioButton(widget);
    mediumDetailRB->setText(QStringLiteral("Generating..."));
    mediumDetailRB->setChecked(false);
    mediumDetailRB->setEnabled(false);

    QRadioButton *highDetailRB = new QRadioButton(widget);
    highDetailRB->setText(QStringLiteral("Generating..."));
    highDetailRB->setChecked(false);
    highDetailRB->setEnabled(false);

    QVBoxLayout *textureDetailVBox = new QVBoxLayout;
    textureDetailVBox->addWidget(lowDetailRB);
    textureDetailVBox->addWidget(mediumDetailRB);
    textureDetailVBox->addWidget(highDetailRB);
    textureDetailGroupBox->setLayout(textureDetailVBox);

    QCheckBox *colorTableCheckBox = new QCheckBox(widget);
    colorTableCheckBox->setText(QStringLiteral("Alternate color table"));
    colorTableCheckBox->setChecked(false);

    QLabel *sliceImageXLabel = new QLabel(widget);
    QLabel *sliceImageYLabel = new QLabel(widget);
    QLabel *sliceImageZLabel = new QLabel(widget);
    sliceImageXLabel->setMinimumSize(QSize(200, 100));
    sliceImageYLabel->setMinimumSize(QSize(200, 200));
    sliceImageZLabel->setMinimumSize(QSize(200, 100));
    sliceImageXLabel->setMaximumSize(QSize(200, 100));
    sliceImageYLabel->setMaximumSize(QSize(200, 200));
    sliceImageZLabel->setMaximumSize(QSize(200, 100));
    sliceImageXLabel->setFrameShape(QFrame::Box);
    sliceImageYLabel->setFrameShape(QFrame::Box);
    sliceImageZLabel->setFrameShape(QFrame::Box);
    sliceImageXLabel->setScaledContents(true);
    sliceImageYLabel->setScaledContents(true);
    sliceImageZLabel->setScaledContents(true);

    QSlider *alphaMultiplierSlider = new QSlider(Qt::Horizontal, widget);
    alphaMultiplierSlider->setMinimum(0);
    alphaMultiplierSlider->setMaximum(139);
    alphaMultiplierSlider->setValue(100);
    alphaMultiplierSlider->setEnabled(true);
    QLabel *alphaMultiplierLabel = new QLabel(QStringLiteral("Alpha multiplier: 1.0"));

    QCheckBox *preserveOpacityCheckBox = new QCheckBox(widget);
    preserveOpacityCheckBox->setText(QStringLiteral("Preserve opacity"));
    preserveOpacityCheckBox->setChecked(true);

    QCheckBox *transparentGroundCheckBox = new QCheckBox(widget);
    transparentGroundCheckBox->setText(QStringLiteral("Transparent ground"));
    transparentGroundCheckBox->setChecked(false);

    QCheckBox *useHighDefShaderCheckBox = new QCheckBox(widget);
    useHighDefShaderCheckBox->setText(QStringLiteral("Use HD shader"));
    useHighDefShaderCheckBox->setChecked(true);

    vLayout->addWidget(sliceXCheckBox);
    vLayout->addWidget(sliceXSlider);
    vLayout->addWidget(sliceImageXLabel);
    vLayout->addWidget(sliceYCheckBox);
    vLayout->addWidget(sliceYSlider);
    vLayout->addWidget(sliceImageYLabel);
    vLayout->addWidget(sliceZCheckBox);
    vLayout->addWidget(sliceZSlider);
    vLayout->addWidget(sliceImageZLabel, 1, Qt::AlignTop);
    vLayout2->addWidget(fpsCheckBox);
    vLayout2->addWidget(fpsLabel);
    vLayout2->addWidget(textureDetailGroupBox);
    vLayout2->addWidget(colorTableCheckBox);
    vLayout2->addWidget(alphaMultiplierLabel);
    vLayout2->addWidget(alphaMultiplierSlider);
    vLayout2->addWidget(preserveOpacityCheckBox);
    vLayout2->addWidget(transparentGroundCheckBox);
    vLayout2->addWidget(useHighDefShaderCheckBox, 1, Qt::AlignTop);

    VolumetricModifier *modifier = new VolumetricModifier(graph);
    modifier->setFpsLabel(fpsLabel);
    modifier->setMediumDetailRB(mediumDetailRB);
    modifier->setHighDetailRB(highDetailRB);
    modifier->setSliceSliders(sliceXSlider, sliceYSlider, sliceZSlider);
    modifier->setSliceLabels(sliceImageXLabel, sliceImageYLabel, sliceImageZLabel);
    modifier->setAlphaMultiplierLabel(alphaMultiplierLabel);
    modifier->setTransparentGround(transparentGroundCheckBox->isChecked());

    QObject::connect(fpsCheckBox, &QCheckBox::stateChanged, modifier,
                     &VolumetricModifier::setFpsMeasurement);
    QObject::connect(sliceXCheckBox, &QCheckBox::stateChanged, modifier,
                     &VolumetricModifier::sliceX);
    QObject::connect(sliceYCheckBox, &QCheckBox::stateChanged, modifier,
                     &VolumetricModifier::sliceY);
    QObject::connect(sliceZCheckBox, &QCheckBox::stateChanged, modifier,
                     &VolumetricModifier::sliceZ);
    QObject::connect(sliceXSlider, &QSlider::valueChanged, modifier,
                     &VolumetricModifier::adjustSliceX);
    QObject::connect(sliceYSlider, &QSlider::valueChanged, modifier,
                     &VolumetricModifier::adjustSliceY);
    QObject::connect(sliceZSlider, &QSlider::valueChanged, modifier,
                     &VolumetricModifier::adjustSliceZ);
    QObject::connect(lowDetailRB, &QRadioButton::toggled, modifier,
                     &VolumetricModifier::toggleLowDetail);
    QObject::connect(mediumDetailRB, &QRadioButton::toggled, modifier,
                     &VolumetricModifier::toggleMediumDetail);
    QObject::connect(highDetailRB, &QRadioButton::toggled, modifier,
                     &VolumetricModifier::toggleHighDetail);
    QObject::connect(colorTableCheckBox, &QCheckBox::stateChanged, modifier,
                     &VolumetricModifier::changeColorTable);
    QObject::connect(preserveOpacityCheckBox, &QCheckBox::stateChanged, modifier,
                     &VolumetricModifier::setPreserveOpacity);
    QObject::connect(transparentGroundCheckBox, &QCheckBox::stateChanged, modifier,
                     &VolumetricModifier::setTransparentGround);
    QObject::connect(useHighDefShaderCheckBox, &QCheckBox::stateChanged, modifier,
                     &VolumetricModifier::setUseHighDefShader);
    QObject::connect(alphaMultiplierSlider, &QSlider::valueChanged, modifier,
                     &VolumetricModifier::adjustAlphaMultiplier);

    widget->show();
    return app.exec();
}