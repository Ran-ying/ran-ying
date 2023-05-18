#include <iostream>
#include "xString.h"
#include "xString_BIT.h"
#include "xString_ID.h"

using namespace std;

enum Type
{
    BIT = 1,
    ID = 2,
};

int main(void)
{
    int number;
    cout << "МЕНЮ\n\tИнициализация\n\t\t1. Число элементов\nвыбирайте!\n" << endl;
    cout << "Число элементов:" << endl;
    cin >> number;
    xString** base = (xString**)malloc((sizeof(xString*)) * number);
    int* baseType = (int*)malloc((sizeof(int)) * number);
    int type = 0;
    do
    {
        cout << "МЕНЮ\n\tИнициализация\n\t\t2.Начальное значение\n\t3.Тестирование\nвыбирайте!" << endl;
        cin >> type;
        if (type == 2)
            while (true)
            {
                int eleID = 0;
                cout << "type 0 to exit\nномер элемента:" << endl;
                cin >> eleID;
                if (!eleID) break;
                if (eleID > number)
                {
                    cout << "номер элемента больше чем Число элементов" << endl;
                    continue;
                }
                int eleType = 0;
                cout << "type 0 to exit\nтип элемента:\n\t1. String_BIT\n\t2. String_ID" << endl;
                cin >> eleType;
                if (!eleType) break;
                if (eleType != 2 && eleType != 1)
                {
                    cout << "Тип неверно!" << endl;
                    continue;
                }
                cout << "type 0 to exit\nначальное значение элемента:" << endl;
                char eleValue[1010];
                cin >> eleValue;
                baseType[eleID - 1] = eleType;
                if (eleType == ID)  base[eleID - 1] = new xString_ID(eleValue);
                else if (eleType == BIT) base[eleID - 1] = new xString_BIT(eleValue);
            }
    } while (type != 3);
    do
    {
        cout << "\nТестирование:\nxString\n1. GetChar(int = 0)\n2. ShowElement\nxString_ID\n3. GetFirstChar()\n4. operator=(const xString_ID&)\n5. operator+(const xString_ID&, const xString_ID&)\n6. operator[](int)\n7. ShowElement\nxString_BIT\n8. Reverse(void)\n9. operator=(const xString_BIT&)\n10. operator+(const xString_BIT&, const xString_BIT&)\n11. operator/(const xString_BIT&, const xString_BIT&)\n12. ShowElement\nВыбирайте:" << endl;
        cin >> type;
        switch (type)
        {
        case 0: {break; }
        case 1:
        {
            cout << "1. GetChar(int = 0)\nelement number(type = xString):" << endl;
            for (int i = 0; i < number; i++)
                if (baseType[i] == ID || baseType[i] == BIT)
                    cout << (i + 1) << " ";
            cout << endl << "select: ";
            int eleID_1 = 0;
            cin >> eleID_1;
            cout << "Input arg: " << endl;
            int arg_1 = 0;
            cin >> arg_1;
            cout << "result: " << (*base[eleID_1-1]).GetChar(arg_1) << endl;
            break;
        }
        case 2:
        {
            cout << "2. ShowElement" << endl;
            for (int i = 0; i < number; i++)
                if (baseType[i] == ID)
                    cout << (i + 1) << ". xString_ID\t" << (*base[i]).GetStr() << endl;
                else if (baseType[i] == BIT)
                    cout << (i + 1) << ". xString_BIT\t" << (*base[i]).GetStr() << endl;
            break;
        }
        case 3:
        {
            cout << "3. GetFirstChar()\nelement number(type = xString_ID):" << endl;
            for (int i = 0; i < number; i++)
                if (baseType[i] == ID)
                    cout << (i + 1) << " ";
            cout << endl << "select: ";
            int eleID_3 = 0;
            cin >> eleID_3;
            cout << "result: " << (*(xString_ID*)(base[eleID_3-1])).GetFirstChar() << endl;
            break;
        }
        case 4:
        {
            cout << "4. operator=(const xString_ID&)\nelement number(type = xString_ID):\n" << endl;
            for (int i = 0; i < number; i++)
                if (baseType[i] == ID)
                    cout << (i + 1) << " ";
            cout << endl << "select: ";
            int eleID_4 = 0;
            cin >> eleID_4;
            xString_ID x4 = xString_ID();
            x4 = *(xString_ID*)base[eleID_4 - 1];
            cout << "success!" << endl;
            break;
        }
        case 5:
        {
            cout << "5. operator+(const xString_ID&, const xString_ID&)\nelement number(type = xString_ID):" << endl;
            for (int i = 0; i < number; i++)
                if (baseType[i] == ID)
                    cout << (i + 1) << " ";
            cout << endl << "select first number: ";
            int eleID_5_1 = 0;
            cin >> eleID_5_1;
            cout << "select second number: ";
            int eleID_5_2 = 0;
            cin >> eleID_5_2;
            cout << "result=" << (*(xString_ID*)base[eleID_5_1 - 1] + *(xString_ID*)base[eleID_5_2 - 1]).GetStr() << endl;
            break;
        }
        case 6:
        {
            cout << "6. operator[](int)\nelement number(type = xString_ID):" << endl;
            for (int i = 0; i < number; i++)
                if (baseType[i] == ID)
                    cout << (i + 1) << " ";
            cout << endl << "select element number: ";
            int eleID_6 = 0;
            cin >> eleID_6;
            cout << "length: " << (*(xString_ID*)base[eleID_6 - 1]).GetLen() << " input index: ";
            int index_6 = 0;
            cin >> index_6;
            cout << "result=" << (*(xString_ID*)base[eleID_6-1])[index_6] << endl;
            break;
        }
        case 7:
        {
            cout << "7. ShowElement" << endl;
            for (int i = 0; i < number; i++)
                if (baseType[i] == ID)
                    cout << (i + 1) << ". xString_ID\t" << (*base[i]).GetStr() << endl;
            break;
        }
        case 8:
        {
            cout << "8. Reverse(void)\nelement number(type = xString_BIT):" << endl;
            for (int i = 0; i < number; i++)
                if (baseType[i] == BIT)
                    cout << (i + 1) << " ";
            cout << "select element number: ";
            int eleID_8 = 0;
            cin >> eleID_8;
            cout << "origin: " << (*(xString_BIT*)base[eleID_8-1]).GetStr() << endl;
            cout << "result: " << (*(xString_BIT*)base[eleID_8-1]).Reverse() << endl;
            break;
        }
        case 9:
        {
            cout << "9. operator=(const xString_BIT&)\nelement number(type = xString_BIT):" << endl;
            for (int i = 0; i < number; i++)
                if (baseType[i] == BIT)
                    cout << (i + 1) << " ";
            cout << "select: ";
            int eleID_9 = 0;
            cin >> eleID_9;
            xString_BIT x9 = xString_BIT();
            x9 = *(xString_BIT*)base[eleID_9 - 1];
            cout << "success!" << endl;
            break;
        }
        case 10:
        {
            cout << "10. operator+(const xString_BIT&, const xString_BIT&)\nelement number(type = xString_BIT):" << endl;
            for (int i = 0; i < number; i++)
                if (baseType[i] == BIT)
                    cout << (i + 1) << " ";
            cout << "select first number: ";
            int eleID_10_1 = 0;
            cin >> eleID_10_1;
            cout << "select second number: ";
            int eleID_10_2 = 0;
            cin >> eleID_10_2;
            xString_BIT str_10 = *(xString_BIT*)base[eleID_10_1-1] + *(xString_BIT*)base[eleID_10_2-1];
            cout << "result=" << str_10.GetStr() << endl;
            break;
        }
        case 11:
        {
            cout << "11. operator/(const xString_BIT&, const xString_BIT&)\nelement number(type = xString_BIT):" << endl;
            for (int i = 0; i < number; i++)
                if (baseType[i] == BIT)
                    cout << (i + 1) << " ";
            cout << "select first number:";
            int eleID_11_1 = 0;
            cin >> eleID_11_1;
            cout << "select second number:";
            int eleID_11_2 = 0;
            cin >> eleID_11_2;
            xString_BIT str_11 = *(xString_BIT*)base[eleID_11_1-1] / *(xString_BIT*)base[eleID_11_2-1];
            cout << "result=" << str_11.GetStr() << endl;
            break;
        }
        case 12:
        {
            cout << "12. ShowElement" << endl;
            for (int i = 0; i < number; i++)
                if (baseType[i] == BIT)
                    cout << (i + 1) << ". xString_BIT\t" << (*base[i]).GetStr() << endl;
            break;
        }
        default:
            break;
        }
    } while (type != 0);
}