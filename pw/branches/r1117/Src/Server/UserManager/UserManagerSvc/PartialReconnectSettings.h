#pragma once

namespace UserManager
{
  class PartialReconnectSettings
  {
  public:
    PartialReconnectSettings();
    PartialReconnectSettings(bool _supported, unsigned int _retries, unsigned int _retryTimeout);

  public:
    bool supported() const;
    unsigned int retries() const;
    unsigned int retryTimeout() const;

  private:
    bool supported_;
    unsigned int retries_;
    unsigned int retryTimeout_;
  };

  inline
  bool PartialReconnectSettings::supported() const
  {
    return supported_;
  }

  inline
  unsigned int PartialReconnectSettings::retries() const
  {
    return retries_;
  }

  inline
  unsigned int PartialReconnectSettings::retryTimeout() const
  {
    return retryTimeout_;
  }
}
