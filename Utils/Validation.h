#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>
#include <regex>
#include <ctime>
using namespace std;

namespace Validation {

    // Validate CNIC format: XXXXX-XXXXXXX-X
    inline bool isValidCNIC(const string& cnic) {
        regex pattern("^\\d{5}-\\d{7}-\\d{1}$");
        return regex_match(cnic, pattern);
    }

    // Validate phone number format: 03XXXXXXXXX
    inline bool isValidPhone(const string& phone) {
        regex pattern("^03\\d{9}$");
        return regex_match(phone, pattern);
    }

    // Validate PIN: 4-digit
    inline bool isValidPIN(const string& pin) {
        regex pattern("^\\d{4}$");
        return regex_match(pin, pattern);
    }

    // Validate password: minimum 6 characters
    inline bool isValidPassword(const string& password) {
        return password.length() >= 6;
    }

    // Age check: must be at least 18
    inline bool isAdult(const string& dob) {
        int birthYear, birthMonth, birthDay;
        sscanf(dob.c_str(), "%d-%d-%d", &birthYear, &birthMonth, &birthDay);

        time_t now = time(0);
        tm* ltm = localtime(&now);

        int currentYear = 1900 + ltm->tm_year;
        int currentMonth = 1 + ltm->tm_mon;
        int currentDay = ltm->tm_mday;

        int age = currentYear - birthYear;
        if (currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay))
            age--;

        return age >= 18;
    }

    // Remove leading/trailing whitespace
    inline string trim(const string& str) {
        const auto strBegin = str.find_first_not_of(" \t");
        if (strBegin == string::npos) return ""; // no content

        const auto strEnd = str.find_last_not_of(" \t");
        const auto strRange = strEnd - strBegin + 1;

        return str.substr(strBegin, strRange);
    }
}

#endif
