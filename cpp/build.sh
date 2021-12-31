
#!/bin/bash

build()
{
    g++ -std=c++11 -Wall recv1.cpp utility.cpp -o recv -lzmq -lpthread
    g++ -std=c++11 -Wall send1.cpp utility.cpp -o send -lzmq -lpthread
    g++ -std=c++11 -Wall router1.cpp utility.cpp -o router -lzmq -lpthread
}

clean()
{
    rm -rf recv send router
}


parse()
{
    echo "these argument count: $#"
    echo "these argument are  : $*"
    if [ $# -lt 0 ]
    then
        echo "arguments << 1"
    elif [ $# -gt 1 ]
    then
        echo "arguments >> 1"
    elif [ $# == 1 ]
    then 
        echo "arguments == 1"
        if [ $1 == 'build' ]
        then
            build
        else
            clean
            fi
    else
        echo "arguments error"
        echo "sh build.sh build or clean"
    fi
}

#parse build
parse clean

