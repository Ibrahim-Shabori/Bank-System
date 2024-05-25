#pragma once
#include <iostream>
#include "Global.h"
#include "clsDate.h"
#include <fstream>
#include <vector>
#include "clsString.h"

using namespace std;

class clsLoginRegister{
private:
    string _UserName;
    string _Password;
    int _Permissions;
    string _DateTime;

    void _AddLoginRegisterRecordToFile(){
        string Record = _DateTime + "/##/" + _UserName + "/##/" + _Password + "/##/"
                        + to_string(_Permissions);
        fstream File;
        File.open("LoginRegister.txt", ios::out | ios::app);
        if (File.is_open()){
            File << Record << endl;
            File.close();
        }
    }

    static clsLoginRegister _ConvertRecordToLoginRegisterObject(string Record){
        vector<string> vData = clsString::Split(Record, "/##/");
        clsLoginRegister LoginReg;
        LoginReg.SetDateTime(vData[0]);
        LoginReg.SetUserName(vData[1]);
        LoginReg.SetPassword(vData[2]);
        LoginReg.SetPermissions(stoi(vData[3]));
        return LoginReg;
    }

    static vector<clsLoginRegister> _LoadLoginRegisterRecordsFromFile(){
        vector<clsLoginRegister> Records;
        fstream File;
        File.open("LoginRegister.txt", ios::in);
        if (File.is_open()){
            clsLoginRegister NewRecord;
            string Record;
            while(getline(File, Record)){
                if (Record=="") break;
                NewRecord = _ConvertRecordToLoginRegisterObject(Record);
                Records.push_back(NewRecord);
            }
            File.close();
        }
        return Records;
    }

public:
    clsLoginRegister(string UserName, string Password, double Permissions){
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
        _DateTime = clsDate::GetSystemDateTime();
    }

    clsLoginRegister(){
        _UserName = CurrentUser.GetUserName();
        _Password = CurrentUser.GetPassword();
        _Permissions = CurrentUser.GetPermissions();
        _DateTime = clsDate::GetSystemDateTime();
    }

    string UserName(){
        return _UserName;
    }
    string Password(){
        return _Password;
    }
    string DateTime(){
        return _DateTime;
    }
    int Permissions(){
        return _Permissions;
    }

    void SetUserName(string UserName){
        _UserName = UserName;
    }
    void SetPassword(string Password){
        _Password = Password;
    }
    void SetDateTime(string DateTime){
        _DateTime = DateTime;
    }
    void SetPermissions(int Permissions){
        _Permissions = Permissions;
    }

    void Save(){
        _AddLoginRegisterRecordToFile();
    }

    static vector<clsLoginRegister> GetLoginRegistersList(){
        return _LoadLoginRegisterRecordsFromFile();
    }
};

