#pragma once
#include <vector>
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include "domain.h"
#include <utility>
using namespace std;

class RepoError : public std::exception {
public:
	virtual const char* what() const throw() = 0;
};

class InexistingElement :public RepoError {
public:
	virtual const char* what() const throw()
	{
		return "There is no such element!\n";
	}
};

class ExistingElement :public RepoError {
public:
	virtual const char* what() const throw()
	{
		return "This element already exists!\n";
	}
};

class InvalidPosition :public RepoError {
public:
	virtual const char* what() const throw()
	{
		return "That is an invalid position!\n";
	}
};


class Repository {
private:
	std::vector<Transfer> elements;
	std::string fileName;
public:
	Repository(std::string fileNameFromUser) {
		fileName = fileNameFromUser;
	}
	void readFromFile() {
		std::ifstream file;
		file.open(fileName);
		if (!file.is_open())
			return;
		Transfer* element = new Transfer{};
		while (file >> element) {
			elements.push_back(*element);
		}
		file.close();
		delete element;
	}
	void writeToFile() {
		std::ofstream file;
		file.open(fileName);
		if (!file.is_open())
			return;
		for (auto el : elements)
			file << el;
		file.close();
	}
	int getSize() {
		return elements.size();
	}
	Transfer getElementFromPosition(int position) {
		if (position >= elements.size())
			throw std::exception("Invalid position");
		return elements[position];
	}
	void addElement(Transfer element) {
		elements.push_back(element);
		writeToFile();
	}
	bool searchElement(Transfer elementToBeFound) {
		for (auto element : elements) {
			if (element == elementToBeFound)
				return true;
		}
		return false;
	}
	void removeElement(int position) {
		if(position<0 || position>elements.size())
		elements.erase(elements.begin(), elements.begin() + position);
		writeToFile();
	}
	
	std::vector<Transfer> filterByDate(QDate date) {
		std::vector<Transfer> transfersFiltered;
		for (auto element : elements) {
			if (element.getDate() == date)
				transfersFiltered.push_back(element);
		}
		return transfersFiltered;
	}
	std::vector<Transfer> filterByWeek(QDate endDate) {
		QDate startDate = endDate.addDays(-7);
		std::vector<Transfer> transfersFiltered;
		for (auto element : elements) {
			QDate date = element.getDate();
			if (startDate <= date && date <= endDate)
				transfersFiltered.push_back(element);
		}
		sort(transfersFiltered.begin(), transfersFiltered.end());
		return transfersFiltered;
	}
	std::vector<Transfer> filterByMonth(QDate date) {
		std::vector<Transfer> transfersFiltered;
		for (auto element : elements) {
			QDate dateToCheck = element.getDate();
			if (dateToCheck.month()==date.month())
				transfersFiltered.push_back(element);
		}
		sort(transfersFiltered.begin(), transfersFiltered.end());
		return transfersFiltered;
	}
	std::vector<Transfer> filterByString(std::string criteria) {
		std::vector<Transfer> result;
		for (auto transfer: elements) {
			int pos = transfer.toFullString().find(criteria);
			if (pos != std::string::npos) {
				result.push_back(transfer);
			}
		}
		return result;
	}
	std::vector<Transfer> filterByPeriodAndType(QDate date, std::string period, std::string type) {
		/*
		period can be "Week" or "Month"
		type can be "Income" or "Expense"
		*/
		//filtering
		std::vector<Transfer> transfers;
		if (period == "Week")
			transfers = filterByWeek(date);
		else
			transfers = filterByMonth(date);
		std::vector<Transfer> transfersFiltred;
		for (auto transfer : transfers) {
			if (transfer.getType() == type)
				transfersFiltred.push_back(transfer);
		}
		return transfersFiltred;
	}
	std::vector<Transfer> filterByIntervalAndType(QDate startDate, QDate endDate, std::string type) {
		std::vector<Transfer> transfersFiltered;
		for (auto element : elements) {
			QDate date = element.getDate();
			if (startDate <= date && date <= endDate && element.getType()==type)
				transfersFiltered.push_back(element);
		}
		sort(transfersFiltered.begin(), transfersFiltered.end());
		return transfersFiltered;
	}
	std::map<std::string, int> getPeriodicalStatistics(QDate startDate, QDate endDate, std::string type) {
		std::vector<Transfer> transfersForStatistics = filterByIntervalAndType(startDate, endDate, type);
		std::map< std::string, int > statistics;
		for (auto transfer : transfersForStatistics) {
			auto category = transfer.getCategory();
			auto value = transfer.getValue();
			if (statistics.count(category) == 0)
				statistics.insert(pair<std::string, int>(category, value));
			else
				statistics[category] = statistics[category] + value;
		}
		return statistics;
	}
	std::map<std::string,int> getStatisticsForChart(QDate date,std::string period, std::string type) {
		std::vector<Transfer> transfersForStatistics = filterByPeriodAndType(date, period, type);
		std::map< std::string,int > statistics;
		for (auto transfer : transfersForStatistics) {
			auto category = transfer.getCategory();
			auto value = transfer.getValue();
			if (statistics.count(category) == 0)
				statistics.insert(pair<std::string, int>(category, value));
			else
				statistics[category] = statistics[category] + value;
		}
		return statistics;
	}

	double getTotalIncome() {
		double result = 0;
		for (auto element : elements) {
			if (element.getType() == "Income") {
				result += element.getValue();
			}
		}
		return result;
	}
	double getTotalExpenses() {
		double result = 0;
		for (auto element : elements) {
			if (element.getType() == "Expense") {
				result += element.getValue();
			}
		}
		return result;
	}
};
