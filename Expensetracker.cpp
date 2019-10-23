#include "Expensetracker.h"
#include <ctime>
#include <chrono>
#include <qerrormessage.h>
#include <qdebug.h>
QT_CHARTS_USE_NAMESPACE

class ValidationError : public std::exception {
public:
	virtual const char* what() const throw() = 0;
};
class InvalidValue :public ValidationError {
public:
	virtual const char* what() const throw()
	{
		return "Please insert a valid value!\n";
	}
};
class InvalidDescription :public ValidationError {
public:
	virtual const char* what() const throw()
	{
		return "A transfer must have a description!\n";
	}
};
void validateValue(std::string valueFromUser) {
	if (atof(valueFromUser.c_str()) <= 0)
		throw InvalidValue();
}
void validateDescription(std::string descriptionFromUser) {
	if (descriptionFromUser == "")
		throw InvalidDescription();
}


Expensetracker::Expensetracker(Repository* transfersFromUser, QWidget *parent)
	: QMainWindow(parent)
{
	chartPresentIncome = false;
	chartPresentExpense = false;
	ui.setupUi(this);
	transfers = transfersFromUser;
	QDate date = QDate::currentDate();
	//setting the date in the dateEdit (the widget from the right upper corner)
	ui.dateEditTransfer->setDate(date);
	ui.dateEditStatus->setDate(date);

	tabIndex = ui.optionsTabWidget->currentIndex();
	//start-up computations
	displayDailyTransfers();

	//charts
	seriesIncome = new QPieSeries();
	chartIncome = new QChart();
	chartViewIncome = new QChartView(chartIncome);
	additionalInformation = new QLabel{ "See more information about these categories: " };
	categoriesList = new QListWidget{};

	//additional info charts
	additionalInformationWindow = new QWidget{};
	additionalInformationLayout = new QVBoxLayout{};
	additionalInformationSeries = new QLineSeries();
	additionalInformationChart = new QChart();
	aditionalInformationChartView = new QChartView(additionalInformationChart);
	additionalInformationList = new QListWidget();
	axisX = new QCategoryAxis();
	axisY = new QCategoryAxis();
	chartDisplayed = false;

	//setting up the color vector
	colorsForPieCharts.push_back(QColor(255, 0, 0, 127));
	colorsForPieCharts.push_back(Qt::darkYellow);
	colorsForPieCharts.push_back(Qt::darkBlue);
	colorsForPieCharts.push_back(Qt::darkRed);
	colorsForPieCharts.push_back(Qt::darkGray);
	colorsForPieCharts.push_back(Qt::darkMagenta);
	colorsForPieCharts.push_back(Qt::darkGreen);
	colorsForPieCharts.push_back(Qt::black);
	colorsForPieCharts.push_back(Qt::green);
	colorsForPieCharts.push_back(Qt::blue);
	colorsForPieCharts.push_back(Qt::red);
	colorsForPieCharts.push_back(Qt::lightGray);
	colorsForPieCharts.push_back(Qt::cyan);	
	colorsForPieCharts.push_back(Qt::magenta);
	colorsForPieCharts.push_back(Qt::gray);
	colorsForPieCharts.push_back(Qt::yellow);
	colorsForPieCharts.push_back(Qt::darkCyan);
	colorsForPieCharts.push_back(QColor(0, 0, 255, 127));
	//creating the widgets for the add meniu
	addWindow = new QWidget{};
	addWindow->setWindowTitle("Add Meniu");
	mainLayout = new QFormLayout{};
	addWindow->setLayout(mainLayout);
	dateLabelAddMeniu = new QLabel{ "Date & Hour: " };
	typeLabelAddMeniu = new QLabel{ "Type" };
	methodOfPaymentLabelAddMeniu = new QLabel{ "Method of payment" };
	categoryLabelAddMeniu = new QLabel{ "Category" };
	valueLabelAddMeniu = new QLabel{ "Value" };
	descriptionLabelAddMeniu = new QLabel{ "Description" };
	typeComboBoxAddMeniu = new QComboBox{};
	typeComboBoxAddMeniu->addItem(QString::fromStdString("Income"));
	typeComboBoxAddMeniu->addItem(QString::fromStdString("Expense"));
	methodOfPaymentComboBoxAddMeniu = new QComboBox{};
	methodOfPaymentComboBoxAddMeniu->addItem(QString::fromStdString("Cash"));
	methodOfPaymentComboBoxAddMeniu->addItem(QString::fromStdString("Card"));
	categoryComboBoxAddMeniu = new QComboBox{};
	valueLineEditAddMeniu = new QLineEdit{}; //TO DO: when selecting value, display a calculator,too
	descriptionLineEditAddMeniu = new QLineEdit{};
	addButtonMeniu = new QPushButton{ "Add" };
	dateTimeEdtiAddMeniu = new QDateTimeEdit{};

	setupCompleter();

	//periodical meniu
	periodicalMeniuWindow = new QWidget();
	periodicalLayout = new QFormLayout();
	periodicalMeniuWindow->setLayout(periodicalLayout);

	informativeText = new QLabel{ "Please insert the desired period of time: " };
	startDateLabel = new QLabel{ "Start date: " };
	endDateLabel = new QLabel{ "End date: " };
	startDateEdit = new QDateEdit{};
	startDateEdit->setCalendarPopup(true);
	endDateEdit = new QDateEdit{};
	endDateEdit->setCalendarPopup(true);
	startDateEdit->setDate(QDate::currentDate().addDays(-14));
	endDateEdit->setDate(QDate::currentDate());
	showButton = new QPushButton{ "Show charts" };

	//connecting buttons
	//the add button from the daily,weekly and monthly menus are, essentially, the same button
	connect(ui.addButtonDaily, &QPushButton::pressed, this, &Expensetracker::displayAddMeniu);
	connect(addButtonMeniu, &QPushButton::pressed, this, &Expensetracker::addTransfer);
	connect(addButtonMeniu, &QPushButton::pressed, this, &Expensetracker::updateCharts);
	connect(ui.searchButton, &QPushButton::pressed, this, &Expensetracker::displayResults);
	connect(showButton, &QPushButton::pressed, this, [=]() {
		preparePeriodicalChart();
		if (ui.statusTabWidget->currentIndex() == 0) {
			setupAndShowChart("Income", "Update");
		}
		else {
			setupAndShowChart("Expense", "Update");
		}
	});

	connect(ui.dateEditTransfer, &QDateEdit::dateChanged, this, &Expensetracker::displayDailyTransfers);//when the date is changed, new daily transfers are to be displayed
	connect(ui.optionsTabWidget, &QTabWidget::currentChanged, this, &Expensetracker::updateTransfers);
	connect(ui.meniuTabWidget, &QTabWidget::currentChanged, this, &Expensetracker::checkMeniuTab);
	connect(ui.statusTabWidget, &QTabWidget::currentChanged, this, &Expensetracker::showCharts);
	connect(ui.actionViewHelp, &QAction::triggered, this, &Expensetracker::displayHelp);
	connect(categoriesList, &QListWidget::itemClicked, this, &Expensetracker::computeAdditionalInformationAboutCategory);

	connect(ui.expensesCheckBox, &QCheckBox::stateChanged, this, &Expensetracker::verifyExpensesCheckBox);
	connect(ui.comboBoxStatus, QOverload<int>::of(&QComboBox::currentIndexChanged),
		[=](int index) { showCharts();  });
	connect(ui.incomeCheckBox, &QCheckBox::stateChanged, this, &Expensetracker::verifyIncomeCheckBox);

	connect(typeComboBoxAddMeniu, QOverload<const QString &>::of(&QComboBox::activated),
		[=](const QString &selectedType) {
		this->populateCategories(selectedType);
	});
	connect(typeComboBoxAddMeniu, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
		[=](const QString &selectedType) { this->populateCategories(selectedType); });
	connect(ui.comboBoxStatus, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
		[=](const QString &selectedType) { this->updateCharts(); });
}

