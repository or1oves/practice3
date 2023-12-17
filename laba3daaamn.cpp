#include <iostream>
#include "windows.h"
using namespace std;

int RandomValueofRange(int leftLimit, int rightLimit) {
    return leftLimit + rand() % (rightLimit - leftLimit + 1);
}

void SquareReplace(int* square[], int* square2[], const int N) { //переместить подматрицы в матрице
    const int way = (N - 4) / 2;
    for (int i = 0; i < 4; i++) {
        for (int *next = square[i], *end = square[i] + N / 2 - 1, kmem = 1, *next2 = square2[i]; kmem < (N / 2) * (N / 2) - way; next++, next2++ ) { // kmem -
            if (next == end) {
                square[i] += N;
                square2[i] += N;
                *next2 = *next;
                next = square[i];
                next2 = square2[i];
                end = square[i] + N / 2 - 1;
            }
            kmem++;
            if (kmem >= (N / 2) * (N / 2) - way) break;
            *next2 = *next;
        }
    }
}

void outMatrix(int *arr, const int N) { //запринтить матрицу принтэфом блин!!!!
    for (int *first = arr, *second = arr, *end = arr + N * N - 1; first <= end; first++) {
        if (first - N == second) {
            cout << "\n";
            second = first;
        }
        printf("%03d ", *first);
    }
    cout << "\n\n";
}

void makingMatrix(int *arr, const int N, const bool Random = false, int num = 0) { //заполнение матрицы
    if (Random) {
        for (int *first = arr, *second = arr, *end = arr + N * N - 1; first <= end; first++) {
            *first = RandomValueofRange(1, 100);
        }
    }
    else {
        for (int *first = arr, *second = arr, *end = arr + N * N - 1; first <= end; first++) {
            *first = num;
        }
    }
}

void mathInMatrix(int *arr, const int N, const int type, int num = 0) { //4 задание
    switch (type)
    {
        case 1: {
            for (int *first = arr, *second = arr, *end = arr + N * N - 1; first <= end; first++) {
                *first += num;
            }
            break;
        }
        case 2: {
            for (int *first = arr, *second = arr, *end = arr + N * N - 1; first <= end; first++) {
                *first -= num;
            }
            break;
        }
        case 3: {
            for (int *first = arr, *second = arr, *end = arr + N * N - 1; first <= end; first++) {
                *first *= num;
            }
            break;
        }
        case 4: {
            for (int *first = arr, *second = arr, *end = arr + N * N - 1; first <= end; first++) {
                *first /= num;
            }
            break;
        }
    }
}

