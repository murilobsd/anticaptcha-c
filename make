#!/bin/sh 

start=`date +%s`
echo "clean"
rm -f *.o a.out
echo "build http"
cc -c -g -O0 http.c -I/usr/local/include || exit
echo "build anticaptcha"
cc -c -g -O0 anticaptcha.c -I/usr/local/include || exit
echo "link"
cc -g -O0 http.o anticaptcha.o main.c -I/usr/local/include -L/usr/local/lib -lcurl || exit
end=`date +%s`
runtime=$((end-start))
echo "build time: $runtime"

#valgrind --leak-check=full \
#         --show-leak-kinds=all \
#         --track-origins=yes \
#         --verbose \
#         --log-file=valgrind-out.txt \
#         ./a.out
