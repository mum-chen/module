

# weblink http://blog.csdn.net/cosa1231116/article/details/6196015

gcc test_a.c test_b.c test_c.c -fPIC -shared -o libtest.so
gcc test.c -L. -ltest -o test

