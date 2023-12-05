# 环境配置

## FFmpeg Install 

```sh
THIRDPART_PATH=$(pwd)

git clone https://code.videolan.org/videolan/x264.git
cd x264
./configure --enable-shared --disable-asm --prefix=${THIRDPART_PATH}
make
make install

cd ..

wget http://www.ffmpeg.org/releases/ffmpeg-4.1.3.tar.gz --no-check-certificate
tar -zxvf ffmpeg-4.1.3.tar.gz
cd ffmpeg-4.1.3
# 安装ffmpeg
./configure --enable-shared --enable-pic --enable-static --disable-x86asm --enable-libx264 --enable-gpl --prefix=${THIRDPART_PATH}
make -j8
make install

```

**error**

注释调v4l2-common.h下面的代码
```c
// #if HAVE_SYS_VIDEOIO_H
// #include <sys/videoio.h>
// #else
// #if HAVE_ASM_TYPES_H
// #include <asm/types.h>
// #endif
// #include <linux/videodev2.h>
// #endif
// 替换
#include <linux/videodev2.h>
```