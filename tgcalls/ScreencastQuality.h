#ifndef TGCALLS_SCREENCAST_QUALITY_H
#define TGCALLS_SCREENCAST_QUALITY_H

#include <cstdint>
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
    // "VP8", "H264" or "H265", tried first in private calls when both sides
    // have it. VP9 is never put first for a shared screen.
    std::string codec;
};

// YonSeGram: whether private calls on this platform have an encoder for the
// codec, by its SDP name ("H265", ...).
bool HasVideoEncoder(std::string const &codecName);

// YonSeGram: one video stream as the client stats overlay shows it.
struct VideoStreamStats {
    int width = 0;
    int height = 0;
    int fps = 0;
    // Payload bytes so far, the client turns two readings into a bitrate.
    int64_t bytes = 0;
    std::string codec;
};

// YonSeGram: candidate types are ICE ones: "host", "srflx", "prflx", "relay".
struct VideoStatsSnapshot {
    std::optional<VideoStreamStats> outgoing;
    std::optional<VideoStreamStats> incoming;
    std::string localCandidateType;
    std::string localAddress;
    std::string remoteCandidateType;
    std::string remoteAddress;
};

} // namespace tgcalls

#endif
