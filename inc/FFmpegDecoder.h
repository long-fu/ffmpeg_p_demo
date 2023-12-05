#include <dirent.h>
#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <thread>
#include <bits/std_mutex.h>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

#define INVALID_CHANNEL_ID (-1)
#define INVALID_STREAM_FORMAT (-1)
#define VIDEO_CHANNEL_MAX  (256)
#define RTSP_TRANSPORT_UDP "udp"
#define RTSP_TRANSPORT_TCP "tcp"


typedef int (*FrameProcessCallBack)(void* callback_param, void *frame_data,
                                    int frame_size);

enum StreamType {
    STREAM_VIDEO = 0,
    STREAM_RTSP,
};

enum DecodeStatus {
    DECODE_ERROR  = -1,
    DECODE_UNINIT = 0,
    DECODE_READY  = 1,
    DECODE_START  = 2,
    DECODE_FFMPEG_FINISHED = 3,
    DECODE_DVPP_FINISHED = 4,
    DECODE_FINISHED = 5
};

class FFmpegDecoder {
public:
    FFmpegDecoder(const std::string& name);
    ~FFmpegDecoder() {}
    void Decode(FrameProcessCallBack callback_func, void *callback_param);
    int GetFrameWidth()
    {
        return frameWidth_;
    }
    int GetFrameHeight()
    {
        return frameHeight_;
    }
    int GetVideoType()
    {
        return videoType_;
    }
    int GetFps()
    {
        return fps_;
    }
    int IsFinished()
    {
        return isFinished_;
    }
    int GetProfile()
    {
        return profile_;
    }
    void SetTransport(const std::string& transportType);
    void StopDecode()
    {
        isStop_ = true;
    }

private:
    int GetVideoIndex(AVFormatContext* av_format_context);
    void GetVideoInfo();
    void InitVideoStreamFilter(const AVBitStreamFilter* &video_filter);
    bool OpenVideo(AVFormatContext*& av_format_context);
    void SetDictForRtsp(AVDictionary* &avdic);
    bool InitVideoParams(int videoIndex,
                         AVFormatContext* av_format_context,
                         AVBSFContext* &bsf_ctx);

private:
    bool isFinished_;
    bool isStop_;
    int frameWidth_;
    int frameHeight_;
    int videoType_;
    int profile_;
    int fps_;
    std::string streamName_;
    std::string rtspTransport_;
};