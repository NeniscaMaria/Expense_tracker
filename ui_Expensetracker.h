/********************************************************************************
** Form generated from reading UI file 'Expensetracker.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPENSETRACKER_H
#define UI_EXPENSETRACKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExpensetrackerClass
{
public:
    QAction *actionViewHelp;
    QAction *actionExport;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *meniuTabWidget;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QDateEdit *dateEditTransfer;
    QSpacerItem *horizontalSpacer;
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QTabWidget *optionsTabWidget;
    QWidget *dailyTab;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QLabel *dailyIncomeLabel;
    QLabel *dailyExpensesLabel;
    QLabel *totalLabel;
    QListWidget *dailyList;
    QWidget *weeklyTab;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *incomeLabelWeekly;
    QLabel *ExpensesLabelWeekly;
    QLabel *totalLabelWeekly;
    QListWidget *weeklyList;
    QWidget *monthlyTab;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *incomeLabelMonthly;
    QLabel *ExpensesLabelMonthly;
    QLabel *totalLabelMonthly;
    QListWidget *monthlyList;
    QWidget *yearlyTab;
    QVBoxLayout *verticalLayout_6;
    QCalendarWidget *calendarWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *addButtonDaily;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *expensesCheckBox;
    QCheckBox *incomeCheckBox;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QDateEdit *dateEditStatus;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *comboBoxStatus;
    QTabWidget *statusTabWidget;
    QWidget *incomeTab;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *incomeExtraButtonsLayout;
    QWidget *ExpensesTab;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *expensesExtraButtonsLayout;
    QMenuBar *menuBar;
    QMenu *menuSettingd;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ExpensetrackerClass)
    {
        if (ExpensetrackerClass->objectName().isEmpty())
            ExpensetrackerClass->setObjectName(QString::fromUtf8("ExpensetrackerClass"));
        ExpensetrackerClass->resize(711, 535);
        ExpensetrackerClass->setUnifiedTitleAndToolBarOnMac(true);
        actionViewHelp = new QAction(ExpensetrackerClass);
        actionViewHelp->setObjectName(QString::fromUtf8("actionViewHelp"));
        actionExport = new QAction(ExpensetrackerClass);
        actionExport->setObjectName(QString::fromUtf8("actionExport"));
        centralWidget = new QWidget(ExpensetrackerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        meniuTabWidget = new QTabWidget(centralWidget);
        meniuTabWidget->setObjectName(QString::fromUtf8("meniuTabWidget"));
        meniuTabWidget->setTabPosition(QTabWidget::South);
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_2 = new QVBoxLayout(tab_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        dateEditTransfer = new QDateEdit(tab_3);
        dateEditTransfer->setObjectName(QString::fromUtf8("dateEditTransfer"));
        dateEditTransfer->setDateTime(QDateTime(QDate(2019, 9, 3), QTime(0, 0, 0)));
        dateEditTransfer->setMaximumDateTime(QDateTime(QDate(2500, 12, 31), QTime(23, 59, 59)));
        dateEditTransfer->setMinimumDateTime(QDateTime(QDate(2005, 9, 14), QTime(0, 0, 0)));
        dateEditTransfer->setCalendarPopup(true);

        horizontalLayout_4->addWidget(dateEditTransfer);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        searchLineEdit = new QLineEdit(tab_3);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));
        searchLineEdit->setClearButtonEnabled(true);

        horizontalLayout_4->addWidget(searchLineEdit);

        searchButton = new QPushButton(tab_3);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));

        horizontalLayout_4->addWidget(searchButton);


        verticalLayout_2->addLayout(horizontalLayout_4);

        optionsTabWidget = new QTabWidget(tab_3);
        optionsTabWidget->setObjectName(QString::fromUtf8("optionsTabWidget"));
        optionsTabWidget->setToolTipDuration(-1);
        optionsTabWidget->setTabShape(QTabWidget::Triangular);
        optionsTabWidget->setElideMode(Qt::ElideNone);
        optionsTabWidget->setTabsClosable(false);
        optionsTabWidget->setMovable(true);
        optionsTabWidget->setTabBarAutoHide(true);
        dailyTab = new QWidget();
        dailyTab->setObjectName(QString::fromUtf8("dailyTab"));
        verticalLayout_3 = new QVBoxLayout(dailyTab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label = new QLabel(dailyTab);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_6->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        dailyIncomeLabel = new QLabel(dailyTab);
        dailyIncomeLabel->setObjectName(QString::fromUtf8("dailyIncomeLabel"));

        horizontalLayout_6->addWidget(dailyIncomeLabel);

        dailyExpensesLabel = new QLabel(dailyTab);
        dailyExpensesLabel->setObjectName(QString::fromUtf8("dailyExpensesLabel"));

        horizontalLayout_6->addWidget(dailyExpensesLabel);

        totalLabel = new QLabel(dailyTab);
        totalLabel->setObjectName(QString::fromUtf8("totalLabel"));

        horizontalLayout_6->addWidget(totalLabel);


        verticalLayout_3->addLayout(horizontalLayout_6);

        dailyList = new QListWidget(dailyTab);
        dailyList->setObjectName(QString::fromUtf8("dailyList"));

        verticalLayout_3->addWidget(dailyList);

        optionsTabWidget->addTab(dailyTab, QString());
        weeklyTab = new QWidget();
        weeklyTab->setObjectName(QString::fromUtf8("weeklyTab"));
        verticalLayout_4 = new QVBoxLayout(weeklyTab);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        incomeLabelWeekly = new QLabel(weeklyTab);
        incomeLabelWeekly->setObjectName(QString::fromUtf8("incomeLabelWeekly"));

        horizontalLayout_2->addWidget(incomeLabelWeekly);

        ExpensesLabelWeekly = new QLabel(weeklyTab);
        ExpensesLabelWeekly->setObjectName(QString::fromUtf8("ExpensesLabelWeekly"));

        horizontalLayout_2->addWidget(ExpensesLabelWeekly);

        totalLabelWeekly = new QLabel(weeklyTab);
        totalLabelWeekly->setObjectName(QString::fromUtf8("totalLabelWeekly"));

        horizontalLayout_2->addWidget(totalLabelWeekly);


        verticalLayout_4->addLayout(horizontalLayout_2);

        weeklyList = new QListWidget(weeklyTab);
        weeklyList->setObjectName(QString::fromUtf8("weeklyList"));

        verticalLayout_4->addWidget(weeklyList);

        optionsTabWidget->addTab(weeklyTab, QString());
        monthlyTab = new QWidget();
        monthlyTab->setObjectName(QString::fromUtf8("monthlyTab"));
        verticalLayout_5 = new QVBoxLayout(monthlyTab);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        incomeLabelMonthly = new QLabel(monthlyTab);
        incomeLabelMonthly->setObjectName(QString::fromUtf8("incomeLabelMonthly"));

        horizontalLayout_3->addWidget(incomeLabelMonthly);

        ExpensesLabelMonthly = new QLabel(monthlyTab);
        ExpensesLabelMonthly->setObjectName(QString::fromUtf8("ExpensesLabelMonthly"));

        horizontalLayout_3->addWidget(ExpensesLabelMonthly);

        totalLabelMonthly = new QLabel(monthlyTab);
        totalLabelMonthly->setObjectName(QString::fromUtf8("totalLabelMonthly"));

        horizontalLayout_3->addWidget(totalLabelMonthly);


        verticalLayout_5->addLayout(horizontalLayout_3);

        monthlyList = new QListWidget(monthlyTab);
        monthlyList->setObjectName(QString::fromUtf8("monthlyList"));

        verticalLayout_5->addWidget(monthlyList);

        optionsTabWidget->addTab(monthlyTab, QString());
        yearlyTab = new QWidget();
        yearlyTab->setObjectName(QString::fromUtf8("yearlyTab"));
        verticalLayout_6 = new QVBoxLayout(yearlyTab);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        calendarWidget = new QCalendarWidget(yearlyTab);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));

        verticalLayout_6->addWidget(calendarWidget);

        optionsTabWidget->addTab(yearlyTab, QString());

        verticalLayout_2->addWidget(optionsTabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addButtonDaily = new QPushButton(tab_3);
        addButtonDaily->setObjectName(QString::fromUtf8("addButtonDaily"));

        horizontalLayout->addWidget(addButtonDaily);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        expensesCheckBox = new QCheckBox(tab_3);
        expensesCheckBox->setObjectName(QString::fromUtf8("expensesCheckBox"));

        horizontalLayout->addWidget(expensesCheckBox);

        incomeCheckBox = new QCheckBox(tab_3);
        incomeCheckBox->setObjectName(QString::fromUtf8("incomeCheckBox"));

        horizontalLayout->addWidget(incomeCheckBox);


        verticalLayout_2->addLayout(horizontalLayout);

        meniuTabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_7 = new QVBoxLayout(tab_4);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        dateEditStatus = new QDateEdit(tab_4);
        dateEditStatus->setObjectName(QString::fromUtf8("dateEditStatus"));

        horizontalLayout_5->addWidget(dateEditStatus);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        comboBoxStatus = new QComboBox(tab_4);
        comboBoxStatus->addItem(QString());
        comboBoxStatus->addItem(QString());
        comboBoxStatus->addItem(QString());
        comboBoxStatus->setObjectName(QString::fromUtf8("comboBoxStatus"));

        horizontalLayout_5->addWidget(comboBoxStatus);


        verticalLayout_7->addLayout(horizontalLayout_5);

        statusTabWidget = new QTabWidget(tab_4);
        statusTabWidget->setObjectName(QString::fromUtf8("statusTabWidget"));
        incomeTab = new QWidget();
        incomeTab->setObjectName(QString::fromUtf8("incomeTab"));
        verticalLayout_8 = new QVBoxLayout(incomeTab);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        incomeExtraButtonsLayout = new QVBoxLayout();
        incomeExtraButtonsLayout->setSpacing(6);
        incomeExtraButtonsLayout->setObjectName(QString::fromUtf8("incomeExtraButtonsLayout"));

        verticalLayout_8->addLayout(incomeExtraButtonsLayout);

        statusTabWidget->addTab(incomeTab, QString());
        ExpensesTab = new QWidget();
        ExpensesTab->setObjectName(QString::fromUtf8("ExpensesTab"));
        verticalLayout_9 = new QVBoxLayout(ExpensesTab);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        expensesExtraButtonsLayout = new QVBoxLayout();
        expensesExtraButtonsLayout->setSpacing(6);
        expensesExtraButtonsLayout->setObjectName(QString::fromUtf8("expensesExtraButtonsLayout"));

        verticalLayout_9->addLayout(expensesExtraButtonsLayout);

        statusTabWidget->addTab(ExpensesTab, QString());

        verticalLayout_7->addWidget(statusTabWidget);

        meniuTabWidget->addTab(tab_4, QString());

        verticalLayout->addWidget(meniuTabWidget);

        ExpensetrackerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ExpensetrackerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 711, 21));
        menuSettingd = new QMenu(menuBar);
        menuSettingd->setObjectName(QString::fromUtf8("menuSettingd"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        ExpensetrackerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ExpensetrackerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ExpensetrackerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ExpensetrackerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ExpensetrackerClass->setStatusBar(statusBar);

        menuBar->addAction(menuSettingd->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuSettingd->addAction(actionExport);
        menuHelp->addAction(actionViewHelp);

        retranslateUi(ExpensetrackerClass);

        meniuTabWidget->setCurrentIndex(0);
        optionsTabWidget->setCurrentIndex(0);
        statusTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ExpensetrackerClass);
    } // setupUi

    void retranslateUi(QMainWindow *ExpensetrackerClass)
    {
        ExpensetrackerClass->setWindowTitle(QApplication::translate("ExpensetrackerClass", "Expensetracker", nullptr));
        actionViewHelp->setText(QApplication::translate("ExpensetrackerClass", "View help", nullptr));
        actionExport->setText(QApplication::translate("ExpensetrackerClass", "Export", nullptr));
        label_2->setText(QApplication::translate("ExpensetrackerClass", "Selected date:", nullptr));
        dateEditTransfer->setDisplayFormat(QApplication::translate("ExpensetrackerClass", "dd.MM.yyyy", nullptr));
        searchButton->setText(QApplication::translate("ExpensetrackerClass", "Search", nullptr));
        label->setText(QApplication::translate("ExpensetrackerClass", "Transactions:", nullptr));
        dailyIncomeLabel->setText(QApplication::translate("ExpensetrackerClass", "Daily income", nullptr));
        dailyExpensesLabel->setText(QApplication::translate("ExpensetrackerClass", "Daily Expenses", nullptr));
        totalLabel->setText(QApplication::translate("ExpensetrackerClass", "Total", nullptr));
        optionsTabWidget->setTabText(optionsTabWidget->indexOf(dailyTab), QApplication::translate("ExpensetrackerClass", "Daily", nullptr));
        incomeLabelWeekly->setText(QApplication::translate("ExpensetrackerClass", "Income", nullptr));
        ExpensesLabelWeekly->setText(QApplication::translate("ExpensetrackerClass", "Expenses", nullptr));
        totalLabelWeekly->setText(QApplication::translate("ExpensetrackerClass", "Total", nullptr));
        optionsTabWidget->setTabText(optionsTabWidget->indexOf(weeklyTab), QApplication::translate("ExpensetrackerClass", "Weekly", nullptr));
        incomeLabelMonthly->setText(QApplication::translate("ExpensetrackerClass", "Income", nullptr));
        ExpensesLabelMonthly->setText(QApplication::translate("ExpensetrackerClass", "Expenses", nullptr));
        totalLabelMonthly->setText(QApplication::translate("ExpensetrackerClass", "Total", nullptr));
        optionsTabWidget->setTabText(optionsTabWidget->indexOf(monthlyTab), QApplication::translate("ExpensetrackerClass", "Monthly", nullptr));
        optionsTabWidget->setTabText(optionsTabWidget->indexOf(yearlyTab), QApplication::translate("ExpensetrackerClass", "Calendar", nullptr));
        addButtonDaily->setText(QApplication::translate("ExpensetrackerClass", "Add new transfer", nullptr));
        expensesCheckBox->setText(QApplication::translate("ExpensetrackerClass", "Display only expanses", nullptr));
        incomeCheckBox->setText(QApplication::translate("ExpensetrackerClass", "Display only income", nullptr));
        meniuTabWidget->setTabText(meniuTabWidget->indexOf(tab_3), QApplication::translate("ExpensetrackerClass", "Transfer", nullptr));
        comboBoxStatus->setItemText(0, QApplication::translate("ExpensetrackerClass", "Weekly", nullptr));
        comboBoxStatus->setItemText(1, QApplication::translate("ExpensetrackerClass", "Monthly", nullptr));
        comboBoxStatus->setItemText(2, QApplication::translate("ExpensetrackerClass", "Periodically", nullptr));

        statusTabWidget->setTabText(statusTabWidget->indexOf(incomeTab), QApplication::translate("ExpensetrackerClass", "Income", nullptr));
        statusTabWidget->setTabText(statusTabWidget->indexOf(ExpensesTab), QApplication::translate("ExpensetrackerClass", "Expenses", nullptr));
        meniuTabWidget->setTabText(meniuTabWidget->indexOf(tab_4), QApplication::translate("ExpensetrackerClass", "Status", nullptr));
        menuSettingd->setTitle(QApplication::translate("ExpensetrackerClass", "More", nullptr));
        menuHelp->setTitle(QApplication::translate("ExpensetrackerClass", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExpensetrackerClass: public Ui_ExpensetrackerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPENSETRACKER_H
