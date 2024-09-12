#pragma once

namespace MulticastTest
{
  struct MulticastCfg
  {
    nstl::string loginaddr_;
    nstl::string user_;
    nstl::string sessionKey_;
    int sorcvbuf_;
    unsigned int rcvbuf_;
    int sosndbuf_;

    MulticastCfg();

    void print();
    bool parse_args(int argc, char* argv[]);

  };
}
