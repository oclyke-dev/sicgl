# sicgl
\ si-kəl \
small iterator graphics library

# todo

* perform bounds checking within the library based on 
  passed in parameters of the screen but not in tight loops

# principles

* hardware agnostic
* entirely in c
* tested

# tests
unit tests are handled with [unity](https://github.com/ThrowTheSwitch/Unity) and functional tests are enabled using [libspng](https://github.com/randy408/libspng).

**building tests**
```
~/sicgl % mkdir build
~/sicgl % cd build
~/sicgl/build % cmake ..
~/sicgl/build % cmake --build .
```

**running tests**
```
~/sicgl/build % ./test_unity
~/sicgl/build % ./test_libspng_manual_pixels
...
```

**finding tests**
on mac you could use this regex to find tests...
```find -E . -regex '\.\/build\/test_[^\.]*$'```

# code formatting
this project uses clang-format. to format all the right code:

mac: ```find -E . -regex '\.\/(src|include|test)\/.*\.(c|h)$' | xargs clang-format -i```
