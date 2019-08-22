/**
 * Copyright (c) 2017-present, Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include <chrono>
#include <functional>

#include <boost/program_options.hpp>
#include <folly/io/Cursor.h>
#include <folly/io/IOBuf.h>

#include "logdevice/server/Server.h"

struct evbuffer;

namespace facebook { namespace logdevice {

/**
 * @file Base class for admin commands.
 */

class AdminCommand {
 public:
  enum class RestrictionLevel { UNRESTRICTED = 0, LOCALHOST_ONLY = 1 };
  explicit AdminCommand(
      RestrictionLevel restrictionLevel = RestrictionLevel::UNRESTRICTED)
      : restrictionLevel_(restrictionLevel) {}
  virtual ~AdminCommand() {}
  virtual void
  getOptions(boost::program_options::options_description& /*out_options*/) {}
  virtual void getPositionalOptions(
      boost::program_options::positional_options_description& /*out_options*/) {
  }
  virtual std::string getUsage() {
    return "";
  }
  virtual void run() = 0;
  RestrictionLevel getRestrictionLevel() const {
    return restrictionLevel_;
  };

  void setServer(Server* server) {
    server_ = server;
  }
  void setOutput(folly::IOBuf* output) {
    out_ = folly::io::Appender(output, kGrowthValue);
  }

 protected:
  constexpr static size_t kGrowthValue = 100;
  Server* server_;
  const RestrictionLevel restrictionLevel_;
  folly::IOBuf buf_;
  folly::io::Appender out_{&buf_, kGrowthValue};
};

}} // namespace facebook::logdevice
