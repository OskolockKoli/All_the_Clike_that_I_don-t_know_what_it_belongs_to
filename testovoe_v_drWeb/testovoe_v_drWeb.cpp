#include <iostream>

using namespace std;

void TrimRight(char* s) {
    if (!s) return;

    char* end = s + strlen(s) - 1;
    while (end >= s && *end == ' ') {
        *end = '\0';
        end--;
    }
}

int main()
{
    char str1[] = "  Hello, world!   ";
    TrimRight(str1);
    cout << str1 << ";" << endl;
    return 0;
}
