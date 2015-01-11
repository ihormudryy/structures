rm -rf ~/structures_emsc_build
mkdir ~/structures_emsc_build
cd ~/structures_emsc_build

emcmake cmake \
	-G "Unix Makefiles" \
	-D EMSCRIPTEN_PATH=$EMSCRIPTEN_ROOT \
	-D EMSCRIPTEN=ON \
	-D CMAKE_BUILD_TYPE=Debug \
	-D BUILD_TESTS=ON \
	/home/stalker/Dropbox/structures

make -j2
cp ~/structures_emsc_build/src/main* ~/


