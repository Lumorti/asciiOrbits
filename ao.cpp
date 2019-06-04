#include <iostream>
#include <sys/ioctl.h>

using namespace std;

struct vector2Int {

    int x;
    int y;

};

void drawScreen(){



}

vector2Int getSize(){

    vector2Int dims;

    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    dims.x = w.ws_row;
    dims.y = w.ws_col;

    return dims;

}

int main(){

    vector2Int screenSize = getSize();
    cout << "lines: " << screenSize.x << endl << "columns: " << screenSize.y;

    return 0;

}