void Expensetracker::displayDailyTransfers(){
	/*
	Function that displays the transfers from a selected date. The date is given by the user through the QDateEdit widget (dateEditTransfer).
	The starting date is today's date, set previously in the constructor.
	*/
	currentTransfersOnPage = transfers->filterByDate(ui.dateEditTransfer->date());
	if (ui.expensesCheckBox->isChecked())
		displayExpensesOnly();
	else
		displayInDaily();
	getStartingStatistics();
}
void Expensetracker::displayWeeklyTransfers(){
	currentTransfersOnPage = transfers->filterByWeek(ui.dateEditTransfer->date());
	if (ui.expensesCheckBox->isChecked())
		displayExpensesOnly();
	else
		displayInWeekly();
	getWeeklyStatistics();
}
void Expensetracker::displayMonthlyTransfers(){
	currentTransfersOnPage = transfers->filterByMonth(ui.dateEditTransfer->date());
	if (ui.expensesCheckBox->isChecked())
		displayExpensesOnly();
	else
		displayInMonthly();
	getMonthlyStatistics();
}

void Expensetracker::displayHelp(){
	helpWindow = new QWidget();
	helpWindow->setWindowTitle("Help");
	helpLayout = new QVBoxLayout();
	instructionsBox = new QPlainTextEdit();
	helpWindow->setLayout(helpLayout);
	helpLayout->addWidget(instructionsBox);

	instructionsBox->insertPlainText("\tWelcome to the help page!\n\nIn the daily page will be displyed the transfers made in the day selected in the box from the right upper corner.\n\nIn the weekly page will be displayed the transfers made in the day specified above, as well as those for the 6 days prior to this date.\n\nIn the monthly page will be displayed the transfers made in the current month (which can be modified in the right upper corner).\n\nPress on the search button to display all the result in a new window.\n\nIn the more section, you can choose to export an excel file with your transfers from a desired period of time.");
	helpWindow->show();
}

