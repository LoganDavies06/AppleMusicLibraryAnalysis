cmake -S . -B build -DCMAKE_PREFIX_PATH="$(brew --prefix)"
cmake --build build
./build/MusicLibraryAnalysis