## Build iOS
```
git clone https://github.com/opencv/opencv.git
cd opencv/

mkdir build_ios
cd build_ios

cmake .. \
      -DCMAKE_TOOLCHAIN_FILE=../../ios-cmake/ios.toolchain.cmake \
      -DCMAKE_INSTALL_PREFIX:PATH="`grealpath ../../usr`/opencv/" \
      -DIOS_DEPLOYMENT_TARGET=11.0 \
      -DIOS_PLATFORM=OS \
      -DBUILD_SHARED_LIBS=OFF \
      -DBUILD_opencv_apps=OFF \
      -DWITH_PNG=OFF \
      -DWITH_CAP_IOS=OFF \
      -DWITH_AVFOUNDATION=OFF

make -j12 install

```