void Expensetracker::verifyExpensesCheckBox(){
	if (ui.expensesCheckBox->isChecked()) {
		if (ui.incomeCheckBox->isChecked()) {
			QErrorMessage* error = new QErrorMessage;
			error->showMessage("Income only is checked!");
			error->show();
			ui.expensesCheckBox->setChecked(false);
			return;
		}
		else
			displayExpensesOnly();
	}
	else 
		updateTransfers();
}
void Expensetracker::verifyIncomeCheckBox(){
	if (ui.incomeCheckBox->isChecked()) {
		if (ui.expensesCheckBox->isChecked()) {
			QErrorMessage* error = new QErrorMessage;
			error->showMessage("Expenses only is checked!");
			error->show();
			ui.incomeCheckBox->setChecked(false);
			return;
		}
		else
			displayIncomeOnly();
	}
	else 
		updateTransfers();
}

void Expensetracker::displayExpensesOnly(){
	std::vector<Transfer> expenses;
	for (auto transfer : currentTransfersOnPage) {
		if (transfer.getType() == "Expense")
			expenses.push_back(transfer);
	}
	currentTransfersOnPage = expenses;
	switch (tabIndex)
	{
	case 0://daily page
		displayInDaily();
		break;
	case 1://weekly page
		displayInWeekly();
		break;
	case 2://monthly page
		displayInMonthly();
		break;
	default:
		break;
	}
}
void Expensetracker::displayIncomeOnly(){
	std::vector<Transfer> expenses;
	for (auto transfer : currentTransfersOnPage) {
		if (transfer.getType() == "Income")
			expenses.push_back(transfer);
	}
	currentTransfersOnPage = expenses;
	tabIndex = ui.optionsTabWidget->currentIndex();
	switch (tabIndex)
	{
	case 0://daily page
		displayInDaily();
		break;
	case 1://weekly page
		displayInWeekly();
		break;
	case 2://monthly page
		displayInMonthly();
		break;
	default:
		break;
	}
}

void Expensetracker::displayResults(){
	std::string criteria = ui.searchLineEdit->text().toStdString();
	if (criteria == ""){
		QErrorMessage* error1 = new QErrorMessage{};
		error1->showMessage("Please input some search criteria!");
		error1->show();
		return;
	}
	std::vector<Transfer> searchResult = transfers->filterByString(criteria);
	if (searchResult.size() == 0) {
		QErrorMessage* error2 = new QErrorMessage{};
		error2->showMessage("Oops. It seems that there are no results :(");
		error2->show();
		return;
	}
	//setting up new window
	resultsWindow = new QWidget();
	resultsWindow->setWindowTitle("Search results");
	resultsWindowLayout = new QVBoxLayout{};
	resultsWindow->setLayout(resultsWindowLayout);
	searchResultsList = new QListWidget();
	resultsWindowLayout->addWidget(searchResultsList);

	for (int row = 0; row < searchResult.size() ; row++) {
		Transfer result = searchResult[row];
		searchResultsList->addItem(QString::fromStdString(result.toFullString()));
		if (result.getType() == "Income") {
			searchResultsList->item(row)->setForeground(Qt::darkGreen);
		}
		else {
			searchResultsList->item(row)->setForeground(Qt::darkRed);;
		}
	}
	resultsWindow->show();
}

