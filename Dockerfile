FROM gitlab-dl.nvidia.com:5005/dgx/cuda:10.0-cudnn7.2-devel-ubuntu16.04-cuda10.0--18.08

RUN apt-get update && apt-get install -y python-dev python-pip vim wget cmake libgtk2.0-dev \
    pkg-config libavcodec-dev libavformat-dev libswscale-dev \
    python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev \
    freeglut3 libglib2.0-0 libglew1.13 libgstreamer1.0-dev libopenblas-base

RUN mkdir /target
WORKDIR /target
COPY . .
RUN  rm -fr build
RUN mkdir build && cd build && cmake .. -DWITH_OPENCL=OFF -DENABLE_CXX11=ON -DBUILD_EXAMPLES=OFF -DCPACK_GENERATOR=DEB -DBUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -DBUILD_opencv_java=OFF -DBUILD_opencv_apps=OFF -DCUDA_ARCH_BIN="7.0 8.0" -DBUILD_SHARED_LIBS=ON -DBUILD_PERF_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/usr -DOPENCV_CUSTOM_PACKAGE_INFO=ON -DCPACK_PACKAGE_DESCRIPTION="OpenCV 3.4.2+cuda10.0-nv" -DCPACK_PACKAGE_VENDOR="NVIDIA Corp." -DCPACK_PACKAGE_CONTACT="bfomitchev@nvidia.com" -DCPACK_PACKAGE_VERSION_MAJOR=3 -DCPACK_PACKAGE_VERSION_MINOR=3 -DCPACK_PACKAGE_VERSION_PATCH="1+cuda10.0" -DCPACK_PACKAGE_VERSION="3.4.2.1+cuda10.0" -DCPACK_PACKAGE_FILE_NAME="OpenCV-3.4.2.1+cuda10.0-amd64"

RUN cd build && make -j12
RUN cd build && make -j12 install
RUN cd build && make -j12 package
