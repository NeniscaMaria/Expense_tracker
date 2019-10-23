#include "Expensetracker.h"
#include <QtWidgets/QApplication>
//TO DO:
/*
BUGS:
->see why a transer is logged in 2 times if read from file. When running with debugger, it has no problem

NOTES:
->the app opens in the daily page----------------------------------------------------------------------------------------------------------------
->daily income is to be computed everytime a new income is added---------------------------------------------------------------------------------
->daily expenses are to be computed any time a new expense is added------------------------------------------------------------------------------
->in more->export: export an excel with the transfers made in a period of time, which can be selected by the user

STATISTICS:
->how much you spend using cash or card;
->show in a pie chart stats about income and expenses, i.e. how much money come from diff. sources and how much money are spent in diff. categories.----------------------
->put buttons for categories. After you click them, all the transfers made for it will be shown separately, toghether whith a chart that shows how much you spent in------
that cat. in each day-----------------------------------------------------------------------------------------------------------------------------------------------------

DAILY:
->when the date is changed, change the transfers as well-----------------------------------------------------------------------------------------

WHEN OPENING:
->compute the income so far + show; DONE---------------------------------------------------------------------------------------------------------
->compute total expenses + show; DONE -----------------------------------------------------------------------------------------------------------
->compute total,i.e: income-expenses. Color in green if it is positive.Otherwise, color in red.;-------------------------------------------------

UI:
->think what to do with the calendar page
->when clicking on a transfer, open a new window which shows you more actions to take next, such as: edit, remove, etc

FILTERING:
->filter by date, which is obtained from the widget dateEditTransfer. Display them on the daily page + refresh the computations---------------------
->filter by week and month. In the weekly and monthly pages, the same computations are to be made as fot the daily page.----------------------------
->the user can search by date,hour,category,type or description-------------------------------------------------------------------------------------
->filter by type of transfer------------------------------------------------------------------------------------------------------------------------

SETTINGS:
->include the possibility to change the currency

ADD MENIU:
->when you select the value, display the possibility to open  calculator
*/
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Repository* transfers = new Repository{ "transfers.txt" };
	transfers->readFromFile();
	Expensetracker* window = new Expensetracker{ transfers };
	window->show();
	return a.exec();
}