void Expensetracker::displayInDaily()
{
	ui.dailyList->clear();
	for (int row = 0; row < currentTransfersOnPage.size(); row++) {
		Transfer transferToDisplay = currentTransfersOnPage[row];
		if (transferToDisplay.getType() == "Income") {
			ui.dailyList->addItem(QString::fromStdString(transferToDisplay.toStr()));
			ui.dailyList->item(row)->setForeground(Qt::darkGreen);
		}
		else {
			ui.dailyList->addItem(QString::fromStdString(transferToDisplay.toStr()));
			ui.dailyList->item(row)->setForeground(Qt::darkRed);
		}
	}
}
void Expensetracker::displayInWeekly()
{
	ui.weeklyList->clear();
	for (int row = 0; row < currentTransfersOnPage.size(); row++) {
		Transfer transferToDisplay = currentTransfersOnPage[row];
		if (transferToDisplay.getType() == "Income") {
			ui.weeklyList->addItem(QString::fromStdString(transferToDisplay.toStr()));
			ui.weeklyList->item(row)->setForeground(Qt::darkGreen);
		}
		else {
			ui.weeklyList->addItem(QString::fromStdString(transferToDisplay.toStr()));
			ui.weeklyList->item(row)->setForeground(Qt::darkRed);
		}
	}
}
void Expensetracker::displayInMonthly()
{
	ui.monthlyList->clear();
	for (int row = 0; row < currentTransfersOnPage.size(); row++) {
		Transfer transferToDisplay = currentTransfersOnPage[row];
		if (transferToDisplay.getType() == "Income") {
			ui.monthlyList->addItem(QString::fromStdString(transferToDisplay.toStr()));
			ui.monthlyList->item(row)->setForeground(Qt::darkGreen);
		}
		else {
			ui.monthlyList->addItem(QString::fromStdString(transferToDisplay.toStr()));
			ui.monthlyList->item(row)->setForeground(Qt::darkRed);
		}
	}
}

void Expensetracker::showCharts(){
	if (ui.statusTabWidget->currentIndex() == 0) {
		if (!chartPresentIncome) {
			prepareIncomeChart();
			setupAndShowChart("Income","Display");
			chartPresentIncome = true;
			chartPresentExpense = false;
		}
		else
			return;
	}
	else {
		if (!chartPresentExpense) {
			prepareExpenseChart();
			setupAndShowChart("Expense","Display");
			chartPresentExpense = true;
			chartPresentIncome = false;
		}
		else
			return;
	}
}
void Expensetracker::updateCharts(){
	//get the new statistics
	if (ui.statusTabWidget->currentIndex() == 0) {
		prepareIncomeChart();
		setupAndShowChart("Income","Update");
	}
	else {
		prepareExpenseChart();
		setupAndShowChart("Expense","Update");
	}
}
void Expensetracker::checkMeniuTab(){
	if (ui.meniuTabWidget->currentIndex() == 1)
		showCharts();
}

void Expensetracker::prepareIncomeChart(){
	QString chartPeriod = ui.comboBoxStatus->currentText();
	statistics.clear();
	if (chartPeriod == "Weekly")
		statistics = transfers->getStatisticsForChart(ui.dateEditStatus->date(),"Week", "Income");
	else if (chartPeriod == "Monthly")
		statistics = transfers->getStatisticsForChart(ui.dateEditStatus->date(),"Month", "Income");
	else {
		showPeriodicalMeniu();
	}
}

void Expensetracker::prepareExpenseChart(){
	QString chartPeriod = ui.comboBoxStatus->currentText();
	statistics.clear();
	if (chartPeriod == "Weekly")
		statistics = transfers->getStatisticsForChart(ui.dateEditStatus->date(), "Week", "Expense");
	else if (chartPeriod == "Monthly")
		statistics = transfers->getStatisticsForChart(ui.dateEditStatus->date(), "Month", "Expense");
	else {
		showPeriodicalMeniu();
	}
}

void Expensetracker::showPeriodicalMeniu() {
	periodicalLayout->addRow(informativeText);
	periodicalLayout->addRow(startDateLabel, startDateEdit);
	periodicalLayout->addRow(endDateLabel, endDateEdit);
	periodicalLayout->addRow(showButton);

	periodicalMeniuWindow->show();
}

