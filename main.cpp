#include <iostream>
#include "Main.h"

int main(int argc, char *argv[]) {
    auto sString = boot::SerialStringTester();
    auto pString = boot::ParallelStringTester();
    auto sMatrix = boot::SerialMatrixTester();
    auto pMatrix = boot::ParallelMatrixTester();

    cout<<"SerialStringServer start..."<<endl;
    sString.main(argc,argv);
    cout<<"SerialStringServer end..."<<endl;

    cout<<"ParallelStringTester start..."<<endl;
    pString.main(argc,argv);
    cout<<"ParallelStringTester end..."<<endl;

    cout<<"SerialMatrixTester start..."<<endl;
    sMatrix.main(argc,argv);
    cout<<"SerialMatrixTester end..."<<endl;

    cout<<"ParallelMatrixTester start..."<<endl;
    pMatrix.main(argc,argv);
    cout<<"ParallelMatrixTester end..."<<endl;

    return 0;
}
