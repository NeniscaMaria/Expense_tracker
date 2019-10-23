#pragma once
#include <string>
#include <QDate>
#include <QTime>
class Transfer {
private:
	std::string type; //can be Expense or income
	QDate date;
	QTime hour;
	std::string methodOfPayment;//cash or card
	std::string category;//a list will be provided
	double value;
	std::string description;
public:
	Transfer() {};
	Transfer(std::string typeFromUser, QDate dateFromUser, QTime hourFromUser, std::string paymentFromUser, std::string categoryFromUser, double valueFromUser, std::string descriptionFromUser) {
		type = typeFromUser;
		date = dateFromUser;
		hour = hourFromUser;
		methodOfPayment = paymentFromUser;
		category = categoryFromUser;
		value = valueFromUser;
		description = descriptionFromUser;
	}
	~Transfer() {};
	//getters
	std::string getType() {
		return type;
	}
	QDate getDate() {
		return date;
	}
	QTime getHour() {
		return hour;
	}
	std::string getMethodOfPayment() {
		return methodOfPayment;
	}
	std::string getCategory() {
		return category;
	}
	double getValue() {
		return value;
	}
	std::string getDescription() {
		return description;
	}

	std::string toStr() {
		std::string result = date.toString().toStdString()+", "+hour.toString("hh:mm").toStdString()+", "+category + ", "  + methodOfPayment + ", " + std::to_string(value) + " lei, " + description;
		return result;
	}
	std::string toFullString() {
		std::string result = type + ", " + date.toString().toStdString() + ", " + hour.toString("hh:mm").toStdString() + ", " + category + ", " + methodOfPayment + ", " + std::to_string(value) + " lei, " + description;
		return result;
	}
	friend std::ostream& operator<<(std::ostream& os, Transfer transfer) {
		os << transfer.type << "," << transfer.date.toString("dd.MM.yyyy").toStdString() << "," << transfer.hour.toString("hh:mm").toStdString() << "," << transfer.methodOfPayment << "," << transfer.category << "," << transfer.value << ","<<transfer.description<<"\n";
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Transfer* transfer) {
		std::string line;
		getline(is, line);
		char array[512];
		strcpy(array, line.c_str());
		std::vector<char*> tokens;
		char* token = strtok(array, ",");
		while (token != NULL) {
			tokens.push_back(token);
			token = strtok(NULL, ",");
		}
		if (tokens.size() == 6) {//there is no description
			std::string typeOfTranferFromFile = tokens[0];
			transfer->type = typeOfTranferFromFile;
			std::string dateFromFile = tokens[1];
			transfer->date = QDate::fromString(QString::fromStdString(dateFromFile),"dd.MM.yyyy");
			std::string hourFromFile = tokens[2];
			transfer->hour = QTime::fromString(QString::fromStdString(hourFromFile),"hh:mm");
			std::string methodOfPaymentFromFile = tokens[3];
			transfer->methodOfPayment = methodOfPaymentFromFile;
			std::string categoryFromFile = tokens[4];
			transfer->category = categoryFromFile;
			double valueFromFile = atof(tokens[5]);
			transfer->value = valueFromFile;
			std::string descriptionFromFile = "";
			return is;
		}
		if (tokens.size() != 7)
			return is;
		std::string typeOfTranferFromFile = tokens[0];
		transfer->type = typeOfTranferFromFile;
		std::string dateFromFile = tokens[1];
		transfer->date = QDate::fromString(QString::fromStdString(dateFromFile), "dd.MM.yyyy");
		std::string hourFromFile = tokens[2];
		transfer->hour = QTime::fromString(QString::fromStdString(hourFromFile), "hh:mm");
		std::string methodOfPaymentFromFile = tokens[3];
		transfer->methodOfPayment = methodOfPaymentFromFile;
		std::string categoryFromFile = tokens[4];
		transfer->category = categoryFromFile;
		double valueFromFile = atof(tokens[5]);
		transfer->value = valueFromFile;
		std::string descriptionFromFile = tokens[6];
		transfer->description = descriptionFromFile;
		return is;
	}
	bool operator==(Transfer t) {
		return type == t.type && date == t.date && hour == t.hour && methodOfPayment == t.methodOfPayment && category == t.category && value == t.value && description == t.description;
	}
	bool operator>(Transfer t) {
		return date > t.date;
	}
	bool operator<(Transfer t) {
		return date < t.date;
	}
	
};