void Expensetracker::preparePeriodicalChart() {
	periodicalMeniuWindow->close();
	std::string type;
	if (ui.statusTabWidget->currentIndex() == 0) {
		type = "Income";
	}
	else {
		type = "Expense";
	}
	QDate startDate = startDateEdit->date();
	QDate endDate = endDateEdit->date();
	statistics = transfers->getPeriodicalStatistics(startDate, endDate, type);
}
void Expensetracker::setupAndShowChart(std::string type,std::string function)
{
	/*
	type: Income or Expense
	function: Display or update
	*/
	//populate the series
	map<std::string, int>::iterator itr;
	seriesIncome->clear();
	for (itr = statistics.begin(); itr != statistics.end(); ++itr) {
		seriesIncome->append(QString::fromStdString(itr->first), itr->second);
	}
	//set up the slices
	slices.clear();
	int i = 0;
	for (itr = statistics.begin(); itr != statistics.end(); ++itr) {
		std::string category = itr->first;
		slices.push_back(seriesIncome->slices().at(i));
		slices[i]->setLabelVisible();
		slices[i]->setPen(QPen(colorsForPieCharts[i], 2));
		slices[i]->setBrush(colorsForPieCharts[i]);
		slices[i]->setBorderWidth(3);
		slices[i]->setLabel(QString::fromStdString(itr->first));
		connect(slices[i], &QPieSlice::hovered, this, [=](bool state) {
			if (state) {
				slices[i]->setExploded();
				slices[i]->setLabel(QString::fromStdString(category + " " + std::to_string(slices[i]->percentage() * 100) + "%"));
			}
			else {
				slices[i]->setExploded(false);
				slices[i]->setLabel(QString::fromStdString(category));
			}
		});
		connect(slices[i], &QPieSlice::clicked, this, [=]() {
			showPressedTransfers(category);
		});
		i++;
	}
	chartIncome->addSeries(seriesIncome);
	chartIncome->setAnimationOptions(QChart::AllAnimations);
	chartIncome->legend()->setVisible(false);

	chartViewIncome->setRenderHint(QPainter::Antialiasing);
	if(function=="Display")
		if (type == "Income") {
			ui.incomeExtraButtonsLayout->addWidget(chartViewIncome);
			ui.incomeExtraButtonsLayout->addWidget(additionalInformation);
			ui.incomeExtraButtonsLayout->addWidget(categoriesList);
			populateCategoriesList();
		}
		else {
			ui.expensesExtraButtonsLayout->addWidget(chartViewIncome);
			ui.expensesExtraButtonsLayout->addWidget(additionalInformation);
			ui.expensesExtraButtonsLayout->addWidget(categoriesList);
			populateCategoriesList();
		}
	else {
		populateCategoriesList();
	}
}

void Expensetracker::populateCategoriesList(){
	categoriesList->clear();
	map<std::string, int>::iterator itr;
	for (itr = statistics.begin(); itr != statistics.end(); ++itr) {
		categoriesList->addItem(QString::fromStdString(itr->first));
	}
}

void Expensetracker::showPressedTransfers(std::string category){
	pressedTransfersWindow = new QWidget{};
	pressedTransfersWindow->setWindowTitle("Selected transfers");
	pressedTransfersLayout = new QVBoxLayout{};
	pressedTransfersWindow->setLayout(pressedTransfersLayout);
	pressedTrasnsfersList = new QListWidget{};
	pressedTransfersLayout->addWidget(pressedTrasnsfersList);

	std::string period = ui.comboBoxStatus->currentText().toStdString();
	std::string type;
	if (ui.statusTabWidget->currentIndex() == 0)
		type = "Income";
	else
		type = "Expense";
	std::vector<Transfer> transfersFiltred = transfers->filterByPeriodAndType(ui.dateEditStatus->date(), period, type);
	for (auto transfer : transfersFiltred) {
		if (transfer.getCategory() == category) 
			pressedTrasnsfersList->addItem(QString::fromStdString(transfer.toFullString()));
	}
	pressedTransfersWindow->show();
}

