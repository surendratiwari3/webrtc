/*
 *  Copyright (c) 2004 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_MEDIA_WEBRTC_FAKEWEBRTCVCMFACTORY_H_
#define WEBRTC_MEDIA_WEBRTC_FAKEWEBRTCVCMFACTORY_H_

#include <vector>

#include "webrtc/media/webrtc/fakewebrtcvideocapturemodule.h"
#include "webrtc/media/webrtc/webrtcvideocapturer.h"

// Factory class to allow the fakes above to be injected into
// WebRtcVideoCapturer.
class FakeWebRtcVcmFactory : public cricket::WebRtcVcmFactoryInterface {
 public:
  virtual webrtc::VideoCaptureModule* Create(int module_id,
                                             const char* device_id) {
    if (!device_info.GetDeviceById(device_id)) return NULL;
    FakeWebRtcVideoCaptureModule* module =
        new FakeWebRtcVideoCaptureModule(this, module_id);
    modules.push_back(module);
    return module;
  }
  virtual webrtc::VideoCaptureModule::DeviceInfo* CreateDeviceInfo(int id) {
    return &device_info;
  }
  virtual void DestroyDeviceInfo(webrtc::VideoCaptureModule::DeviceInfo* info) {
  }
  void OnDestroyed(webrtc::VideoCaptureModule* module) {
    std::remove(modules.begin(), modules.end(), module);
  }
  FakeWebRtcDeviceInfo device_info;
  std::vector<FakeWebRtcVideoCaptureModule*> modules;
};

FakeWebRtcVideoCaptureModule::~FakeWebRtcVideoCaptureModule() {
  if (factory_)
    factory_->OnDestroyed(this);
}

#endif  // WEBRTC_MEDIA_WEBRTC_FAKEWEBRTCVCMFACTORY_H_
