#pragma once

namespace NGameX
{
  class GenericAbuseController : public NonCopyable
  {
  public:
    explicit GenericAbuseController(const NDb::AbuseSettings& settings);
    ~GenericAbuseController();

    void Update(const float dt);
    bool Use();

    float GetCooldown() const { return cooldown; }
  private:
    typedef list<float> TUsages;

    const NDb::AbuseSettings settings;

    float cooldown;
    float time;

    TUsages usages;
  };
}