void Expensetracker::computeAdditionalInformationAboutCategory(){
	additionalInformationSeries->clear();
	std::string category = categoriesList->currentItem()->text().toStdString();
	std::vector<Transfer> transfersFromCategory;
	std::vector<Transfer> transfers1;
	std::string type;
	if (ui.statusTabWidget->currentIndex() == 0)
		type = "Income";
	else
		type = "Expense";
	std::string period = ui.comboBoxStatus->currentText().toStdString();
	if (period == "Weekly")
		transfers1 = transfers->filterByPeriodAndType(ui.dateEditStatus->date(), "Week", type);
	else if (period == "Monthly")
		transfers1 = transfers->filterByPeriodAndType(ui.dateEditStatus->date(), "Month", type);
	else
		transfers1 = transfers->filterByIntervalAndType(startDateEdit->date(), endDateEdit->date(), type);
	for (auto transfer : transfers1) {
		if (transfer.getCategory() == category)
			transfersFromCategory.push_back(transfer);
	}
	showAdditionalEvidence(transfersFromCategory);
	for (auto transfer : transfersFromCategory) {
		additionalInformationList->addItem(QString::fromStdString(transfer.toFullString()));
	}
	additionalInformationWindow->setFixedSize(600,400);
	additionalInformationList->setFixedHeight(100);
}

void Expensetracker::showAdditionalEvidence(std::vector<Transfer> transfersToShow){

	stats.clear();
	additionalInformationWindow->setLayout(additionalInformationLayout);
	std::string period = ui.comboBoxStatus->currentText().toStdString();
	computeStatistics(transfersToShow, period);
	
	additionalInformationChart->legend()->hide();
	additionalInformationChart->addSeries(additionalInformationSeries);
	additionalInformationChart->setAxisX(axisX);
	additionalInformationChart->setAxisY(axisY);//BUG
	
	if (!chartDisplayed) {
		aditionalInformationChartView->setRenderHint(QPainter::Antialiasing);
		additionalInformationLayout->addWidget(aditionalInformationChartView);
		additionalInformationLayout->addWidget(additionalInformationList);
		additionalInformationWindow->show();
		chartDisplayed = true;
	}
}

void Expensetracker::computeStatistics(std::vector<Transfer> transfersToShow, std::string period)
{
	float maximum = -1;
	QDate startDate, endDate;
	if (period == "Weekly") {
		endDate = ui.dateEditStatus->date();
		startDate = endDate.addDays(-7);
	}
	else if (period == "Monthly") {
		endDate = ui.dateEditStatus->date();
		startDate.setDate(endDate.year(), endDate.month(), 1);
	}
	else {
		startDate = startDateEdit->date();
		endDate = endDateEdit->date();
	}
	//initializing map
	int start = startDate.toJulianDay();
	int end = endDate.toJulianDay();
	for (int i = start; i <= end;i++) {
		stats.insert(pair<QDate, int>(QDate::fromJulianDay(i), 0));
	}
	//we map the total value spent each day to the day
	for (auto transfer : transfersToShow) {
		auto date = transfer.getDate();
		auto value = transfer.getValue();
		stats[date] = stats[date] + value;
	}
	//compute max money spent in a day
	std::map<QDate, float>::iterator itr;
	int i = 0;
	for (itr = stats.begin(); itr != stats.end(); ++itr) {
		if (itr->second > maximum)
			maximum = itr->second;
		if (!chartDisplayed) 
			axisX->append(itr->first.toString("dd.MM.yyyy"), i + 1);
		additionalInformationSeries->append(i + 1, itr->second);
		i++;
	}
	axisX->setRange(0, stats.size());
	axisY->setRange(-10, maximum+2);
}


