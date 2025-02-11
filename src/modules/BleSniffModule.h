#pragma once
#include "SinglePortModule.h"

/**
 * A simple example module that just replies with "Message received" to any message it receives.
 */
class BleSniffModule : public SinglePortModule, private concurrency::OSThread
{
  public:
  protected:
    /** For reply module we do all of our processing in the (normally optional)
     * want_replies handling
     */
    int32_t runOnce() override;
    virtual meshtastic_MeshPacket *allocReply() override;
};