/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPlainTextEdit *areaColor;
    QLabel *problems;
    QPushButton *color;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *path;
    QPushButton *Browse1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *mode;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *outPath;
    QPushButton *Browse2;
    QPushButton *starp;
    QLineEdit *txtPath;
    QLabel *label_5;
    QPushButton *Browse3;
    QComboBox *fps;
    QLabel *label_6;
    QCustomPlot *LeftNoGap;
    QCustomPlot *RightNoGap;
    QCustomPlot *RightGap;
    QCustomPlot *LeftGap;
    QLabel *label_3;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QPushButton *Browse4;
    QLineEdit *plotPath;
    QPushButton *ploting;
    QLineEdit *fps3;
    QTextEdit *Information;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_32;
    QPlainTextEdit *color0;
    QPlainTextEdit *color1;
    QPlainTextEdit *color2;
    QPlainTextEdit *color3;
    QPlainTextEdit *color4;
    QPlainTextEdit *color5;
    QPlainTextEdit *color6;
    QPlainTextEdit *color7;
    QPlainTextEdit *color8;
    QPlainTextEdit *color9;
    QPlainTextEdit *color10;
    QPlainTextEdit *color11;
    QPlainTextEdit *color12;
    QPlainTextEdit *color13;
    QPlainTextEdit *color14;
    QPlainTextEdit *color15;
    QPlainTextEdit *color16;
    QPlainTextEdit *color17;
    QPlainTextEdit *color18;
    QPlainTextEdit *color19;
    QPushButton *PauseButton;
    QLabel *label_33;
    QLabel *label_34;
    QLabel *LeftRatio;
    QLabel *RightRatio;
    QLineEdit *dots;
    QLabel *label_35;
    QLabel *label_36;
    QLineEdit *tilt;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1468, 783);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        areaColor = new QPlainTextEdit(centralWidget);
        areaColor->setObjectName(QStringLiteral("areaColor"));
        areaColor->setEnabled(false);
        areaColor->setGeometry(QRect(640, 250, 51, 31));
        problems = new QLabel(centralWidget);
        problems->setObjectName(QStringLiteral("problems"));
        problems->setGeometry(QRect(720, 610, 241, 41));
        color = new QPushButton(centralWidget);
        color->setObjectName(QStringLiteral("color"));
        color->setGeometry(QRect(550, 250, 75, 23));
        QFont font;
        font.setPointSize(10);
        color->setFont(font);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(550, 20, 401, 211));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        path = new QLineEdit(layoutWidget);
        path->setObjectName(QStringLiteral("path"));
        path->setEnabled(false);

        horizontalLayout->addWidget(path);

        Browse1 = new QPushButton(layoutWidget);
        Browse1->setObjectName(QStringLiteral("Browse1"));
        Browse1->setFont(font);

        horizontalLayout->addWidget(Browse1);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        mode = new QComboBox(layoutWidget);
        mode->setObjectName(QStringLiteral("mode"));

        horizontalLayout_3->addWidget(mode);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        outPath = new QLineEdit(layoutWidget);
        outPath->setObjectName(QStringLiteral("outPath"));
        outPath->setEnabled(false);

        horizontalLayout_2->addWidget(outPath);

        Browse2 = new QPushButton(layoutWidget);
        Browse2->setObjectName(QStringLiteral("Browse2"));
        Browse2->setFont(font);

        horizontalLayout_2->addWidget(Browse2);


        verticalLayout->addLayout(horizontalLayout_2);

        starp = new QPushButton(centralWidget);
        starp->setObjectName(QStringLiteral("starp"));
        starp->setGeometry(QRect(680, 411, 75, 23));
        starp->setFont(font);
        txtPath = new QLineEdit(centralWidget);
        txtPath->setObjectName(QStringLiteral("txtPath"));
        txtPath->setEnabled(false);
        txtPath->setGeometry(QRect(588, 363, 281, 20));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(550, 350, 34, 46));
        Browse3 = new QPushButton(centralWidget);
        Browse3->setObjectName(QStringLiteral("Browse3"));
        Browse3->setGeometry(QRect(880, 361, 75, 23));
        fps = new QComboBox(centralWidget);
        fps->setObjectName(QStringLiteral("fps"));
        fps->setGeometry(QRect(898, 250, 51, 22));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(770, 240, 34, 46));
        LeftNoGap = new QCustomPlot(centralWidget);
        LeftNoGap->setObjectName(QStringLiteral("LeftNoGap"));
        LeftNoGap->setEnabled(true);
        LeftNoGap->setGeometry(QRect(190, 50, 341, 311));
        RightNoGap = new QCustomPlot(centralWidget);
        RightNoGap->setObjectName(QStringLiteral("RightNoGap"));
        RightNoGap->setGeometry(QRect(1000, 50, 341, 311));
        RightGap = new QCustomPlot(centralWidget);
        RightGap->setObjectName(QStringLiteral("RightGap"));
        RightGap->setGeometry(QRect(1000, 410, 341, 311));
        LeftGap = new QCustomPlot(centralWidget);
        LeftGap->setObjectName(QStringLiteral("LeftGap"));
        LeftGap->setGeometry(QRect(190, 410, 341, 311));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(190, 20, 181, 21));
        label_3->setTextFormat(Qt::PlainText);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(190, 380, 131, 16));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(1000, 20, 131, 16));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(1000, 380, 121, 16));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(550, 467, 34, 46));
        Browse4 = new QPushButton(centralWidget);
        Browse4->setObjectName(QStringLiteral("Browse4"));
        Browse4->setGeometry(QRect(880, 480, 75, 23));
        Browse4->setFont(font);
        plotPath = new QLineEdit(centralWidget);
        plotPath->setObjectName(QStringLiteral("plotPath"));
        plotPath->setEnabled(false);
        plotPath->setGeometry(QRect(590, 480, 281, 20));
        ploting = new QPushButton(centralWidget);
        ploting->setObjectName(QStringLiteral("ploting"));
        ploting->setGeometry(QRect(730, 530, 91, 23));
        ploting->setFont(font);
        fps3 = new QLineEdit(centralWidget);
        fps3->setObjectName(QStringLiteral("fps3"));
        fps3->setGeometry(QRect(800, 250, 81, 20));
        Information = new QTextEdit(centralWidget);
        Information->setObjectName(QStringLiteral("Information"));
        Information->setGeometry(QRect(570, 560, 381, 151));
        QFont font1;
        font1.setPointSize(11);
        Information->setFont(font1);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(70, 40, 21, 16));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(110, 40, 31, 16));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(70, 66, 21, 20));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(70, 90, 21, 16));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(70, 110, 21, 16));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(70, 130, 21, 16));
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(70, 150, 21, 16));
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(70, 170, 21, 16));
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(70, 190, 21, 16));
        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(70, 210, 21, 16));
        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(70, 230, 21, 16));
        label_22 = new QLabel(centralWidget);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(60, 250, 21, 16));
        label_23 = new QLabel(centralWidget);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(60, 270, 21, 16));
        label_24 = new QLabel(centralWidget);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(60, 290, 21, 16));
        label_25 = new QLabel(centralWidget);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(60, 310, 21, 16));
        label_26 = new QLabel(centralWidget);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(60, 330, 21, 16));
        label_27 = new QLabel(centralWidget);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(60, 350, 21, 16));
        label_28 = new QLabel(centralWidget);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(60, 370, 21, 16));
        label_29 = new QLabel(centralWidget);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(60, 390, 21, 16));
        label_30 = new QLabel(centralWidget);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(60, 410, 21, 16));
        label_31 = new QLabel(centralWidget);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(60, 430, 21, 16));
        label_32 = new QLabel(centralWidget);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(60, 450, 21, 16));
        color0 = new QPlainTextEdit(centralWidget);
        color0->setObjectName(QStringLiteral("color0"));
        color0->setEnabled(false);
        color0->setGeometry(QRect(90, 70, 51, 15));
        QFont font2;
        font2.setPointSize(6);
        color0->setFont(font2);
        color0->setAcceptDrops(true);
        color0->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color1 = new QPlainTextEdit(centralWidget);
        color1->setObjectName(QStringLiteral("color1"));
        color1->setEnabled(false);
        color1->setGeometry(QRect(90, 90, 51, 15));
        color1->setFont(font2);
        color1->setAcceptDrops(true);
        color1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color2 = new QPlainTextEdit(centralWidget);
        color2->setObjectName(QStringLiteral("color2"));
        color2->setEnabled(false);
        color2->setGeometry(QRect(90, 110, 51, 15));
        color2->setFont(font2);
        color2->setAcceptDrops(true);
        color2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color3 = new QPlainTextEdit(centralWidget);
        color3->setObjectName(QStringLiteral("color3"));
        color3->setEnabled(false);
        color3->setGeometry(QRect(90, 130, 51, 15));
        color3->setFont(font2);
        color3->setAcceptDrops(true);
        color3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color4 = new QPlainTextEdit(centralWidget);
        color4->setObjectName(QStringLiteral("color4"));
        color4->setEnabled(false);
        color4->setGeometry(QRect(90, 150, 51, 15));
        color4->setFont(font2);
        color4->setAcceptDrops(true);
        color4->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color5 = new QPlainTextEdit(centralWidget);
        color5->setObjectName(QStringLiteral("color5"));
        color5->setEnabled(false);
        color5->setGeometry(QRect(90, 170, 51, 15));
        color5->setFont(font2);
        color5->setAcceptDrops(true);
        color5->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color6 = new QPlainTextEdit(centralWidget);
        color6->setObjectName(QStringLiteral("color6"));
        color6->setEnabled(false);
        color6->setGeometry(QRect(90, 190, 51, 15));
        color6->setFont(font2);
        color6->setAcceptDrops(true);
        color6->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color7 = new QPlainTextEdit(centralWidget);
        color7->setObjectName(QStringLiteral("color7"));
        color7->setEnabled(false);
        color7->setGeometry(QRect(90, 210, 51, 15));
        color7->setFont(font2);
        color7->setAcceptDrops(true);
        color7->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color8 = new QPlainTextEdit(centralWidget);
        color8->setObjectName(QStringLiteral("color8"));
        color8->setEnabled(false);
        color8->setGeometry(QRect(90, 230, 51, 15));
        color8->setFont(font2);
        color8->setAcceptDrops(true);
        color8->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color9 = new QPlainTextEdit(centralWidget);
        color9->setObjectName(QStringLiteral("color9"));
        color9->setEnabled(false);
        color9->setGeometry(QRect(90, 250, 51, 15));
        color9->setFont(font2);
        color9->setAcceptDrops(true);
        color9->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color10 = new QPlainTextEdit(centralWidget);
        color10->setObjectName(QStringLiteral("color10"));
        color10->setEnabled(false);
        color10->setGeometry(QRect(90, 270, 51, 15));
        color10->setFont(font2);
        color10->setAcceptDrops(true);
        color10->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color11 = new QPlainTextEdit(centralWidget);
        color11->setObjectName(QStringLiteral("color11"));
        color11->setEnabled(false);
        color11->setGeometry(QRect(90, 290, 51, 15));
        color11->setFont(font2);
        color11->setAcceptDrops(true);
        color11->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color12 = new QPlainTextEdit(centralWidget);
        color12->setObjectName(QStringLiteral("color12"));
        color12->setEnabled(false);
        color12->setGeometry(QRect(90, 310, 51, 15));
        color12->setFont(font2);
        color12->setAcceptDrops(true);
        color12->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color13 = new QPlainTextEdit(centralWidget);
        color13->setObjectName(QStringLiteral("color13"));
        color13->setEnabled(false);
        color13->setGeometry(QRect(90, 330, 51, 15));
        color13->setFont(font2);
        color13->setAcceptDrops(true);
        color13->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color14 = new QPlainTextEdit(centralWidget);
        color14->setObjectName(QStringLiteral("color14"));
        color14->setEnabled(false);
        color14->setGeometry(QRect(90, 350, 51, 15));
        color14->setFont(font2);
        color14->setAcceptDrops(true);
        color14->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color15 = new QPlainTextEdit(centralWidget);
        color15->setObjectName(QStringLiteral("color15"));
        color15->setEnabled(false);
        color15->setGeometry(QRect(90, 370, 51, 15));
        color15->setFont(font2);
        color15->setAcceptDrops(true);
        color15->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color16 = new QPlainTextEdit(centralWidget);
        color16->setObjectName(QStringLiteral("color16"));
        color16->setEnabled(false);
        color16->setGeometry(QRect(90, 390, 51, 15));
        color16->setFont(font2);
        color16->setAcceptDrops(true);
        color16->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color17 = new QPlainTextEdit(centralWidget);
        color17->setObjectName(QStringLiteral("color17"));
        color17->setEnabled(false);
        color17->setGeometry(QRect(90, 410, 51, 15));
        color17->setFont(font2);
        color17->setAcceptDrops(true);
        color17->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color18 = new QPlainTextEdit(centralWidget);
        color18->setObjectName(QStringLiteral("color18"));
        color18->setEnabled(false);
        color18->setGeometry(QRect(90, 430, 51, 15));
        color18->setFont(font2);
        color18->setAcceptDrops(true);
        color18->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        color19 = new QPlainTextEdit(centralWidget);
        color19->setObjectName(QStringLiteral("color19"));
        color19->setEnabled(false);
        color19->setGeometry(QRect(90, 450, 51, 15));
        color19->setFont(font2);
        color19->setAcceptDrops(true);
        color19->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        PauseButton = new QPushButton(centralWidget);
        PauseButton->setObjectName(QStringLiteral("PauseButton"));
        PauseButton->setGeometry(QRect(780, 411, 75, 23));
        PauseButton->setFont(font);
        label_33 = new QLabel(centralWidget);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(0, 590, 61, 20));
        label_34 = new QLabel(centralWidget);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(0, 650, 61, 20));
        LeftRatio = new QLabel(centralWidget);
        LeftRatio->setObjectName(QStringLiteral("LeftRatio"));
        LeftRatio->setGeometry(QRect(80, 590, 61, 20));
        LeftRatio->setFont(font);
        RightRatio = new QLabel(centralWidget);
        RightRatio->setObjectName(QStringLiteral("RightRatio"));
        RightRatio->setGeometry(QRect(80, 650, 61, 20));
        RightRatio->setFont(font);
        dots = new QLineEdit(centralWidget);
        dots->setObjectName(QStringLiteral("dots"));
        dots->setGeometry(QRect(640, 310, 81, 20));
        label_35 = new QLabel(centralWidget);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setGeometry(QRect(550, 300, 81, 46));
        label_36 = new QLabel(centralWidget);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setGeometry(QRect(770, 300, 34, 46));
        tilt = new QLineEdit(centralWidget);
        tilt->setObjectName(QStringLiteral("tilt"));
        tilt->setGeometry(QRect(800, 310, 81, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1468, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        problems->setText(QString());
        color->setText(QApplication::translate("MainWindow", "Set Color", 0));
        label_2->setText(QApplication::translate("MainWindow", "Input", 0));
        Browse1->setText(QApplication::translate("MainWindow", "Browse", 0));
        label->setText(QApplication::translate("MainWindow", "Mode", 0));
        mode->clear();
        mode->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "No Windows", 0)
         << QApplication::translate("MainWindow", "Windows", 0)
        );
        label_4->setText(QApplication::translate("MainWindow", "Output", 0));
        Browse2->setText(QApplication::translate("MainWindow", "Browse", 0));
        starp->setText(QApplication::translate("MainWindow", "Process", 0));
        label_5->setText(QApplication::translate("MainWindow", "Gaps", 0));
        Browse3->setText(QApplication::translate("MainWindow", "Browse", 0));
        fps->clear();
        fps->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "420", 0)
         << QApplication::translate("MainWindow", "240", 0)
        );
        label_6->setText(QApplication::translate("MainWindow", "FPS", 0));
        label_3->setText(QApplication::translate("MainWindow", "Left No Gap (frames, mm)", 0));
        label_7->setText(QApplication::translate("MainWindow", "Left Gap(frames, mm)", 0));
        label_8->setText(QApplication::translate("MainWindow", "Right No Gap(frames, mm)", 0));
        label_9->setText(QApplication::translate("MainWindow", "Right Gap(frames, mm)", 0));
        label_10->setText(QApplication::translate("MainWindow", "Plots", 0));
        Browse4->setText(QApplication::translate("MainWindow", "Browse", 0));
        ploting->setText(QApplication::translate("MainWindow", "Recreate Plots", 0));
        label_11->setText(QApplication::translate("MainWindow", "Trial", 0));
        label_12->setText(QApplication::translate("MainWindow", "Color", 0));
        label_13->setText(QApplication::translate("MainWindow", "1", 0));
        label_14->setText(QApplication::translate("MainWindow", "2", 0));
        label_15->setText(QApplication::translate("MainWindow", "3", 0));
        label_16->setText(QApplication::translate("MainWindow", "4", 0));
        label_17->setText(QApplication::translate("MainWindow", "5", 0));
        label_18->setText(QApplication::translate("MainWindow", "6", 0));
        label_19->setText(QApplication::translate("MainWindow", "7", 0));
        label_20->setText(QApplication::translate("MainWindow", "8", 0));
        label_21->setText(QApplication::translate("MainWindow", "9", 0));
        label_22->setText(QApplication::translate("MainWindow", "10", 0));
        label_23->setText(QApplication::translate("MainWindow", "11", 0));
        label_24->setText(QApplication::translate("MainWindow", "12", 0));
        label_25->setText(QApplication::translate("MainWindow", "13", 0));
        label_26->setText(QApplication::translate("MainWindow", "14", 0));
        label_27->setText(QApplication::translate("MainWindow", "15", 0));
        label_28->setText(QApplication::translate("MainWindow", "16", 0));
        label_29->setText(QApplication::translate("MainWindow", "17", 0));
        label_30->setText(QApplication::translate("MainWindow", "18", 0));
        label_31->setText(QApplication::translate("MainWindow", "19", 0));
        label_32->setText(QApplication::translate("MainWindow", "20", 0));
        PauseButton->setText(QApplication::translate("MainWindow", "Pause", 0));
        label_33->setText(QApplication::translate("MainWindow", "Left Ratio", 0));
        label_34->setText(QApplication::translate("MainWindow", "Right Ratio", 0));
        LeftRatio->setText(QString());
        RightRatio->setText(QString());
        label_35->setText(QApplication::translate("MainWindow", "Size of dot (mml)", 0));
        label_36->setText(QApplication::translate("MainWindow", "Tilt %", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
