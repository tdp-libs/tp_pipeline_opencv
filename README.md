## Build iOS
```
mkdir opencv
cd opencv/
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
python opencv/platforms/ios/build_framework.py ios --contrib opencv_contrib

mkdir usr
mkdir usr/include
cd usr/include/
ln -snf ../../ios/opencv2.framework/Headers opencv2
cd ../..

```
