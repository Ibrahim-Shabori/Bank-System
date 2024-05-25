#pragma once
#include <iostream>
#include "Global.h"
#include "clsDate.h"
#include <fstream>
#include <vector>
#include "clsString.h"
#include "clsBankClient.h"

using namespace std;

class clsTransfer{
private:
    string _DateTime;
    string _SenderAccountNumber;
    string _RecieverAccountNumber;
    double _Amount;
    double _SenderAmountAfterTransfer;
    double _RecieverAmountAfterTransfer;
    string _UserName;

    void _AddTransferRecordToFile(){
        string Record = _DateTime + "/##/" + _SenderAccountNumber + "/##/" + _RecieverAccountNumber + "/##/"
                        + to_string(_Amount) + "/##/" + to_string(_Amount) + "/##/" + to_string(_SenderAmountAfterTransfer) +
                        to_string(_RecieverAmountAfterTransfer) + "/##/" + _UserName;
        fstream File;
        File.open("TransferLog.txt", ios::out | ios::app);
        if (File.is_open()){
            File << Record << endl;
            File.close();
        }
    }

    static clsTransfer _ConvertRecordToTransferObject(string Record){
        vector<string> vData = clsString::Split(Record, "/##/");
        clsTransfer Transfer;
        Transfer.SetDateTime(vData[0]);
        Transfer.SetSenderAccountNumber(vData[1]);
        Transfer.SetRecieverAccountNumber(vData[2]);
        Transfer.SetAmount(stod(vData[3]));
        Transfer.SetSenderAmountAfterTransfer(stod(vData[4]));
        Transfer.SetRecieverAmountAfterTransfer(stod(vData[5]));
        Transfer.SetUserName(vData[6]);

        return Transfer;
    }

    static vector<clsTransfer> _LoadTransfersFromFile(){
        vector<clsTransfer> Records;
        fstream File;
        File.open("TransferLog.txt", ios::in);
        if (File.is_open()){
            clsTransfer NewRecord;
            string Record;
            while(getline(File, Record)){
                if (Record=="") break;
                NewRecord = _ConvertRecordToTransferObject(Record);
                Records.push_back(NewRecord);
            }
            File.close();
        }
        return Records;
    }

public:
    clsTransfer(clsBankClient Sender, clsBankClient Reciever, double Amount){
        _UserName = CurrentUser.GetUserName();
        _DateTime = clsDate::GetSystemDateTime();
        _SenderAccountNumber = Sender.AccountNumber();
        _RecieverAccountNumber = Reciever.AccountNumber();
        _Amount = Amount;
        _SenderAmountAfterTransfer = Sender.AccountBalance();
        _RecieverAmountAfterTransfer = Reciever.AccountBalance();
    }
    clsTransfer(){
        _UserName = "";
        _DateTime = "";
        _SenderAccountNumber = "";
        _RecieverAccountNumber = "";
        _Amount = 0;
        _SenderAmountAfterTransfer = 0;
        _RecieverAmountAfterTransfer = 0;
    }
    string UserName(){
        return _UserName;
    }
    string DateTime(){
        return _DateTime;
    }
    string SenderAccountNumber(){
        return _SenderAccountNumber;
    }
    string RecieverAccountNumber(){
        return _RecieverAccountNumber;
    }
    double RecieverAmountAfterTransfer(){
        return _RecieverAmountAfterTransfer;
    }
    double SenderAmountAfterTransfer(){
        return _SenderAmountAfterTransfer;
    }
    double Amount(){
        return _Amount;
    }

    void SetUserName(string UserName){
        _UserName = UserName;
    }
    void SetSenderAccountNumber(string SenderAccountNumber){
        _SenderAccountNumber = SenderAccountNumber;
    }
    void SetRecieverAccountNumber(string RecieverAccountNumber){
        _RecieverAccountNumber = RecieverAccountNumber;
    }
    void SetRecieverAmountAfterTransfer(double RecieverAmountAfterTransfer){
        _RecieverAmountAfterTransfer = RecieverAmountAfterTransfer;
    }
    void SetSenderAmountAfterTransfer(double SenderAmountAfterTransfer){
        _SenderAmountAfterTransfer = SenderAmountAfterTransfer;
    }
    void SetAmount(double Amount){
        _Amount = Amount;
    }
    void SetDateTime(string DateTime){
        _DateTime = DateTime;
    }

    void Save(){
        _AddTransferRecordToFile();
    }

    static vector<clsTransfer> GetTransferList(){
        return _LoadTransfersFromFile();
    }
};