void insertSort(int *arr, const int N) {
    int k;
    for (int *i = &arr[1], *j = nullptr, *end = arr + N * N - 1; i <= end; i++) { // заменил 0 на nullptr
        k = *i;
        j = i - 1;
        while (j >= arr && *j > k) {
            *(j + 1) = *j;
            j = j - 1;
        }
        *(j + 1) = k;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    const int N = 6;
    int arr[N * N] = {};

    while(true) {

        cin.clear();
        cin.sync();
        short int taskNumber;
        cout << "enter de task number: ";
        cin >> taskNumber;

        switch (taskNumber)
        {

            case 1: {

                const int sizeofNum = 4;
                int cnt = 1;
                int k = 1; // коэффициент уменьшения
                system("cls");
                HANDLE hStdout;
                COORD destCoord;
                hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
                destCoord.X = -sizeofNum;
                makingMatrix(arr, N); // очищение матрицы

                while (cnt <= N * N) {

                    int *upLeft = &arr[(k - 1) * N + (k - 1)]; //движение в углы
                    int *upRight = &arr[k * N - 1 - (k - 1)];
                    int *downLeft = &arr[N * N - (k * N) + (k - 1)];
                    int *downRight = &arr[N * N - ((k - 1) * N) - 1 - (k - 1)];

                    for (int *first = upLeft, *end = upRight; first <= end; first++) { //слева направо
                        *first = RandomValueofRange(1, N * N);
                        int Y = (first - arr) / N;
                        destCoord.X += sizeofNum;
                        destCoord.Y = Y;
                        SetConsoleCursorPosition(hStdout, destCoord);
                        printf("%03d\r", *first);
                        cout.flush();
                        Sleep(200);
                        cnt++;
                    }

                    for (int *first = upRight + N, *end = downRight; first <= end; first += N) { //справа на 1 вниз
                        *first = RandomValueofRange(1, N * N);
                        int Y = (first - arr) / N;
                        destCoord.Y = Y;
                        SetConsoleCursorPosition(hStdout, destCoord);
                        printf("%03d\r", *first);
                        cout.flush();
                        Sleep(200);
                        cnt++;
                    }

                    for (int *first = downRight - 1, *end = downLeft; first >= end; first--) { //правый низ налево
                        *first = RandomValueofRange(1, N * N);
                        int Y = (first - arr) / N;
                        destCoord.X -= sizeofNum;
                        destCoord.Y = Y;
                        SetConsoleCursorPosition(hStdout, destCoord);
                        printf("%03d\r", *first);
                        cout.flush();
                        Sleep(200);
                        cnt++;
                    }

                    for (int *first = downLeft - N, *end = upLeft + N; first >= end; first -= N) { //низ слева вверх
                        *first = RandomValueofRange(1, N * N);
                        int Y = (first - arr) / N;
                        destCoord.Y = Y;
                        SetConsoleCursorPosition(hStdout, destCoord);
                        printf("%03d\r", *first);
                        cout.flush();
                        Sleep(200);
                        cnt++;
                    }

                    k++; //сужается круг
                }

                system("cls"); //очищаем консоль

                destCoord.X = -sizeofNum;
                destCoord.Y += N * N;
                cout << "\n";

                makingMatrix(arr, N);

                cnt = 1;
                k = 0;

                //змейка

                int *upMax = &arr[k];
                int *downMin = &arr[N * N - N + k];

                while (cnt <= N * N) {

                    destCoord.X += sizeofNum;
                    for (int *first = upMax + k, *end = downMin + k; first <= end; first += N) {
                        *first = RandomValueofRange(1, N * N);
                        int Y = (first - arr) / N;
                        destCoord.Y = Y;
                        SetConsoleCursorPosition(hStdout, destCoord);
                        printf("%03d\r", *first);
                        cout.flush();
                        Sleep(200);
                        cnt++;
                    }

                    k++;
                    destCoord.X += 4;

                    for (int *first = downMin + k, *end = upMax + k; first >= end; first -= N) {
                        *first = RandomValueofRange(1, N * N);
                        int Y = (first - arr) / N;
                        destCoord.Y = Y;
                        SetConsoleCursorPosition(hStdout, destCoord);
                        printf("%03d\r", *first);
                        cout.flush();
                        Sleep(200);
                        cnt++;
                    }

                    k++;
                }
                for (int i = 0; i < N; i++) cout << "\n";
                break;
            }

            case 2: {

                int arr2[N * N] = {};

                cout << "\n" << "a" << "\n";

                //square - откуда, square2 - куда
                int* square[4] = {&arr[0], &arr[N / 2], &arr[N / 2 + N * (N / 2)], &arr[(N * N) / 2]};
                int* square2[4] = {&arr2[N / 2], &arr2[N / 2 + N * (N / 2)], &arr2[(N * N) / 2], &arr2[0]};
                SquareReplace(square, square2, N);
                outMatrix(arr2, N);

                //начинается перестановка блоков

                cout << "\n" << "b" << "\n";

                square[0] = &arr[0];
                square[1] = &arr[N / 2 + N * (N / 2)];
                square[2] = &arr[(N * N) / 2];
                square[3] = &arr[N / 2];

                square2[0] = &arr2[N / 2 + N * (N / 2)];
                square2[1] = &arr2[0];
                square2[2] = &arr2[N / 2];
                square2[3] = &arr2[(N * N) / 2];

                SquareReplace(square, square2, N);
                outMatrix(arr2, N);

                cout << "\n" << "c" << "\n";

                square[0] = &arr[0];
                square[1] = &arr[(N * N) / 2];
                square[2] = &arr[N / 2];
                square[3] = &arr[N / 2 + N * (N / 2)];

                square2[0] = &arr2[(N * N) / 2];
                square2[1] = &arr2[0];
                square2[2] = &arr2[N / 2 + N * (N / 2)];
                square2[3] = &arr2[N / 2];

                SquareReplace(square, square2, N);
                outMatrix(arr2, N);

                cout << "\n" << "d" << "\n";

                square[0] = &arr[0];
                square[1] = &arr[N / 2];
                square[2] = &arr[(N * N) / 2];
                square[3] = &arr[N / 2 + N * (N / 2)];

                square2[0] = &arr2[N / 2];
                square2[1] = &arr2[0];
                square2[2] = &arr2[N / 2 + N * (N / 2)];
                square2[3] = &arr2[(N * N) / 2];

                SquareReplace(square, square2, N);
                outMatrix(arr2, N);

                break;
            }

            case 3: {
                cout << "\n";
                insertSort(arr, N); //перестановка ставками
                outMatrix(arr, N);
                break;
            }

            case 4: {

                int type;
                cout << "\n" << "choose de type (1: +, 2: -, 3: *, 4: /): ";
                cin >> type;

                if (!cin.good() || type < 1 || type > 4) {
                    cout << "\n" << "you entered de wrong type";
                    break;
                }

                int num;
                cout << "\n" << "enter de number: ";
                cin >> num;
                cout << "\n";

                if (!cin.good()) {
                    cout << "\n" << "u entered de wrong number";
                    break;
                }
                if (type == 4 && num == 0) {
                    cout << "\n" << "u can't divide by zero! (Well, almost)";
                    break;
                }
                mathInMatrix(arr, N, type, num);
                outMatrix(arr, N);
                break;
            }

            //идз номер 9
            case 5: {
                cout << "\n";
                makingMatrix(arr, N, true);
                outMatrix(arr, N);

                int arr2[N * N] = {};
                int *begin = &arr[0];
                int *finish = &arr[N - 1];
                int *start = &arr2[0];

                for (int *first = begin, *end = finish, *next2 = start; finish < arr + N * N; first++, next2 += N) {
                    if (first == end ) {
                        begin += N;
                        start += 1;
                        finish = begin + N - 1;
                        *next2 = *first;
                        first = begin;
                        next2 = start;
                        end = finish;
                    }
                    if (end > arr + N * N) break;
                    *next2 = *first;
                }
                outMatrix(arr2, N);
                break;
            }
            default: {
                cout << "\n" << "you entered de wrong task number";
                break;
            }
        }

        cin.clear();
        cin.sync();

        char programStop;
        cout << "\n" << "press Y to continue the program ";
        cin >> programStop;
        cout << "\n";

        if (programStop != 'Y' && programStop != 'y') {
            break;
        }
    }

    return 0;
}