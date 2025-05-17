#pragma once

#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"



class clsCurrencyCalculatorScreen : protected clsScreen
{

private:

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";
    }

public:

    static void ShowCurrencyCalaulatorScreen()
    {
        _DrawScreenHeader("    Currancy Calaulator Screen");

        string Code1, Code2;
        float Amount;

        cout << "\n\nEnter Code Of Currency 1 : ";
        Code1 = clsInputValidate::ReadString();
        while (!clsCurrency::IsCurrencyExist(Code1))
        {
            cout << "\nCurrency Not Found Enter Another Code : ";
            Code1 = clsInputValidate::ReadString();
        }
        clsCurrency Currency1 = clsCurrency::FindByCode(Code1);
        _PrintCurrency(Currency1);

        cout << "\n\nEnter Code Of Currency 2 : ";
        Code2 = clsInputValidate::ReadString();
        while (!clsCurrency::IsCurrencyExist(Code2))
        {
            cout << "\nCurrency Not Found Enter Another Code : ";
            Code2 = clsInputValidate::ReadString();
        }
        clsCurrency Currency2 = clsCurrency::FindByCode(Code2);
        _PrintCurrency(Currency2);


        cout << "\n\nEnter Amount To Exchange From [" << Currency1.CurrencyName() << "] To [" << Currency2.CurrencyName() << "] : ";
        Amount = clsInputValidate::ReadDblNumber();

        cout << "\n\nResult : ";
        cout << clsCurrency::CurrencyExchange(Currency1, Currency2, Amount);

        char Answer = 'n';
        cout << "\n\nDo You Want To Do Another Exchange Y/N ? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            system("cls");
            ShowCurrencyCalaulatorScreen();
        }

    }



};

