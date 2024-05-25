#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"

using namespace std;

class clsBankClient : public clsPerson{
private:
    enum enMode {EmptyMode= 0, UpdateMode = 1, AddNewMode = 2};
    enMode _Mode;
    string _AccountNumber;
    double _AccountBalance;
    string _PinCode;
    bool _MarkForDelete = false;

    static clsBankClient _ConvertLineToBankClientObject(string Line, string Separator = "#//#"){
        vector<string> vBankClientData;
        vBankClientData = clsString::Split(Line, Separator);
        return clsBankClient(enMode::UpdateMode, vBankClientData[0], vBankClientData[1],
                             vBankClientData[2], vBankClientData[3], vBankClientData[4],
                             vBankClientData[5], stod(vBankClientData[6]));
    }

    static vector<string> _ConvertClientDataToVector(clsBankClient Client){
        vector<string> vClientData(7);
        vClientData[0] = Client.FirstName();
        vClientData[1] = Client.LastName();
        vClientData[2] = Client.Email();
        vClientData[3] = Client.Phone();
        vClientData[4] = Client.AccountNumber();
        vClientData[5] = Client.PinCode();
        vClientData[6] = to_string(Client.AccountBalance());
        return vClientData;
    }

    static string _ConvertClientDataToLine(clsBankClient &Client){
        vector<string> vClientData;
        vClientData = clsBankClient::_ConvertClientDataToVector(Client);
        string Line;
        Line = clsString::JoinString(vClientData, "#//#");
        return Line;
    }

    static clsBankClient _GetEmptyClientObject(){
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static vector<clsBankClient> _LoadClientsDataFromFile(){
        vector<clsBankClient> Clients;
        fstream File;
        File.open("Clients.txt", ios::in);
        if (File.is_open()){
            string Line;
            while(getline(File, Line)){
                clsBankClient Client = clsBankClient::_ConvertLineToBankClientObject(Line);
                Clients.push_back(Client);
            }
            File.close();
        }
        return Clients;
    }

    void _SaveClientsDataToFile(vector<clsBankClient> vBankClients){
        fstream File;
        File.open("Clients.txt", ios::out);
        if (File.is_open()){
            for (clsBankClient &C : vBankClients){
                if (!C._MarkForDelete){
                    string ClientData = clsBankClient::_ConvertClientDataToLine(C);
                    File << ClientData << "\n";
                }
            }
            File.close();
        }
    }

    void _Update(){
        vector<clsBankClient> vBankClients;
        vBankClients = _LoadClientsDataFromFile();
        for (clsBankClient &C: vBankClients){
            if (C.AccountNumber() == AccountNumber()){
                C = *this;
                break;
            }
        }
        _SaveClientsDataToFile(vBankClients);
    }

    void _AddDataLineToFile(string Line){
        fstream File;
        File.open("Clients.txt", ios::out | ios::app);
        if (File.is_open()){
            File << Line << "\n";
            File.close();
        }
    }

    void _AddNew(){
        _AddDataLineToFile(_ConvertClientDataToLine(*this));
    }

public:
    enum enSaveResults {svFailedEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExists = 2};

    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
    string AccountNumber, string PinCode, double AccountBalance)
    : clsPerson(FirstName, LastName, Email, Phone){
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
        _Mode = Mode;
    }

    bool IsEmpty(){
        return (_Mode == enMode::EmptyMode);
    }

    string AccountNumber(){
        return _AccountNumber;
    }

    void SetPinCode(string PinCode){
        _PinCode = PinCode;
    }

    string PinCode(){
        return _PinCode;
    }

    void SetAccountBalance(double AccountBalance){
        _AccountBalance = AccountBalance;
    }

    double AccountBalance(){
        return _AccountBalance;
    }

    void Print(){
        cout << "\n         Client Card:    \n";
        cout << "----------------------------------\n";
        cout << "First Name: " << FirstName() << "\n";
        cout << "Last Name: " << LastName() << "\n";
        cout << "Full Name: " << FullName() << "\n";
        cout << "Email: " << Email() << "\n";
        cout << "Phone Number: " << Phone() << "\n";
        cout << "Acc. Number: " << _AccountNumber << "\n";
        cout << "Password: " << _PinCode << "\n";
        cout << "Balance: " << _AccountBalance << "\n";
        cout << "----------------------------------\n";
    }

    static clsBankClient Find(string AccountNumber){
        fstream File;
        File.open("Clients.txt", ios::in);
        string Line;
        if (File.is_open()){
            while (getline(File, Line)){
                clsBankClient Client = _ConvertLineToBankClientObject(Line);
                if (Client.AccountNumber() == AccountNumber){
                    File.close();
                    return Client;
                }
            }
            File.close();
        }
        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string Password){
        fstream File;
        File.open("Clients.txt", ios::in);
        string Line;
        if (File.is_open()){
            while (getline(File, Line)){
                clsBankClient Client = _ConvertLineToBankClientObject(Line);
                if ((Client.AccountNumber() == AccountNumber) && (Client.PinCode() == Password)){
                    File.close();
                    return Client;
                }
            }
            File.close();
        }
        return _GetEmptyClientObject();
    }

    static clsBankClient GetAddNewClientObject(string AccountNumber){
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    static bool IsClientExist(string AccountNumber){
        clsBankClient Client = Find(AccountNumber);
        return (!Client.IsEmpty());
    }

    static vector<clsBankClient> GetClientsList(){
        return _LoadClientsDataFromFile();
    }

    static double GetTotalBalances(){
        vector<clsBankClient> vBankClients;
        vBankClients = GetClientsList();
        double TotalBalances = 0;
        for (clsBankClient &C : vBankClients){
            TotalBalances += C.AccountBalance();
        }
        return TotalBalances;
    }

    enSaveResults Save(){
        switch(_Mode){
            case enMode::EmptyMode:
                return enSaveResults::svFailedEmptyObject;
                break;
            case enMode::UpdateMode:
                _Update();
                return enSaveResults::svSucceeded;
                break;
            case enMode::AddNewMode:
                if (clsBankClient::IsClientExist(_AccountNumber)){
                    return enSaveResults::svFailedAccountNumberExists;
                } else{
                    _AddNew();
                    _Mode = enMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                }
        }
        return enSaveResults::svSucceeded;
    }

    bool Delete(){
        vector<clsBankClient> vBankClients;
        vBankClients = _LoadClientsDataFromFile();
        for (clsBankClient &C : vBankClients){
            if (C.AccountNumber() == _AccountNumber){
                C._MarkForDelete = true;
                break;
            }
        }
        _SaveClientsDataToFile(vBankClients);
        *this = clsBankClient::_GetEmptyClientObject();
        return true;
    }

    void Deposit(double Amount){
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount){
        if (Amount <= _AccountBalance){
            _AccountBalance -= Amount;
            Save();
            return true;
        }
        return false;
    }
};