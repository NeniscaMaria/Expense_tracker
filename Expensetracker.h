#pragma once

#include <QtWidgets/QMainWindow>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QCompleter>
#include <QFormLayout>
#include "ui_Expensetracker.h"
#include "repository.h"
#include <QtCharts/QPieSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QCategoryAxis>
QT_CHARTS_USE_NAMESPACE
class Expensetracker : public QMainWindow
{
	Q_OBJECT

public:
	Expensetracker(Repository* transfersFromUser, QWidget *parent = Q_NULLPTR);

private:
	int tabIndex;
	bool chartPresentIncome;
	bool chartPresentExpense;
	std::vector<QColor> colorsForPieCharts;
	QCompleter* searchCompleter;
	QListWidget* searchResultsList;
	QWidget* resultsWindow;
	QVBoxLayout* resultsWindowLayout;

	////charts
	std::map<std::string, int> statistics;
	std::vector<QPieSlice*> slices;
	QChart* chartIncome;
	QChartView* chartViewIncome;
	QPieSeries* seriesIncome;
	QLabel* additionalInformation;
	QListWidget* categoriesList;
	bool chartDisplayed;

	//additional information meniu
	QWidget* additionalInformationWindow;
	QListWidget* additionalInformationList;
	QVBoxLayout* additionalInformationLayout;
	QLineSeries* additionalInformationSeries;
	QChart* additionalInformationChart;
	QChartView* aditionalInformationChartView;
	QCategoryAxis *axisX;
	QCategoryAxis *axisY;
	std::map<QDate, float> stats;

	//displaying pressed transfers
	QWidget* pressedTransfersWindow;
	QVBoxLayout* pressedTransfersLayout;
	QListWidget* pressedTrasnsfersList;

	//periodical meniu
	QWidget* periodicalMeniuWindow;
	QFormLayout* periodicalLayout;
	QLabel* informativeText;
	QLabel* startDateLabel;
	QLabel* endDateLabel;
	QDateEdit* startDateEdit;
	QDateEdit* endDateEdit;
	QPushButton* showButton;

	//add meniu window
	QWidget* addWindow;
	QLabel* dateLabelAddMeniu;
	QLabel* typeLabelAddMeniu;
	QLabel* methodOfPaymentLabelAddMeniu;
	QLabel* categoryLabelAddMeniu;
	QLabel* valueLabelAddMeniu;
	QLabel* descriptionLabelAddMeniu;

	QDateTimeEdit* dateTimeEdtiAddMeniu;
	QComboBox* typeComboBoxAddMeniu;
	QComboBox* methodOfPaymentComboBoxAddMeniu;
	QComboBox* categoryComboBoxAddMeniu;
	QLineEdit* valueLineEditAddMeniu; //TO DO: when selecting value, display a calculator,too
	QLineEdit* descriptionLineEditAddMeniu;

	QPushButton* addButtonMeniu;
	QFormLayout* mainLayout;

	//help window
	QWidget* helpWindow;
	QPlainTextEdit* instructionsBox;
	QVBoxLayout* helpLayout;

	Ui::ExpensetrackerClass ui;
	Repository* transfers;
	std::vector<Transfer> currentTransfersOnPage;//this will changed based on the day the user selected and based on the page selected as well (daily,weekly or monthly)

private:
	void displayDailyTransfers();
	void displayWeeklyTransfers();
	void displayMonthlyTransfers();
	void displayHelp();
	void verifyExpensesCheckBox();
	void verifyIncomeCheckBox();
	void displayExpensesOnly();
	void displayIncomeOnly();
	void displayResults();
	void displayInDaily();
	void displayInWeekly();
	void displayInMonthly();

	void showCharts();
	void updateCharts();
	void checkMeniuTab();
	void showPeriodicalMeniu();
	void preparePeriodicalChart();
	void prepareIncomeChart();
	void prepareExpenseChart();
	void setupAndShowChart(std::string,std::string);
	void populateCategoriesList();
	void showPressedTransfers(std::string category);
	void computeAdditionalInformationAboutCategory();
	void showAdditionalEvidence(std::vector<Transfer> transfersToShow);
	void computeStatistics(std::vector<Transfer> transfersToShow, std::string period);

	void getStartingStatistics();
	void getWeeklyStatistics();
	void getMonthlyStatistics();
	void displayAddMeniu();
	void addTransfer();
	void updateTransfers();
	void updateStatistics();
	void populateDateAndHour();
	void populateCategories(const QString &type);
	void setupCompleter();
};