void Expensetracker::getStartingStatistics()
{
	/*
	Function that computes the total income and the total expanses from the daily transfers.
	*/
	double income=0, expenses=0,total=0;
	for (auto transfer : currentTransfersOnPage) {
		if (transfer.getType() == "Income")
			income += transfer.getValue();
		else
			expenses += transfer.getValue();
	}
	total = income - expenses;
	ui.dailyIncomeLabel->setText(QString::fromStdString("Income: " + std::to_string(income)));
	ui.dailyExpensesLabel->setText(QString::fromStdString("Expense: " + std::to_string(expenses)));
	ui.totalLabel->setText(QString::fromStdString("Total: " + std::to_string(total)));
	if (total <= 0) {
		QPalette palette = ui.totalLabel->palette();
		palette.setColor(ui.totalLabel->backgroundRole(), Qt::darkRed);
		palette.setColor(ui.totalLabel->foregroundRole(), Qt::darkRed);
		ui.totalLabel->setPalette(palette);
	}
	else {
		QPalette palette = ui.totalLabel->palette();
		palette.setColor(ui.totalLabel->backgroundRole(), Qt::darkGreen);
		palette.setColor(ui.totalLabel->foregroundRole(), Qt::darkGreen);
		ui.totalLabel->setPalette(palette);
	}
}
void Expensetracker::getWeeklyStatistics(){
	/*
	Function that computes the total income and the total expanses from the weekly transfers.
	*/
	double income=0, expenses=0, total=0;
	for (auto transfer : currentTransfersOnPage) {
		if (transfer.getType() == "Income")
			income += transfer.getValue();
		else
			expenses += transfer.getValue();
	}
	total = income - expenses;
	ui.incomeLabelWeekly->setText(QString::fromStdString("Income: " + std::to_string(income)));
	ui.ExpensesLabelWeekly->setText(QString::fromStdString("Expense: " + std::to_string(expenses)));
	ui.totalLabelWeekly->setText(QString::fromStdString("Total: " + std::to_string(total)));
	if (total <= 0) {
		QPalette palette = ui.totalLabelWeekly->palette();
		palette.setColor(ui.totalLabelWeekly->backgroundRole(), Qt::darkRed);
		palette.setColor(ui.totalLabelWeekly->foregroundRole(), Qt::darkRed);
		ui.totalLabelWeekly->setPalette(palette);
	}
	else {
		QPalette palette = ui.totalLabelWeekly->palette();
		palette.setColor(ui.totalLabelWeekly->backgroundRole(), Qt::darkGreen);
		palette.setColor(ui.totalLabelWeekly->foregroundRole(), Qt::darkGreen);
		ui.totalLabelWeekly->setPalette(palette);
	}
}
void Expensetracker::getMonthlyStatistics(){
	/*
	Function that computes the total income and the total expanses from the monthly transfers.
	*/
	double income=0, expenses=0, total=0;
	for (auto transfer : currentTransfersOnPage) {
		if (transfer.getType() == "Income")
			income += transfer.getValue();
		else
			expenses += transfer.getValue();
	}
	total = income - expenses;
	ui.incomeLabelMonthly->setText(QString::fromStdString("Income: " + std::to_string(income)));
	ui.ExpensesLabelMonthly->setText(QString::fromStdString("Expense: " + std::to_string(expenses)));
	ui.totalLabelMonthly->setText(QString::fromStdString("Total: " + std::to_string(total)));
	if (total <= 0) {
		QPalette palette = ui.totalLabelMonthly->palette();
		palette.setColor(ui.totalLabelMonthly->backgroundRole(), Qt::darkRed);
		palette.setColor(ui.totalLabelMonthly->foregroundRole(), Qt::darkRed);
		ui.totalLabelMonthly->setPalette(palette);
	}
	else {
		QPalette palette = ui.totalLabelMonthly->palette();
		palette.setColor(ui.totalLabelMonthly->backgroundRole(), Qt::darkGreen);
		palette.setColor(ui.totalLabelMonthly->foregroundRole(), Qt::darkGreen);
		ui.totalLabelMonthly->setPalette(palette);
	}
}

void Expensetracker::displayAddMeniu(){
	dateTimeEdtiAddMeniu->setCalendarPopup(true);
	populateDateAndHour();
	mainLayout->addRow(typeLabelAddMeniu, typeComboBoxAddMeniu);
	mainLayout->addRow(dateLabelAddMeniu, dateTimeEdtiAddMeniu);
	mainLayout->addRow(methodOfPaymentLabelAddMeniu, methodOfPaymentComboBoxAddMeniu);
	mainLayout->addRow(categoryLabelAddMeniu, categoryComboBoxAddMeniu);
	mainLayout->addRow(valueLabelAddMeniu, valueLineEditAddMeniu);
	mainLayout->addRow(descriptionLabelAddMeniu, descriptionLineEditAddMeniu);
	mainLayout->addRow(addButtonMeniu);
	populateCategories("Income");//the first choices
	addWindow->show();
}

