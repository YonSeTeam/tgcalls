#ifndef TGCALLS_SCREENCAST_QUALITY_H
#define TGCALLS_SCREENCAST_QUALITY_H

#include <optional>
#include <string>

namespace tgcalls {

// YonSeGram: how a shared screen is captured and encoded. A capture that never
// gets one keeps the upstream behaviour everywhere.
struct ScreencastQuality {
    // Frames are scaled down to at most this height before encoding, 0 keeps
    // the source size.
    int maxHeight = 0;
    int fps = 30;
    // Bitrate cap of the full quality stream, 0 keeps the engine default.
    int maxBitrateKbps = 0;
    // Under pressure keep the frame rate and lower the resolution, instead of
    // keeping the resolution and lowering the frame rate.
    bool preferMotion = false;
    // "VP8", "VP9", "H264" or "H265", tried first when both sides have it.
    std::string codec;
};

} // namespace tgcalls

#endif
