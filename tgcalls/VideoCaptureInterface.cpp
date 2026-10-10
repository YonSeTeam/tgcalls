#include "VideoCaptureInterface.h"

#include "VideoCaptureInterfaceImpl.h"

namespace tgcalls {

std::unique_ptr<VideoCaptureInterface> VideoCaptureInterface::Create(
   std::shared_ptr<Threads> threads, std::string deviceId, bool isScreenCapture,
   std::shared_ptr<PlatformContext> platformContext) {
	return std::make_unique<VideoCaptureInterfaceImpl>(deviceId, isScreenCapture, platformContext, std::move(threads));
}

VideoCaptureInterface::~VideoCaptureInterface() = default;

bool HasVideoEncoder(std::string const &codecName) {
    // The same factory InstanceV2Impl and InstanceV2ReferenceImpl encode with.
    const auto factory = PlatformInterface::SharedInstance()->makeVideoEncoderFactory(true);
    if (!factory) {
        return false;
    }
    for (const auto &format : factory->GetSupportedFormats()) {
        if (format.name == codecName) {
            return true;
        }
    }
    return false;
}

} // namespace tgcalls
