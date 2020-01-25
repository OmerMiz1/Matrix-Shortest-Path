#include <iostream>
#include "Main.h"

int main(int argc, char *argv[]) {

    auto myMain = server_side::boot::Main();
    /*Below made for testing*/
//    auto myMain = server_side::boot::ParallelMatrixTester();
    myMain.main(argc,argv);

    /*Below was used for testing :)*/
    /*auto sString = boot::SerialStringTester();
    auto pString = boot::ParallelStringTester();
    auto sMatrix = boot::SerialMatrixTester();
    auto pMatrix = boot::ParallelMatrixTester();*/
    /*cout<<"SerialStringServer start..."<<endl;
    sString.main(argc,argv);
    cout<<"SerialStringServer end..."<<endl;

    cout<<"ParallelStringTester start..."<<endl;
    pString.main(argc,argv);
    cout<<"ParallelStringTester end..."<<endl;*/
    /*cout<<"SerialMatrixTester start..."<<endl;
    sMatrix.main(argc,argv);
    cout<<"SerialMatrixTester end..."<<endl;*/
    /*cout<<"ParallelMatrixTester #1 start..."<<endl;
    pMatrix.main(argc,argv);
    cout<<"ParallelMatrixTester #1 end..."<<endl;*/

    return 0;
}