void Expensetracker::addTransfer()
{
	std::string typeFromUser = typeComboBoxAddMeniu->currentText().toStdString();
	QDate dateFromUser = dateTimeEdtiAddMeniu->date();
	QTime hourFromUser = dateTimeEdtiAddMeniu->time();
	std::string methodOfPaymentFromUser = methodOfPaymentComboBoxAddMeniu->currentText().toStdString();
	std::string categoryFromUser = categoryComboBoxAddMeniu->currentText().toStdString();
	std::string valueFromUserString = valueLineEditAddMeniu->text().toStdString();
	std::string descriptionFromUser = descriptionLineEditAddMeniu->text().toStdString();
	try {
		//It is garanteed that the date and hour are valid.
		validateValue(valueFromUserString);
		validateDescription(descriptionFromUser);
	}
	catch (ValidationError& error) {
		QErrorMessage* errorBox = new QErrorMessage{};
		errorBox->showMessage(QString::fromStdString(error.what()));
		errorBox->show();
		return;
	}
	Transfer* newTransfer=new Transfer{ typeFromUser,dateFromUser,hourFromUser ,methodOfPaymentFromUser ,categoryFromUser ,atof(valueFromUserString.c_str()),descriptionFromUser };
	transfers->addElement(*newTransfer);
	delete newTransfer;
	addWindow->close();
	descriptionLineEditAddMeniu->clear();
	updateTransfers();
	updateStatistics();
}

void Expensetracker::updateTransfers(){
	/*
	Function that is called after the tabs are changed
	*/
	tabIndex = ui.optionsTabWidget->currentIndex();
	switch (tabIndex)
	{
	case 0://daily page
		displayDailyTransfers();
		break;
	case 1://weekly page
		displayWeeklyTransfers();
		break;
	case 2://monthly page
		displayMonthlyTransfers();
		break;
	case 3://calendar page
		//TO DO---------------------------------
		break;
	default:
		break;
	}

}

void Expensetracker::updateStatistics(){
	switch (tabIndex)
	{
	case 0://daily page
		getStartingStatistics();
		break;
	case 1://weekly page
		getWeeklyStatistics();
		break;
	case 2://monthly page
		getMonthlyStatistics();
		break;
	case 3://calendar page
		//TO DO---------------------------------
		break;
	default:
		break;
	}
}

void Expensetracker::populateDateAndHour(){
	dateTimeEdtiAddMeniu->setDate(ui.dateEditTransfer->date());
	dateTimeEdtiAddMeniu->setTime(QTime::currentTime());
}
void Expensetracker::populateCategories(const QString & type){
	if (type == "Income") {
		categoryComboBoxAddMeniu->clear();
		categoryComboBoxAddMeniu->addItem(QString::fromStdString("Allowence"));
		categoryComboBoxAddMeniu->addItem(QString::fromStdString("Salary"));
		categoryComboBoxAddMeniu->addItem(QString::fromStdString("Bonus"));
		categoryComboBoxAddMeniu->addItem(QString::fromStdString("Tips"));
		categoryComboBoxAddMeniu->addItem(QString::fromStdString("Others"));
	}
	else {
		categoryComboBoxAddMeniu->clear();
		categoryComboBoxAddMeniu->addItem(QString::fromStdString("Food"));
		categoryComboBoxAddMeniu->addItem(QString::fromStdString("Social Life"));
		categoryComboBoxAddMeniu->addItem(QString::fromStdString("Personal development"));
		categoryComboBoxAddMeniu->addItem(QString::fromStdString("Transport"));
		categoryComboBoxAddMeniu->addItem(QString::fromStdString("Culture"));
		categoryComboBoxAddMeniu->addItem(QString::fromStdString("House mentenance"));
		categoryComboBoxAddMeniu->addItem(QString::fromStdString("Clothes"));
		categoryComboBoxAddMeniu->addItem(QString::fromStdString("Beauty"));
		categoryComboBoxAddMeniu->addItem(QString::fromStdString("Health"));
		categoryComboBoxAddMeniu->addItem(QString::fromStdString("Education"));
		categoryComboBoxAddMeniu->addItem(QString::fromStdString("Gift"));
		categoryComboBoxAddMeniu->addItem(QString::fromStdString("Others"));
	}
}

void Expensetracker::setupCompleter(){
	QStringList completionList;
	//completionList << "Bryan" << "Bart" << "Mary";
	for (int i = 0; i < transfers->getSize(); i++) {
		completionList << QString::fromStdString(transfers->getElementFromPosition(i).toFullString());
	}
	searchCompleter = new QCompleter(completionList, this);
	searchCompleter->setCaseSensitivity(Qt::CaseInsensitive);
	searchCompleter->setFilterMode(Qt::MatchContains);
	ui.searchLineEdit->setCompleter(searchCompleter);
}
