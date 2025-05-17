#pragma once

#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"




class clsFindCurrencyScreen : protected clsScreen
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

    static void ShowFindCurrencyScreen()
    {
        _DrawScreenHeader("\t  Find Currency Screen");


        short Choice = 1;
        cout << "\n\nFind By: [1] Code Or [2] Country ? ";
        Choice = clsInputValidate::ReadIntNumberBetween(1, 2, "Choose Number 1 Or Number 2 ? ");

        if (Choice == 1)
        {
            string code = "";
            cout << "\n\nEnter Currency Code ? ";
            code = clsInputValidate::ReadString();

            clsCurrency Currncy = clsCurrency::FindByCode(code);

            if (Currncy.IsEmpty())
            {
                cout << "\nCurrency Not Found.." << endl;
            }
            else
            {
                cout << "\nCurrency Found.." << endl;
                _PrintCurrency(Currncy);
            }

        }
        else
        {

            string country = "";
            cout << "\n\nEnter Country Name ? ";
            country = clsInputValidate::ReadString();

            clsCurrency Currncy = clsCurrency::FindByCountry(country);

            if (Currncy.IsEmpty())
            {
                cout << "\nCurrency Not Found.." << endl;
            }
            else
            {
                cout << "\nCurrency Found.." << endl;
                _PrintCurrency(Currncy);
            }

        }

    }


};

