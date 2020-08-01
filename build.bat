
mkdir build
call emcc main.c -I..\pr\sokol -o build\old_debug.html -fsanitize=address -s INITIAL_MEMORY=134217728 -g4 --source-map-base http://localhost:5000
call emcc main.c -I..\pr\sokol -o build\old_release.html -O2
call emcc main.c -I..\pr\sokol -s USE_PTHREADS -pthread -o build\pull_debug.html -fsanitize=address -s INITIAL_MEMORY=134217728 -g4 --source-map-base http://localhost:5000
call emcc main.c -I..\pr\sokol -s USE_PTHREADS -pthread -o build\pull_release.html -O2
call emcc main.c -I..\pr\sokol -s USE_PTHREADS -pthread -o build\push_debug.html -fsanitize=address -s INITIAL_MEMORY=134217728 -g4 --source-map-base http://localhost:5000 -DPUSH=1
call emcc main.c -I..\pr\sokol -s USE_PTHREADS -pthread -o build\push_release.html -O2 -DPUSH=1

