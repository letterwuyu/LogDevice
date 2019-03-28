/**
 * Copyright (c) 2018-present, Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

include "logdevice/admin/if/common.thrift"

namespace cpp2 facebook.logdevice.thrift
namespace py3 logdevice.admin
namespace php LogDevice
namespace wiki LogDevice.Exceptions

/**
 * The node you are communicating with is not ready to respond yet.
 */
exception NodeNotReady {
  1: string message,
}

/**
 * The server has an older version than expected
 */
exception StaleVersion {
  1: string message,
  2: common.unsigned64 server_version,
}

/**
 * The operation is not supported
 */
exception NotSupported {
  1: string message,
}

/**
 * An operation that failed for unexpected reasons
 */
exception OperationError {
  1: string message,
  2: optional i32 error_code, // maps to E
}

/**
 * The request contains invalid parameters
 */
exception InvalidRequest {
  1: string message,
}

/**
 * There is maintenance already set by the same user for different targets
 */
exception MaintenanceClash {
  1: string message,
}

/**
 * The system couldn't match the maintenance in the definition with the internal
 * state
 */
exception MaintenanceMatchError {
  1: string message,
}

/*
 * The operation cannot be performed on this node, use the advise supplioed in
 * the redirect_to_node and retry the request
 */
exception Redirect {
  1: common.NodeID redirect_to_node,
}
